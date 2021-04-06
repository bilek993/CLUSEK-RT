#  _____  _      _   _  _____  _____  _   __        ______  _____
# /  __ \| |    | | | |/  ___||  ___|| | / /        | ___ \|_   _|
# | /  \/| |    | | | |\ `--. | |__  | |/ /  ______ | |_/ /  | |
# | |    | |    | | | | `--. \|  __| |    \ |______||    /   | |
# | \__/\| |____| |_| |/\__/ /| |___ | |\  \        | |\ \   | |
#  \____/\_____/ \___/ \____/ \____/ \_| \_/        \_| \_|  \_/

cmake_minimum_required(VERSION 3.17)

project(CLUSEK-RT VERSION 1.0.0)

if (NOT CMAKE_BUILD_TYPE)
    message("Build type is not defined! Falling back to the 'Debug' mode.")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_compile_definitions(WIN32_LEAN_AND_MEAN)
add_compile_definitions(ENGINE_VERSION="${CMAKE_PROJECT_VERSION}")

add_executable(
        ${PROJECT_NAME}
        engine/main.cpp
        engine/common/debug/Logger.cpp
        engine/common/debug/Logger.h
        engine/common/debug/LoggerModes.h
        engine/common/StringUtil.cpp
        engine/common/StringUtil.h
        engine/common/translations/Text.cpp
        engine/common/translations/Text.h
        engine/common/translations/Language.h
        engine/Engine.cpp
        engine/Engine.h
        engine/common/ConfigData.h
        engine/common/generators/SerializationMacros.h
        engine/common/generators/CommonMacros.h
        engine/generated/ObjectSerializers.h
        engine/ecs/systems/RenderSystem.cpp
        engine/ecs/systems/RenderSystem.h
        engine/ecs/systems/BaseSystem.cpp
        engine/ecs/systems/BaseSystem.h
        engine/common/Timer.cpp
        engine/common/Timer.h
        engine/window/Window.cpp
        engine/window/Window.h
        engine/renderer/allocator/VulkanMemoryAllocatorImplementation.h
        engine/renderer/allocator/VulkanMemoryAllocatorImplementation.cpp
        engine/renderer/core/VulkanInstance.cpp
        engine/renderer/core/VulkanInstance.h
        engine/renderer/helpers/VulkanVersion.h
        engine/renderer/helpers/VulkanVersion.cpp)

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND node ./scripts/js/format_json_files.js ./bin/
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_command(
        OUTPUT ./engine/generated/ObjectSerializers.h
        COMMAND node ./scripts/js/generate_serializers.js ./engine/generated/ ObjectSerializers ./engine/
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND node ./scripts/js/redistribute_engine.js ./bin/ ${CMAKE_PROJECT_VERSION} ${CMAKE_PROJECT_NAME}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif ()

#  _      _  _                         _
# | |    (_)| |                       (_)
# | |     _ | |__   _ __   __ _  _ __  _   ___  ___
# | |    | || '_ \ | '__| / _` || '__|| | / _ \/ __|
# | |____| || |_) || |   | (_| || |   | ||  __/\__ \
# \_____/|_||_.__/ |_|    \__,_||_|   |_| \___||___/

# fmt

add_subdirectory(libraries/fmt)

target_link_libraries(${PROJECT_NAME} fmt::fmt)

include_directories(libraries/fmt/include)

# Boxer

add_subdirectory(libraries/Boxer)

target_link_libraries(${PROJECT_NAME} Boxer)

include_directories(libraries/Boxer/include)

# Nlohmann JSON

add_subdirectory(libraries/json)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

include_directories(libraries/json/include)

# EnTT

add_subdirectory(libraries/entt)

target_link_libraries(${PROJECT_NAME} EnTT)

include_directories(libraries/entt/single_include)

# Vulkan

find_package(Vulkan)

target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARY})

include_directories(${Vulkan_INCLUDE_DIR})

# Vulkan Memory Allocator

include_directories(libraries/VulkanMemoryAllocator/src)

# GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libraries/glfw)

target_link_libraries(${PROJECT_NAME} glfw)

include_directories(libraries/glfw/include)

# GLM

add_subdirectory(libraries/glm)

target_link_libraries(${PROJECT_NAME} glm)

include_directories(libraries/glm)
