//
// Created by jbili on 19.03.2021.
//

#ifndef CLUSEK_RT_CONFIGDATA_H
#define CLUSEK_RT_CONFIGDATA_H

#include "generators/SerializationMacros.h"

SERIALIZE_OBJECT(ConfigData)
struct ConfigData final
{
    SERIALIZE_FIELD(LoggerPath, std::string)
    std::string LoggerPath{};

    SERIALIZE_FIELD(LoggerLevel, int)
    int LoggerLevel = 0;

    SERIALIZE_FIELD(EnableLoggingToConsole, bool)
    bool EnableLoggingToConsole = false;

    SERIALIZE_FIELD(EnableLoggingToFile, bool)
    bool EnableLoggingToFile = false;

    SERIALIZE_FIELD(ShowMessageBoxOnError, bool)
    bool ShowMessageBoxOnError = true;

    SERIALIZE_FIELD(TextEnglishPath, std::string)
    std::string TextEnglishPath{};

    SERIALIZE_FIELD(TextPolishPath, std::string)
    std::string TextPolishPath{};

    SERIALIZE_FIELD(TextDefaultLanguageId, std::string)
    std::string TextDefaultLanguageId = "E";

    SERIALIZE_FIELD(WindowName, std::string)
    std::string WindowName = "Unnamed Project";

    SERIALIZE_FIELD(WindowResizable, bool)
    bool WindowResizable = false;

    SERIALIZE_FIELD(WindowClosableWithX, bool)
    bool WindowClosableWithX = true;

    SERIALIZE_FIELD(WindowedMode, bool)
    bool WindowedMode = true;

    SERIALIZE_FIELD(WindowWidth, int)
    int WindowWidth = 800;

    SERIALIZE_FIELD(WindowHeight, int)
    int WindowHeight = 600;
};

#endif //CLUSEK_RT_CONFIGDATA_H
