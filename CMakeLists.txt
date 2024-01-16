############## Include #######################
include(./.env.cmake OPTIONAL RESULT_VARIABLE LOCAL_ENV)

############## Setup Project #######################
cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_STANDARD 17)

set(NAME ToastGame)

project(${NAME} VERSION 1.0.0)

##############  Set Values  #######################
set(TARGET_NAME "${NAME}")
set(SOURCES_DIR "Source")

set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build/Deploy")

##############  Set Source Files  #######################
file(
    GLOB_RECURSE
    SOURCES

    # Source
    ${SOURCES_DIR}/**.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})

############## Set Property Balues  #######################
set_property(
    TARGET
    ${TARGET_NAME}
    PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY
    "${BUILD_DIR}"
)

set_property(
    TARGET
    ${TARGET_NAME}
    PROPERTY
    RUNTIME_OUTPUT_DIRECTORY
    "${BUILD_DIR}"
)

set_property(
    TARGET
    ${TARGET_NAME}
    PROPERTY
    RUNTIME_OUTPUT_DIRECTORY_DEBUG
    "${BUILD_DIR}"
)

set_property(
    TARGET
    ${TARGET_NAME}
    PROPERTY
    RUNTIME_OUTPUT_DIRECTORY_RELEASE
    "${BUILD_DIR}"
)

############## Linking Libs  #######################

find_package(Vulkan REQUIRED)

if (NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan not found")
endif()

target_include_directories(
    ${TARGET_NAME}
    PRIVATE

    # Source
    ${SOURCES_DIR}

    # Engine
    ${CHICANE_ENGINE_SOURCE_DIR}
    ${CHICANE_ENGINE_INCLUDE_DIR}/stb
)

if (WIN32)
    message(STATUS "CREATING BUILD FOR WINDOWS")

    if (USE_MINGW)
        target_include_directories(
            ${TARGET_NAME}
            PRIVATE

            ${MINGW_PATH}/include
        )

        target_link_directories(
            ${TARGET_NAME}
            PRIVATE

            ${MINGW_PATH}/lib
        )
    endif()

    target_include_directories(
        ${TARGET_NAME}
        PRIVATE

        # Source
        ${SOURCES_DIR}

        # Engine
        ${Vulkan_INCLUDE_DIRS}
    )

    target_link_directories(
        ${TARGET_NAME}
        PRIVATE

        $ENV{VULKAN_SDK}/Lib
    )

    target_link_directories(
        ${TARGET_NAME}
        PRIVATE

        vulkan-1
        SDL2
    )

    target_link_libraries(
        ${TARGET_NAME}
        PRIVATE

        # Engine
        ${CHICANE_ENGINE_LIB_DIR}/Engine.a

        # Vendor
        vulkan-1
        SDL2
    )
elseif(UNIX)
    message(STATUS "CREATING BUILD FOR UNIX")

endif()