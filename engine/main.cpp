#include "common/debug/Logger.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", DEBUG);
    Logger::Log(DEBUG, "test123");
    Logger::Free();

    return 0;
}
