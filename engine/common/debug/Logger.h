//
// Created by jbili on 11.03.2021.
//

#ifndef CLUSEK_RT_LOGGER_H
#define CLUSEK_RT_LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#ifdef _WIN32

#include <cassert>
#include <windows.h>

#endif

#include "LoggerModes.h"

#define LOG_DEBUG(message) Logger::Log(DEBUG_MODE, message, __FILE__, __FUNCTION__, __LINE__)
#define LOG_WARNING(message) Logger::Log(WARNING_MODE, message, __FILE__, __FUNCTION__, __LINE__)
#define LOG_ERROR(message) Logger::Log(ERROR_MODE, message, __FILE__, __FUNCTION__, __LINE__)

class Logger final
{
public:
    static void Initialize(bool enableConsoleLogging, bool enableFileLogging, const std::string& filePath,
                           bool enableErrorMessageBox, LoggerModes loggerLevel);
    static void Free();

    /// Don't call this function manually. Use proper USE_* macro instead.
    static void Log(LoggerModes level, const std::string& message, const std::string& file, const std::string& function,
                    unsigned int line);
private:
    inline static bool Initialized = false;

    static std::unique_ptr<std::fstream> File;

    inline static bool EnabledConsoleLogging = false;
    inline static bool EnabledFileLogging = false;
    inline static bool EnableErrorMessageBox = false;

    inline static LoggerModes LoggingLevel;

#ifdef _WIN32
    static HANDLE ConsoleHandle;
#endif

    static std::string GeneratePrefix(LoggerModes loggerLevel);

    static void LogToConsole(const std::string& message, LoggerModes level);
    static void LogToFile(const std::string& message);
};

#endif //CLUSEK_RT_LOGGER_H
