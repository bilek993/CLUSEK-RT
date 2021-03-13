#include "common/debug/Logger.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG);
    Logger::Log(ERROR, "This is example error 1", __FILE__, __FUNCTION__, __LINE__);
    Logger::Log(ERROR, "This is example error 2", __FILE__, __FUNCTION__, __LINE__);
    Logger::Free();

    return 0;
}
