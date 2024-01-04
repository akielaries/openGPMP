/**
 * File containing functions to display system information
 * TODO: figure out logic behind collecting information (to variables) and
 * dumping them en masse to a file. this should be done logically with some
 * sort of interval / condition on collecting data to log i.e.:
 *  - before benchmark test
 *  - during test (how often?, pause/resume timers before/after check_mem call?)
 *  - after test
 */
#include "../lib/sys.hpp"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <thread>
#include <vector>

#ifdef __HAS_NVCC__

// This will break compilation with g++ even if protected with ifdef since cpp
// files assume g++
// #include <cuda_runtime_api.h>

#endif

// function to read and return the contents of a file
std::string System::read_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "Error: Unable to read " + filename;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// function to get the number of running processes
int System::ps_count() {
    FILE *proc_pipe = popen("ps aux | wc -l", "r");
    if (!proc_pipe) {
        std::cerr << "popen failed for processes." << std::endl;
        return -1;
    }

    char proc_buffer[128];
    if (fgets(proc_buffer, sizeof(proc_buffer), proc_pipe) != nullptr) {
        int num_proc = std::stoi(proc_buffer);
        pclose(proc_pipe);
        return num_proc;
    } else {
        std::cerr << "Failed to read the output of 'ps'." << std::endl;
        pclose(proc_pipe);
        return -1;
    }
}

// function to display CPU usage
void System::cpu_usage() {
    std::string cpu_usage = read_file("/proc/loadavg");
    std::cout << "CPU Usage (load average): " << cpu_usage;
}

// function to extract CPU BogoMIPS and model name
void System::cpu_info() {
    std::string lscpu_output;
    std::string model;
    double bogoMIPS = 0.0;
    int numCPUs = 0;

    // run the lscpu command and capture its output
    FILE *pipe = popen("lscpu", "r");
    if (pipe) {
        char buffer[128];
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != nullptr) {
                lscpu_output += buffer;
            }
        }
        pclose(pipe);

        // parse lscpu output to extract information
        size_t pos = 0;
        while (pos < lscpu_output.size()) {
            size_t newline_pos = lscpu_output.find('\n', pos);
            if (newline_pos == std::string::npos) {
                newline_pos = lscpu_output.size();
            }
            std::string line = lscpu_output.substr(pos, newline_pos - pos);

            // convert the line to lowercase for case-insensitive matching
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);

            if (line.find("model name") != std::string::npos) {
                // extract model name
                size_t colon_pos = line.find(":");
                if (colon_pos != std::string::npos) {
                    model = line.substr(colon_pos + 1);
                    System::cpu_model =
                        model.substr(model.find_first_not_of(" \t"),
                                     model.find_last_not_of(" \t") + 1);
                }
            } else if (line.find("bogomips") != std::string::npos) {
                // extract BogoMIPS value
                size_t colon_pos = line.find(":");
                if (colon_pos != std::string::npos) {
                    bogoMIPS = std::stod(line.substr(colon_pos + 1));
                    System::bogus_mips = bogoMIPS;
                }
            } else if (line.find("cpu(s):") != std::string::npos) {
                // extract the number of CPU(s)
                size_t colon_pos = line.find(":");
                if (colon_pos != std::string::npos) {
                    numCPUs = std::stoi(line.substr(colon_pos + 1));
                    System::num_proc = numCPUs;
                }
            }

            pos = newline_pos + 1;
        }

        // print the extracted information
        // std::cout << "CPU model: " << model << std::endl;
        // std::cout << "BogoMIPS: " << bogoMIPS << std::endl;
        // std::cout << "Number of CPU(s): " << numCPUs << std::endl;
    }
    // otherwise
    else {
        std::cerr << "Failed to run lscpu command." << std::endl;
    }
}

// function to display CPU temperature
double System::cpu_temp() {
    // TODO initialize starting temp here?
    std::string cpu_temp = read_file("/sys/class/thermal/thermal_zone0/temp");
    if (!cpu_temp.compare(0, 5, "Error")) {
        std::cout << "Error reading CPU temperature." << std::endl;
    } else {
        float temp_c = std::stof(cpu_temp) / 1000.0; // convert to Celsius
        // float temp_f = (temp_c * 9 / 5) + 32;        // convert to Fahrenheit
        // std::cout << "CPU Temperature: " << temp_c << "°C"
        //          << " (" << temp_f << "°F)" << std::endl;
        return temp_c;
    }
    return -1;
}

double System::cpu_idle_temp() {
    std::cout << "Determining idle CPU temperature...\n";

    int duration = 20;

    std::vector<double> temperatures;
    auto time_start = std::chrono::steady_clock::now();
    while (true) {
        auto time_now = std::chrono::steady_clock::now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                                time_now - time_start)
                                .count();
        if (time_elapsed >= duration) {
            break;
        }
        double temperature = cpu_temp();
        temperatures.push_back(temperature);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    double sum = 0.0;
    for (const double &temp : temperatures) {
        sum += temp;
    }
    double idle_temp = sum / temperatures.size();

    return idle_temp;
}

// wait until idle CPU temp is met
void System::cpu_idle(double idle_temp) {
    while (true) {
        double temp_now = cpu_temp();

        if (temp_now <= idle_temp) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// get CPU usage
double System::cpu_load() {
    std::ifstream file("/proc/stat");
    if (!file.is_open()) {
        std::cerr << "Failed to open /proc/stat" << std::endl;
        return -1.0;
    }

    std::string line;
    std::getline(file, line);

    std::istringstream iss(line);
    std::string cpuLabel;
    iss >> cpuLabel;

    if (cpuLabel != "cpu") {
        std::cerr << "Failed to parse /proc/stat" << std::endl;
        return -1.0;
    }

    std::vector<uint64_t> values;
    uint64_t value;
    while (iss >> value) {
        values.push_back(value);
    }

    if (values.size() < 7) {
        std::cerr << "Failed to parse /proc/stat" << std::endl;
        return -1.0;
    }

    uint64_t idle = values[3];
    uint64_t total = 0;
    for (int i = 0; i < 7; i++) {
        total += values[i];
    }

    // Calculate CPU usage as a percentage
    double usage = 100.0 * (1.0 - static_cast<double>(idle) / total);
    // std::cout << "CPU USAGE: " << usage << std::endl;
    return usage;
}

// function to display memory statistics
void System::mem_info() {
    std::ifstream meminfo_file("/proc/meminfo");
    if (meminfo_file.is_open()) {
        std::string line;
        std::vector<std::string> fetched_stats =
            {"MemTotal:", "MemFree:", "MemAvailable:", "Buffers:", "Cached:"};

        while (std::getline(meminfo_file, line)) {
            for (const std::string &stat : fetched_stats) {
                if (line.find(stat) == 0) {
                    std::cout << line << std::endl;
                }
            }
        }
    } else {
        std::cerr << "Failed to read /proc/meminfo." << std::endl;
    }
}

// get memory usage info programmatically
void System::mem_stats() {
    struct sysinfo mem_info;

    sysinfo(&mem_info);

    uint64_t virt_total =
        (mem_info.totalram + mem_info.totalswap) * mem_info.mem_unit;
    uint64_t virt_used = (mem_info.totalram - mem_info.freeram +
                          mem_info.totalswap - mem_info.freeswap) *
                         mem_info.mem_unit;

    uint64_t phys_total = mem_info.totalram * mem_info.mem_unit;
    uint64_t phys_used =
        (mem_info.totalram - mem_info.freeram) * mem_info.mem_unit;

    // VIRTUAL MEM in KB
    System::v_mem_total = virt_total / 1000;
    System::v_mem_used = virt_used / 1000;
    System::v_mem_free = (virt_total - virt_used) / 1000;

    // PHYSICAL MEM in KB
    System::p_mem_total = phys_total / 1000;
    System::p_mem_used = phys_used / 1000;
    System::p_mem_free = (phys_total - phys_used) / 1000;
}

bool has_nvidia_gpu() {
    std::string command = "nvcc -V";
    std::string result;

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error: Unable to execute command" << std::endl;
        return false;
    }

    // fetch command output
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    // close the pipe for cmd
    int status = pclose(pipe);
    if (status == -1) {
        std::cerr << "Error: Unable to close command pipe" << std::endl;
        return false;
    }

    // check if "nvcc" was found in the output
    return result.find("nvcc") != std::string::npos;
}

#ifdef __HAS_NVCC__

#endif

/*
int main() {

    mem_stats();
    cpu_load();
    return 0;
}*/
