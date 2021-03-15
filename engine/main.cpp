#include "common/debug/Logger.h"

int main()
{
    Logger::Initialize(true, false, "logs.txt", true, DEBUG);

    LOG_DEBUG("This is example debug 1");
    LOG_WARNING("This is example warning 1");
    LOG_ERROR("This is example error 1");
    LOG_ERROR("This is example error 2");

    Logger::Free();

    return 0;
}
