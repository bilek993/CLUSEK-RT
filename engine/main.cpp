#include "common/debug/Logger.h"
#include "common/translations/Text.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG); // TODO: Make configurable
    Text::Initialize(); // TODO: Make configurable

    Logger::Free();

    return 0;
}
