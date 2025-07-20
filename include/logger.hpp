#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    INFO,
    WARN,
    ERR
};

class Logger {
public:
    static void init(const std::string& file = "");
    static void log(LogLevel level, const std::string& message);

    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

private:
    static std::mutex log_mutex;
    static std::ofstream log_file;
    static bool log_to_file;

    static std::string getTimeStamp();
    static std::string levelToString(LogLevel level);
};

#endif