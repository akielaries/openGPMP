#ifndef SYSSTATS_HPP
#define SYSSTATS_HPP
#include <string>

class System {
  public:
    /** CPU/PROC info */
    std::string cpu_model; // proc model
    double bogus_mips;     // proc speed
    int num_proc;          // # of processors

    /** Idle CPU temp set in cpu_idle_temp() */
    double cpu_temp_idle;
    float cpu_use;
    /** IRTUAL MEMORY IN KB */
    uint64_t v_mem_total;
    uint64_t v_mem_used;
    uint64_t v_mem_free;

    /** PHYSICAL MEMORY IN KB */
    uint64_t p_mem_total;
    uint64_t p_mem_used;
    uint64_t p_mem_free;

    /**
     * @brief reads the contents of a file into a string
     *
     * @param filename path to the file to be read
     * @return string containing the contents of the file if successful, or an
     * error message if the file cannot be opened or read
     */
    std::string read_file(const std::string &filename);

    /**
     * @brief get number of running processes on the system
     *
     * @return number of running processes or error code
     */
    int ps_count();

    /**
     * @brief get CPU usage using load average read from /proc/loadavg
     * calculating CPU and IO utilization over the last
     *
     * 1 / 5 / 10 min, number of running/total processes, last PID
     *  0.20 0.18 0.12 1/80 11206
     */
    void cpu_usage();

    /**
     * @brief get CPU info, BogoMIPS and Model
     */
    void cpu_info();

    /**
     * @brief get memory info and stats from /proc/meminfo
     */
    void mem_info();

    /**
     * @brief get current CPU temperature from
     * /sys/class/thermal/thermal_zone0/temp
     */
    double cpu_temp();

    /**
     * @brief get idle CPU temp based on a 20 second cooldown
     * @return idle CPU temp
     */
    double cpu_idle_temp();

    /**
     * @brief pause program execution until idle CPU temp is reached
     * @param idle_temp idle CPU temp
     */
    void cpu_idle(double idle_temp);

    /**
     * @brief get CPU usage
     * @return usage as a percentage
     */
    double cpu_load();

    /**
     * @brief get memory stats and populate Sys class variables
     */
    void mem_stats();

    /**
     * @brief determine if host has Nvidia GPU/NVCC compiler
     * @return true/false
     */
    bool has_nvidia_gpu();

/** IF CUDA CAPABLE DEVICE */
#ifdef __HAS_NVCC__
    /** NVIDIA GPU INFO */
    /** GPU name */
    std::string name;
    /** CUDA driver version */
    int nvd_driver_version;
    /** CUDA runtime version */
    int cuda_version;
    int major;
    int minor;
    /** total memory in KB */
    float total_glbl_mem;
    /** GPU count */
    int gpu_mp_count;
    /** CUDA GPU cores */
    int cuda_cores;
    /** max GPU clock rate in GHz */
    float max_clock_rt;
    /** total GPU memory */
    size_t total_const_mem;
    /** shared memory / block */
    size_t shared_mem_pb;
    /** max threads per GPU */
    int max_mp_threads;
    /** max thread per GPU block */
    int max_pb_threads;
    /** GPU threads MAX dimension */
    int max_dim_threads[3];
    /** GPU MAX grid size */
    int max_grid_size[3];
    size_t gpu_mem_total;
    size_t gpu_mem_used;
    size_t gpu_mem_free;

    /**
     * @brief get Nvidia GPU architecture from reference matrix
     */
    int _gpu_arch(int major, int minor);

    /**
     * @brief get Nvidia GPU information
     */
    void gpu_info();

    /**
     * @brief display Nvidia GPU information
     */
    void gpu_info_print();

#endif
};

#endif
