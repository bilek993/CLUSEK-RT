//  _____  _____  _   _  _____ ______   ___   _____  _____ ______ 
// |  __ \|  ___|| \ | ||  ___|| ___ \ / _ \ |_   _||  ___||  _  \
// | |  \/| |__  |  \| || |__  | |_/ // /_\ \  | |  | |__  | | | |
// | | __ |  __| | . ` ||  __| |    / |  _  |  | |  |  __| | | | |
// | |_\ \| |___ | |\  || |___ | |\ \ | | | |  | |  | |___ | |/ /
//  \____/\____/ \_| \_/\____/ \_| \_|\_| |_/  \_/  \____/ |___/
//
// ---------------------------------------------------------------------------------------------------------------------
//
//                                                  Warning!
// Never modify this file by hand, because it's automatically generated by an external tool and will be overwritten.
//
// ---------------------------------------------------------------------------------------------------------------------

#ifndef CLUSEK_RT_OBJECTSERIALIZERS_H
#define CLUSEK_RT_OBJECTSERIALIZERS_H

#include <fstream>
#include <nlohmann/json.hpp>
#include <ostream>
#include <string>
#include <iomanip>

#include "..\common\ConfigData.h"

#define LOAD_PRIMITIVE_DATA_TO_FIELD(JSON, OBJECT, FIELD, TYPE) if (!JSON[#FIELD].is_null()) OBJECT.FIELD = JSON[#FIELD].get<TYPE>();
#define SAVE_PRIMITIVE_DATA_TO_JSON(JSON, OBJECT, FIELD) JSON[#FIELD] = OBJECT.FIELD;

namespace ObjectSerializers
{
    // DESERIALIZERS
    void Deserialize(std::ifstream& fileStream, ConfigData& object)
    {
        nlohmann::json json;
        fileStream >> json;

        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, LoggerPath, std::string);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, LoggerLevel, int);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, EnableLoggingToConsole, bool);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, EnableLoggingToFile, bool);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, ShowMessageBoxOnError, bool);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, TextEnglishPath, std::string);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, TextPolishPath, std::string);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, TextDefaultLanguageId, std::string);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, WindowName, std::string);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, WindowResizable, bool);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, WindowClosableWithX, bool);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, WindowedMode, bool);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, WindowWidth, int);
        LOAD_PRIMITIVE_DATA_TO_FIELD(json, object, WindowHeight, int);
    }

    // SERIALIZERS
    void Serialize(std::ofstream& fileStream, const ConfigData& object)
    {
        nlohmann::json json;

        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, LoggerPath);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, LoggerLevel);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, EnableLoggingToConsole);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, EnableLoggingToFile);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, ShowMessageBoxOnError);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, TextEnglishPath);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, TextPolishPath);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, TextDefaultLanguageId);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, WindowName);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, WindowResizable);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, WindowClosableWithX);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, WindowedMode);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, WindowWidth);
        SAVE_PRIMITIVE_DATA_TO_JSON(json, object, WindowHeight);

        fileStream << std::setw(3) << json;
    }
};

#endif //CLUSEK_RT_OBJECTSERIALIZERS_H