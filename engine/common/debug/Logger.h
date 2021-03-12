//
// Created by jbili on 11.03.2021.
//

#ifndef CLUSEK_RT_LOGGER_H
#define CLUSEK_RT_LOGGER_H

#include <string>
#include <fstream>
#include <iostream>

#include "LoggerModes.h"

class Logger final
{
public:
    static void Initialize(bool enableConsoleLogging, bool enableFileLogging, const std::string& filePath,
                           LoggerModes loggerLevel);
    static void Free();

    static void Log(LoggerModes level, const std::string& message);
private:
    inline static bool Initialized = false;

    static std::unique_ptr<std::fstream> File;

    inline static bool EnabledConsoleLogging = false;
    inline static bool EnabledFileLogging = false;
    inline static LoggerModes LoggingLevel;

    static void LogToConsole(const std::string& message);
    static void LogToFile(const std::string& message);
};

#endif //CLUSEK_RT_LOGGER_H
