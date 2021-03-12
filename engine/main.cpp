#include "common/debug/Logger.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG);
    Logger::Log(ERROR, "test123");
    Logger::Free();

    return 0;
}
