#  _____ ___  ___        _
# /  __ \|  \/  |       | |
# | /  \/| .  . |  __ _ | | __  ___
# | |    | |\/| | / _` || |/ / / _ \
# | \__/\| |  | || (_| ||   < |  __/
#  \____/\_|  |_/ \__,_||_|\_\ \___|

cmake_minimum_required(VERSION 3.17)

#  _____  _      _   _  _____  _____  _   __        ______  _____
# /  __ \| |    | | | |/  ___||  ___|| | / /        | ___ \|_   _|
# | /  \/| |    | | | |\ `--. | |__  | |/ /  ______ | |_/ /  | |
# | |    | |    | | | | `--. \|  __| |    \ |______||    /   | |
# | \__/\| |____| |_| |/\__/ /| |___ | |\  \        | |\ \   | |
#  \____/\_____/ \___/ \____/ \____/ \_| \_/        \_| \_|  \_/

project(CLUSEK-RT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
        CLUSEK-RT
        engine/main.cpp
        engine/common/debug/Logger.cpp
        engine/common/debug/Logger.h
        engine/common/debug/LoggerModes.h)

#  _      _  _                         _
# | |    (_)| |                       (_)
# | |     _ | |__   _ __   __ _  _ __  _   ___  ___
# | |    | || '_ \ | '__| / _` || '__|| | / _ \/ __|
# | |____| || |_) || |   | (_| || |   | ||  __/\__ \
# \_____/|_||_.__/ |_|    \__,_||_|   |_| \___||___/

# fmt

add_subdirectory(libraries/fmt)

target_link_libraries(CLUSEK-RT fmt::fmt)

include_directories(libraries/fmt/include)

# Boxer

add_subdirectory(libraries/Boxer)

target_link_libraries(CLUSEK-RT Boxer)

include_directories(libraries/Boxer/include)