#  _____  _      _   _  _____  _____  _   __        ______  _____
# /  __ \| |    | | | |/  ___||  ___|| | / /        | ___ \|_   _|
# | /  \/| |    | | | |\ `--. | |__  | |/ /  ______ | |_/ /  | |
# | |    | |    | | | | `--. \|  __| |    \ |______||    /   | |
# | \__/\| |____| |_| |/\__/ /| |___ | |\  \        | |\ \   | |
#  \____/\_____/ \___/ \____/ \____/ \_| \_/        \_| \_|  \_/

cmake_minimum_required(VERSION 3.19)

project(CLUSEK-RT VERSION 1.1.0)

if (NOT CMAKE_BUILD_TYPE)
    message("Build type is not defined! Falling back to the 'Debug' mode.")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_compile_definitions(WIN32_LEAN_AND_MEAN)
add_compile_definitions(NOMINMAX)
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
        engine/renderer/helpers/VulkanVersion.cpp
        engine/renderer/helpers/DebuggerCallback.h
        engine/renderer/helpers/DebuggerCallback.cpp
        engine/renderer/core/VulkanPhysicalDevice.cpp
        engine/renderer/core/VulkanPhysicalDevice.h
        engine/renderer/core/VulkanLogicalDevice.cpp
        engine/renderer/core/VulkanLogicalDevice.h
        engine/renderer/helpers/DeviceRequiredFeatures.cpp
        engine/renderer/helpers/DeviceRequiredFeatures.h
        engine/renderer/core/VulkanQueues.cpp
        engine/renderer/core/VulkanQueues.h
        engine/renderer/core/VulkanQueue.cpp
        engine/renderer/core/VulkanQueue.h
        engine/renderer/helpers/DebugExtender.cpp
        engine/renderer/helpers/DebugExtender.h
        engine/renderer/allocator/VulkanMemory.cpp
        engine/renderer/allocator/VulkanMemory.h
        engine/renderer/core/VulkanBuffer.cpp
        engine/renderer/core/VulkanBuffer.h
        engine/common/CommandLineArgumentsParser.cpp
        engine/common/CommandLineArgumentsParser.h
        engine/renderer/core/VulkanSurface.cpp
        engine/renderer/core/VulkanSurface.h
        engine/renderer/core/VulkanSwapChain.cpp
        engine/renderer/core/VulkanSwapChain.h
        engine/renderer/core/VulkanImage.cpp
        engine/renderer/core/VulkanImage.h
        engine/renderer/core/VulkanImageView.cpp
        engine/renderer/core/VulkanImageView.h
        engine/renderer/core/VulkanCommandBuffer.cpp
        engine/renderer/core/VulkanCommandBuffer.h
        engine/renderer/core/VulkanCommandPool.cpp
        engine/renderer/core/VulkanCommandPool.h
        engine/renderer/core/VulkanSemaphore.cpp
        engine/renderer/core/VulkanSemaphore.h
        engine/renderer/core/VulkanFence.cpp
        engine/renderer/core/VulkanFence.h
        engine/renderer/vertex/FatVertex.h
        engine/renderer/core/VulkanVertexBuffer.h
        engine/renderer/core/VulkanIndexBuffer.cpp
        engine/renderer/core/VulkanIndexBuffer.h
        engine/renderer/helpers/ImageMemoryBarrierBuilder.cpp
        engine/renderer/helpers/ImageMemoryBarrierBuilder.h
        engine/renderer/helpers/MemoryBarrierBuilder.cpp
        engine/renderer/helpers/MemoryBarrierBuilder.h
        engine/renderer/helpers/BufferMemoryBarrierBuilder.cpp
        engine/renderer/helpers/BufferMemoryBarrierBuilder.h
        engine/renderer/core/VulkanShaderModule.cpp
        engine/renderer/core/VulkanShaderModule.h
        engine/renderer/core/VulkanRasterizationPipeline.cpp
        engine/renderer/core/VulkanRasterizationPipeline.h
        engine/renderer/core/VulkanRayTracingPipeline.cpp
        engine/renderer/core/VulkanRayTracingPipeline.h
        engine/renderer/core/VulkanComputePipeline.cpp
        engine/renderer/core/VulkanComputePipeline.h
        engine/renderer/helpers/VertexBindingDescriptorGenerator.h
        engine/common/generators/VertexMacros.h
        engine/generated/VertexInputAttributeDescriptions.h
        engine/renderer/core/VulkanRenderPass.cpp
        engine/renderer/core/VulkanRenderPass.h
        engine/renderer/core/VulkanPipelineLayout.cpp
        engine/renderer/core/VulkanPipelineLayout.h
        engine/renderer/helpers/VulkanSubpass.h
        engine/renderer/helpers/RasterizationPipelineBuilder.cpp
        engine/renderer/helpers/RasterizationPipelineBuilder.h
        engine/renderer/core/VulkanFrameBuffer.cpp
        engine/renderer/core/VulkanFrameBuffer.h
        engine/renderer/core/VulkanPushConstantRanges.cpp
        engine/renderer/core/VulkanPushConstantRanges.h
        engine/math/PaddingCalculator.h)

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

add_compile_definitions(GLFW_INCLUDE_VULKAN)

# GLM

add_subdirectory(libraries/glm)

target_link_libraries(${PROJECT_NAME} glm)

include_directories(libraries/glm)

add_compile_definitions(GLM_FORCE_RADIANS)
add_compile_definitions(GLM_FORCE_DEPTH_ZERO_TO_ONE)

# Argh!

include_directories(libraries/argh)

#  _____              _         _
# /  ___|            (_)       | |
# \ `--.   ___  _ __  _  _ __  | |_  ___
#  `--. \ / __|| '__|| || '_ \ | __|/ __|
# /\__/ /| (__ | |   | || |_) || |_ \__ \
# \____/  \___||_|   |_|| .__/  \__||___/
#                       | |
#                       |_|

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND node ./scripts/js/format_json_files.js ./bin/
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND node ./scripts/js/compile_shaders.js ${Vulkan_GLSLC_EXECUTABLE} ./shaders/ ./bin/data/shaders/
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_command(
        OUTPUT ./engine/generated/ObjectSerializers.h
        COMMAND node ./scripts/js/generate_serializers.js ./engine/generated/ ObjectSerializers ./engine/
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_command(
        OUTPUT ./engine/generated/VertexInputAttributeDescriptions.h
        COMMAND node ./scripts/js/generate_vertex_attribute_descriptors.js ./engine/generated/ VertexInputAttributeDescriptions ./engine/
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND node ./scripts/js/redistribute_engine.js ./bin/ ${CMAKE_PROJECT_VERSION} ${CMAKE_PROJECT_NAME}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif ()