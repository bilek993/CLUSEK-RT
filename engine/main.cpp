#include <argh.h>

#include "common/debug/Logger.h"
#include "common/translations/Text.h"
#include "Engine.h"
#include "common/ConfigData.h"
#include "generated/ObjectSerializers.h"

int main(int argc, char* argv[])
{
    const auto commandLineArguments = argh::parser(argc, argv);

    std::string configurationFilePath;

    commandLineArguments("config-file", "./data/configuration.json") >> configurationFilePath;

    const auto configurationData = std::make_shared<ConfigData>();
    std::ifstream configurationFile(configurationFilePath);
    ObjectSerializers::Deserialize(configurationFile, *configurationData);

    Logger::Initialize(configurationData->EnableLoggingToConsole,
                       configurationData->EnableLoggingToFile,
                       configurationData->LoggerPath,
                       configurationData->ShowMessageBoxOnError,
                       static_cast<LoggerModes>(configurationData->LoggerLevel));

    Text::Initialize({
                             std::make_pair(ENGLISH, configurationData->TextEnglishPath),
                             std::make_pair(POLISH, configurationData->TextPolishPath),
                     });
    Text::SetLanguage(static_cast<Language>(configurationData->TextDefaultLanguageId[0]));

    try
    {
        LOG_DEBUG("Preparing CLUSEK-RT engine...");

        Engine engine{};
        engine.Initialize(configurationData);

        while (engine.ShouldUpdate())
            engine.Update();

        LOG_DEBUG("Finishing CLUSEK-RT engine...");
    }
    catch (const std::exception& e)
    {
        LOG_ERROR(e.what());
    }
    catch (...)
    {
        LOG_ERROR("Something unexpected and unknown happened in the engine!");
    }

    Text::Free();
    Logger::Free();

    return 0;
}
