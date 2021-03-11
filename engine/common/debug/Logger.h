//
// Created by jbili on 11.03.2021.
//

#ifndef CLUSEK_RT_LOGGER_H
#define CLUSEK_RT_LOGGER_H

#include <string>

class Logger final
{
public:
    static void Initialize(bool enableConsoleLogging, bool enableFileLogging, const std::string& filePath, int level);
    static void Free();

private:
    inline static bool Initialized = false;

    inline static bool EnabledConsoleLogging = false;
    inline static bool EnabledFileLogging = false;

    inline static int LoggingLevel = 0;
};

#endif //CLUSEK_RT_LOGGER_H
