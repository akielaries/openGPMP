#include "../lib/log.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

Logger::Logger(LogLevel level, bool useTimestamp)
    : logLevel(level), enableTimestamp(useTimestamp), logDestination(CONSOLE),
      logToFile(false) {
}

Logger::~Logger() {
    if (logToFile) {
        logFileStream.close();
    }
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::enableTimestamps(bool enable) {
    enableTimestamp = enable;
}

void Logger::setLogDestination(LogDestination destination) {
    logDestination = destination;
}

void Logger::setLogFile(const std::string &logFile) {
    logToFile = true;
    logFileStream.open(logFile, std::ios::out | std::ios::app);
    if (!logFileStream.is_open()) {
        std::cerr << "Error: Could not open log file " << logFile << std::endl;
    }
}

void Logger::log(LogLevel level, const std::string &message) {
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

std::string Logger::getLogPrefix(LogLevel level) {
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

std::string Logger::getCurrentTimestamp() {
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

std::string Logger::formatLogMessage(const std::string &prefix,
                                     const std::string &message) {
    std::string logMessage = prefix + " " + message;
    if (enableTimestamp) {
        logMessage = getCurrentTimestamp() + " " + logMessage;
    }
    return logMessage;
}

/*int main() {
    // Create a logger with default settings (log to console with timestamps)
    Logger logger;

    // Log messages at various log levels
    logger.log(DEBUG, "This is a debug message.");
    logger.log(INFO, "This is an info message.");
    logger.log(WARNING, "This is a warning message.");
    logger.log(ERROR, "This is an error message.");

    return 0;
}*/
