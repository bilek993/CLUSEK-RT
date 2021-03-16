#include "common/debug/Logger.h"
#include "common/translations/Text.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG); // TODO: Make configurable
    Text::Initialize({
                             std::make_pair("EN", "./texts/english_strings.json"),
                     }); // TODO: Make configurable
    Text::SetLanguage("EN"); // TODO: Make configurable

    Text::Free();
    Logger::Free();

    return 0;
}
