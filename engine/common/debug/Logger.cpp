//
// Created by jbili on 11.03.2021.
//

#include "Logger.h"

std::unique_ptr<std::fstream> Logger::File{};

void Logger::Initialize(const bool enableConsoleLogging, const bool enableFileLogging, const std::string& filePath,
                        const LoggerModes loggerLevel)
{
    if (Initialized)
        return;

    EnabledConsoleLogging = enableConsoleLogging;
    EnabledFileLogging = enableFileLogging;
    LoggingLevel = loggerLevel;

    if (EnabledFileLogging)
    {
        File = std::make_unique<std::fstream>(filePath, std::ofstream::out);
        if (!File)
            return;
    }

    Initialized = true;
}

void Logger::Free()
{
    if (EnabledFileLogging)
    {
        File->close();
    }

    EnabledConsoleLogging = false;
    EnabledFileLogging = false;
    LoggingLevel = DEBUG;

    Initialized = false;
}

void Logger::Log(const LoggerModes level, const std::string& message)
{
    if (EnabledConsoleLogging)
        LogToConsole(message);

    if (EnabledFileLogging)
        LogToFile(message);
}

void Logger::LogToConsole(const std::string& message)
{
    std::cout << message;
}

void Logger::LogToFile(const std::string& message)
{
    *File << message;
}
