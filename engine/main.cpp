#include "common/debug/Logger.h"
#include "common/translations/Text.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG_MODE); // TODO: Make configurable
    Text::Initialize({
                             std::make_pair(ENGLISH, "./texts/english_strings.json"),
                             std::make_pair(POLISH, "./texts/polish_strings.json"),
                     }); // TODO: Make configurable
    Text::SetLanguage(ENGLISH); // TODO: Make configurable

    Text::Free();
    Logger::Free();

    return 0;
}
