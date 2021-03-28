//
// Created by jbili on 11.03.2021.
//

#include "Logger.h"

#include <boxer/boxer.h>
#include <fmt/os.h>
#include <fmt/compile.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

#include "../StringUtil.h"
#include "../translations/Text.h"

std::unique_ptr<std::fstream> Logger::File{};

#ifdef _WIN32
HANDLE Logger::ConsoleHandle{};
#endif

void Logger::Initialize(const bool enableConsoleLogging, const bool enableFileLogging, const std::string& filePath,
                        const bool enableErrorMessageBox, const LoggerModes loggerLevel)
{
    if (Initialized)
        return;

    EnabledConsoleLogging = enableConsoleLogging;
    EnabledFileLogging = enableFileLogging;
    EnableErrorMessageBox = enableErrorMessageBox;

    ColorsDisabledDueToError = false;

    LoggingLevel = loggerLevel;

    if (EnabledFileLogging)
    {
        File = std::make_unique<std::fstream>(filePath, std::ofstream::out);
        if (!File)
            return;
    }

#ifdef _WIN32
    ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

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

    ColorsDisabledDueToError = false;

    LoggingLevel = DEBUG_MODE;

    Initialized = false;
}

void Logger::Log(const LoggerModes level, const std::string& message, const std::string& file,
                 const std::string& function, unsigned int line)
{
    if (!Initialized)
        return;

    if (level < LoggingLevel)
        return;

    if (EnabledConsoleLogging || EnabledFileLogging)
    {
        const auto prefix = GeneratePrefix(level);
        const auto filename = StringUtil::FindFilename(file);
        const auto combinedMessage = fmt::format(FMT_COMPILE("{}|{}|{}|{}|{}"), prefix, filename, function, line,
                                                 message);

        if (EnabledConsoleLogging)
            LogToConsole(combinedMessage, level);

        if (EnabledFileLogging)
            LogToFile(combinedMessage);
    }

    if (level == LoggerModes::ERROR_MODE && EnableErrorMessageBox)
    {
        const auto title = Text::Get("logger_error_box_title");
        const auto messageWithAdditionalInfo = fmt::format("{}{}", Text::Get("logger_error_prefix_message"), message);

        const auto result = boxer::show(messageWithAdditionalInfo.c_str(), title.c_str(), boxer::Style::Error,
                                        boxer::Buttons::YesNo);

        if (result == boxer::Selection::No)
            exit(EXIT_FAILURE);
    }
}

std::string Logger::GeneratePrefix(const LoggerModes loggerLevel)
{
    std::string levelString;
    switch (loggerLevel)
    {
    case DEBUG_MODE:
        levelString = "DBG";
        break;
    case WARNING_MODE:
        levelString = "WRN";
        break;
    case ERROR_MODE:
        levelString = "ERR";
        break;
    }

    return fmt::format(FMT_COMPILE("{:%H:%M:%S}|{:s}"), fmt::localtime(std::time(nullptr)), levelString);
}

void Logger::LogToConsole(const std::string& message, const LoggerModes level)
{
#ifdef _WIN32
    if (!ColorsDisabledDueToError)
    {
        switch (level)
        {
        case DEBUG_MODE:
            ColorsDisabledDueToError = !SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_GREEN);
            break;
        case WARNING_MODE:
            ColorsDisabledDueToError = !SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_BLUE);
            break;
        case ERROR_MODE:
            ColorsDisabledDueToError = !SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);
            break;
        }

        if (ColorsDisabledDueToError)
            std::cout << "Logger colors disabled due to unknown error!" << std::endl;
    }

    std::cout << message << std::endl;
#else
    fmt::text_style style;
    switch (level)
    {
    case DEBUG_MODE:
        style = fg(fmt::color::green);
        break;
    case WARNING_MODE:
        style = fmt::emphasis::underline | fg(fmt::color::yellow);
        break;
    case ERROR_MODE:
        style = fmt::emphasis::bold | fg(fmt::color::red);
        break;
    }

    fmt::print(style, message);
    std::putc('\n', stdout);
#endif
}

void Logger::LogToFile(const std::string& message)
{
    *File << message << std::endl;
}
