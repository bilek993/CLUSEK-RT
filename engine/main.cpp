#include "common/debug/Logger.h"
#include "common/translations/Text.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG_MODE); // TODO: Make configurable
    Text::Initialize({
                             std::make_pair(ENGLISH, "./texts/english_strings.json"),
                             std::make_pair(POLISH, "./texts/polish_strings.json"),
                     }); // TODO: Make configurable
    Text::SetLanguage(POLISH); // TODO: Make configurable

    LOG_WARNING("Remove this line!!!"); // TODO: Remove this!
    LOG_ERROR("Remove this line!!!"); // TODO: Remove this!

    LOG_DEBUG("------------------"); // TODO: Remove this!
    LOG_DEBUG(Text::Get("example")); // TODO: Remove this!
    LOG_DEBUG("------------------"); // TODO: Remove this!

    Text::Free();
    Logger::Free();

    return 0;
}
