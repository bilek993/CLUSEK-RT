#include "common/debug/Logger.h"
#include "common/translations/Text.h"
#include "Engine.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG_MODE); // TODO: Make configurable
    Text::Initialize({
                             std::make_pair(ENGLISH, "./texts/english_strings.json"),
                             std::make_pair(POLISH, "./texts/polish_strings.json"),
                     }); // TODO: Make configurable
    Text::SetLanguage(ENGLISH); // TODO: Make configurable

    try
    {
        LOG_DEBUG("Preparing CLUSEK-RT engine...");

        Engine engine{};
        engine.Initialize();

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
