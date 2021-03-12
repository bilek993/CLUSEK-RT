#include "common/debug/Logger.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG);
    Logger::Log(ERROR, "Error1");
    Logger::Log(ERROR, "Error2");
    Logger::Free();

    return 0;
}
