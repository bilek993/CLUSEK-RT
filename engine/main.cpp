#include "common/debug/Logger.h"

int main()
{
    Logger::Initialize(false, true, "logs.txt", DEBUG);
    Logger::Log(DEBUG, "test123");
    Logger::Free();

    return 0;
}
