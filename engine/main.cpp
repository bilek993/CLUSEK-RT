#include "common/debug/Logger.h"
#include "common/translations/Text.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG); // TODO: Make configurable
    Text::Initialize({
                             std::make_pair("EN", "./texts/english_strings.json"),
                             std::make_pair("PL", "./texts/polish_strings.json"),
                     }); // TODO: Make configurable
    Text::SetLanguage("EN"); // TODO: Make configurable

    LOG_DEBUG("------------------"); // TODO: Remove this!
    LOG_DEBUG(Text::Get("example")); // TODO: Remove this!
    LOG_DEBUG("------------------"); // TODO: Remove this!

    Text::Free();
    Logger::Free();

    return 0;
}
