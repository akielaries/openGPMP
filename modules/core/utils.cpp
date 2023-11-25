/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

/*
 * Utilities implementations for different helper methods/functions
 * needed for openGPMP
 */
#include "../../include/core/utils.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

gpmp::core::Logger::Logger(LogLevel level, bool useTimestamp)
    : logLevel(level), enableTimestamp(useTimestamp), logDestination(CONSOLE),
      logToFile(false) {
}

gpmp::core::Logger::~Logger() {
    if (logToFile) {
        logFileStream.close();
    }
}

void gpmp::core::Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void gpmp::core::Logger::enableTimestamps(bool enable) {
    enableTimestamp = enable;
}

void gpmp::core::Logger::setLogDestination(LogDestination destination) {
    logDestination = destination;
}

void gpmp::core::Logger::setLogFile(const std::string &logFile) {
    logToFile = true;
    logFileStream.open(logFile, std::ios::out | std::ios::app);
    if (!logFileStream.is_open()) {
        std::cerr << "Error: Could not open log file " << logFile << std::endl;
    }
}

void gpmp::core::Logger::log(LogLevel level, const std::string &message) {
    if (level >= logLevel) {
        std::string prefix = getLogPrefix(level);
        std::string logMessage = formatLogMessage(prefix, message);

        if (logDestination == CONSOLE || logDestination == CONSOLE_AND_FILE) {
            if (level == ERROR) {
                std::cerr << logMessage << std::endl;
            } else {
                std::cout << logMessage << std::endl;
            }
        }
        if (logDestination != CONSOLE && logToFile && logFileStream.is_open()) {
            logFileStream << logMessage << std::endl;
        }
    }
}

std::string gpmp::core::Logger::getLogPrefix(LogLevel level) {
    switch (level) {
    case DEBUG:
        return "[DEBUG]";
    case INFO:
        return "[INFO]";
    case WARNING:
        return "[WARN]";
    case ERROR:
        return "[ERR]";
    default:
        return "[UNKN]";
    }
}

std::string gpmp::core::Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) %
              1000;
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&nowTime);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S") << '.' << std::setfill('0')
        << std::setw(3) << ms.count();

    return oss.str();
}

std::string gpmp::core::Logger::formatLogMessage(const std::string &prefix,
                                                 const std::string &message) {
    std::string logMessage = prefix + " " + message;
    if (enableTimestamp) {
        logMessage = getCurrentTimestamp() + " " + logMessage;
    }
    return logMessage;
}

/*int main() {
    // Create a logger with default settings (log to console with timestamps)
    gpmp::core::Logger logger;

    // Log messages at various log levels
    logger.log(DEBUG, "This is a debug message.");
    logger.log(INFO, "This is an info message.");
    logger.log(WARNING, "This is a warning message.");
    logger.log(ERROR, "This is an error message.");

    return 0;
}*/
