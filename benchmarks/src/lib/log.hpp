#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

enum LogLevel { DEBUG, INFO, WARNING, ERROR };

enum LogDestination { CONSOLE, FILE_ONLY, CONSOLE_AND_FILE };

class Logger {
  public:
    /**
     * @brief Constructs a Logger instance.
     * @param level The minimum log level to record.
     * @param useTimestamp Whether to include timestamps in log messages
     * (default: true).
     * @param destination The log destination, which can be CONSOLE, FILE_ONLY,
     * or CONSOLE_AND_FILE (default: CONSOLE).
     * @param logFile The name of the log file (if destination is FILE_ONLY or
     * CONSOLE_AND_FILE).
     */
    Logger(LogLevel level = INFO, bool useTimestamp = true);

    /**
     * @brief Logger destructor, destroys the Logger instance.
     */
    ~Logger();

    /**
     * @brief Sets the minimum log level.
     * @param level The minimum log level to record.
     */
    void setLogLevel(LogLevel level);

    /**
     * @brief Enables or disables timestamps in log messages.
     * @param enable True to enable timestamps, false to disable.
     */
    void enableTimestamps(bool enable);

    /**
     * @brief Sets the log destination.
     * @param destination The log destination, which can be CONSOLE, FILE_ONLY,
     * or CONSOLE_AND_FILE.
     */
    void setLogDestination(LogDestination destination);

    /**
     * @brief Sets the log file name for FILE_ONLY or CONSOLE_AND_FILE
     * destinations.
     * @param logFile The name of the log file.
     */
    void setLogFile(const std::string &logFile);

    /**
     * @brief Logs a message with the specified log level.
     * @param level The log level of the message.
     * @param message The message to log.
     */
    void log(LogLevel level, const std::string &message);

  private:
    /**
     * @brief The minimum log level to record.
     */
    LogLevel logLevel;

    /**
     * @brief Flag indicating whether to include timestamps in log messages.
     */
    bool enableTimestamp;

    /**
     * @brief The log destination, which can be CONSOLE, FILE_ONLY, or
     * CONSOLE_AND_FILE.
     */
    LogDestination logDestination;

    /**
     * @brief Flag indicating whether to log messages to a file.
     */
    bool logToFile;

    /**
     * @brief The output stream for logging to a file.
     */
    std::ofstream logFileStream;

    /**
     * @brief Gets the log prefix based on the log level.
     * @param level The log level.
     * @return A string representing the log prefix.
     */
    std::string getLogPrefix(LogLevel level);

    /**
     * @brief Gets the current timestamp as a string.
     * @return A string representing the current timestamp.
     */
    std::string getCurrentTimestamp();

    /**
     * @brief Formats a log message with a specified prefix.
     * @param prefix The log message prefix.
     * @param message The log message content.
     * @return The formatted log message as a string.
     */
    std::string formatLogMessage(const std::string &prefix,
                                 const std::string &message);
};

#endif
