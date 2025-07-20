#include "logger.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

std::mutex Logger::log_mutex;
std::ofstream Logger::log_file;
bool Logger::log_to_file = false;

void Logger::init(const std::string& file) {
    if (!file.empty()) {
        log_file.open(file, std::ios::app);
        log_to_file = log_file.is_open();
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::string timestamp = getTimeStamp();
    std::string level_str = levelToString(level);
    std::string full_message = "[" + timestamp + "] [" + level_str + "] " + message;

    std::cout << full_message << std::endl;
    if (log_to_file) {
        log_file << full_message << std::endl;
    }
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warn(const std::string& message) {
    log(LogLevel::WARN, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERR, message);
}

std::string Logger::getTimeStamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    std::time_t time = system_clock::to_time_t(now);
    std::tm tm{};
#if defined (_WIN32)
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERR: return "ERROR";
        default: return "UNKNOWN";
    }
}
