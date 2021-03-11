//
// Created by jbili on 11.03.2021.
//

#include "Logger.h"

void Logger::Initialize(bool enableConsoleLogging, bool enableFileLogging, const std::string& filePath, int level)
{
    if (Initialized)
        return;

    EnabledConsoleLogging = enableConsoleLogging;
    EnabledFileLogging = enableFileLogging;

    Initialized = true;
}

void Logger::Free()
{
    EnabledConsoleLogging = false;
    EnabledFileLogging = false;

    Initialized = false;
}
