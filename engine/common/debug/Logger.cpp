//
// Created by jbili on 11.03.2021.
//

#include "Logger.h"
#include "../StringUtil.h"

#include <boxer/boxer.h>
#include <fmt/os.h>
#include <fmt/compile.h>
#include <fmt/chrono.h>

std::unique_ptr<std::fstream> Logger::File{};

void Logger::Initialize(const bool enableConsoleLogging, const bool enableFileLogging, const std::string& filePath,
                        const bool enableErrorMessageBox, const LoggerModes loggerLevel)
{
    if (Initialized)
        return;

    EnabledConsoleLogging = enableConsoleLogging;
    EnabledFileLogging = enableFileLogging;
    EnableErrorMessageBox = enableErrorMessageBox;

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
        File = nullptr;
    }

    EnabledConsoleLogging = false;
    EnabledFileLogging = false;

    LoggingLevel = DEBUG;

    Initialized = false;
}

void Logger::Log(const LoggerModes level, const std::string& message, const std::string& file,
                 const std::string& function, unsigned int line)
{
    if (!Initialized)
        return;

    if (level < LoggingLevel)
        return;

    const auto prefix = GeneratePrefix(level);
    const auto filename = StringUtil::FindFilename(file);
    const auto combinedMessage = fmt::format(FMT_COMPILE("{}|{}|{}|{}|{}\n"), prefix, filename, function, line,
                                             message);

    if (EnabledConsoleLogging)
        LogToConsole(combinedMessage);

    if (EnabledFileLogging)
        LogToFile(combinedMessage);

    if (level == LoggerModes::ERROR && EnableErrorMessageBox)
        boxer::show(message.c_str(), "TITLE HERE", boxer::Style::Error, boxer::Buttons::OK); // TODO: Title as string
}

std::string Logger::GeneratePrefix(const LoggerModes loggerLevel)
{
    std::string levelString;
    switch (loggerLevel)
    {
    case DEBUG:
        levelString = "DBG";
        break;
    case WARNING:
        levelString = "WRN";
        break;
    case ERROR:
        levelString = "ERR";
        break;
    }

    return fmt::format(FMT_COMPILE("{:%H:%M:%S}|{:s}"), fmt::localtime(std::time(nullptr)), levelString);
}

void Logger::LogToConsole(const std::string& message)
{
    std::cout << message;
}

void Logger::LogToFile(const std::string& message)
{
    *File << message;
}
