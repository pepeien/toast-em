############## Include #######################
include(./.env.cmake OPTIONAL RESULT_VARIABLE LOCAL_ENV)

############## Setup Project #######################
cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_STANDARD 17)

set(NAME ToastGame)

project(${NAME} VERSION 1.0.0)

##############  Set Values  #######################
set(TARGET_NAME "${NAME}")
set(SOURCES_DIR "${PROJECT_SOURCE_DIR}/Source")
set(BUILD_DIR   "${CMAKE_SOURCE_DIR}/Bin")

set(CONTENT_TARGET_NAME "Content")
set(CONTENT_SOURCE_DIR  "${PROJECT_SOURCE_DIR}/Content")
set(CONTENT_BUILD_DIR   "${BUILD_DIR}/Content")

set(VENDOR_SOURCE_DIR "${PROJECT_SOURCE_DIR}/Vendor")

##############  Set Source Files  #######################
file(
    GLOB_RECURSE
    SOURCES

    # Source
    ${SOURCES_DIR}/**.cpp

    # Vendor
    ${VENDOR_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${VENDOR_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${VENDOR_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${VENDOR_SOURCE_DIR}/imgui/imgui.cpp
    ${VENDOR_SOURCE_DIR}/imgui/backends/imgui_impl_sdl2.cpp
    ${VENDOR_SOURCE_DIR}/imgui/backends/imgui_impl_vulkan.cpp
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

    # Vendor
    ${VENDOR_SOURCE_DIR}
    ${VENDOR_SOURCE_DIR}/imgui
    ${VENDOR_SOURCE_DIR}/pugixml/src

    # Engine
    ${CHICANE_SOURCE_DIR}
    ${CHICANE_SOURCE_DIR}/Runtime
    ${CHICANE_SOURCE_DIR}/Vendor
)

target_link_directories(   
    ${TARGET_NAME}
    PRIVATE

    # Vendor
    ${VENDOR_SOURCE_DIR}/pugixml/build

    # Engine
    ${CHICANE_LIB_DIR}
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE

    # Vendor
    pugixml

    # Engine
    Runtime
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

        # Engine Vendor
        ${Vulkan_INCLUDE_DIRS}
        ${Vulkan_INCLUDE_DIRS}/SDL2
    )

    target_link_directories(
        ${TARGET_NAME}
        PRIVATE

        # Engine Vendor
        $ENV{VULKAN_SDK}/Lib
    )

    target_link_libraries(
        ${TARGET_NAME}
        PRIVATE

        # Engine Vendor
        vulkan-1
        SDL2
    )
elseif(UNIX)
    message(STATUS "CREATING BUILD FOR UNIX")

    find_package(SDL2 REQUIRED)

    target_link_libraries(
        ${TARGET_NAME}
        PRIVATE

        # Vendor
        vulkan
        SDL2::SDL2
    )
endif()

add_subdirectory(Content)