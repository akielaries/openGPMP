/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
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

/**
 * @file
 *
 * @brief Miscellaneous utilities methods related to openGPMP
 *
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

enum LogDestination {
    CONSOLE,
    FILE_ONLY,
    CONSOLE_AND_FILE
};

namespace gpmp {

namespace core {

class TypeCast {
  public:
    void convert();
    /** std::string -> c string
     *
     */

    /* std::array -> c array on stack
     *      int arr[4];
     */

    /* std::vector -> c array on heap ?
     *      int *arr = new int[5];
     */

    /** std::tuple -> c array
     *
     */

    /** std::pair -> struct
     *
     */

    /** std::map -> c array (key, val)
     *
     */

    /** std::unordered_map -> c array (key, val)
     *
     */

    /** std::shared_ptr -> c ptr
     *
     */

    /** std::unique_ptr -> c ptr
     *
     */
};
class Logger {
public:
    Logger(LogLevel level = INFO, bool useTimestamp = true, LogDestination destination = CONSOLE, const std::string& logFile = "");
    ~Logger();

    void setLogLevel(LogLevel level);
    void enableTimestamps(bool enable);
    void setLogDestination(LogDestination destination);
    void setLogFile(const std::string& logFile);
    void log(LogLevel level, const std::string& message);

private:
    LogLevel logLevel;
    bool enableTimestamp;
    LogDestination logDestination;
    bool logToFile;
    std::ofstream logFileStream;

    std::string getLogPrefix(LogLevel level);
    std::string getCurrentTimestamp();
    std::string formatLogMessage(const std::string& prefix, const std::string& message);
};

} // namespace core

} // namespace gpmp

#endif
