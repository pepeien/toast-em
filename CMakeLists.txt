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
set(BUILD_DIR   "${CMAKE_SOURCE_DIR}/Bin/${CMAKE_SYSTEM_NAME}")

set(CONTENT_TARGET_NAME "Content")
set(CONTENT_SOURCE_DIR  "${PROJECT_SOURCE_DIR}/Content")
set(CONTENT_BUILD_DIR   "${BUILD_DIR}/Content")

##############  Add subdirectories  #######################
add_subdirectory(Content)

add_subdirectory(Vendor/chicane)

##############  Set Source Files  #######################
file(
    GLOB_RECURSE
    SOURCES

    ${SOURCES_DIR}/**.cpp
)

add_executable(${TARGET_NAME} "")

target_sources(
    ${TARGET_NAME}

    PRIVATE
        ${SOURCES}
)

############## Set Property Balues  #######################
set_target_properties(
    ${TARGET_NAME}
    PROPERTIES

    VS_DEBUGGER_WORKING_DIRECTORY
    "${BUILD_DIR}"

    RUNTIME_OUTPUT_DIRECTORY
    "${BUILD_DIR}"

    RUNTIME_OUTPUT_DIRECTORY_DEBUG
    "${BUILD_DIR}"

    RUNTIME_OUTPUT_DIRECTORY_RELEASE
    "${BUILD_DIR}"
)

############## Linking Libs  #######################
if (WIN32)
    if (USE_MINGW)
        target_include_directories(
            ${TARGET_NAME}
            PUBLIC

            ${MINGW_PATH}/include
        )

        target_link_directories(
            ${TARGET_NAME}
            PUBLIC

            ${MINGW_PATH}/lib
        )
    endif()
endif()

target_include_directories(
    ${TARGET_NAME}

    PRIVATE
        ${SOURCES_DIR}

        Chicane
)

target_link_libraries(
    ${TARGET_NAME}

    PRIVATE
        Chicane
)