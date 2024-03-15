# cmake-format: off
cmake_minimum_required(VERSION 3.17.0)

if(NOT CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_BUILD_TYPE Release)
endif()

project(rpi-monitor)
string(TIMESTAMP BUILD_TIME "%s")

###################
## CONFIGURATION ##
###################

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED BUILD_VERSION)
    set(BUILD_VERSION "0.0.0+${BUILD_TIME}")
endif()

#############
##  BUILD  ##
#############

add_executable(${PROJECT_NAME})

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        -Wall -Werror -Wpedantic -Weffc++
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/build
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        src/sensors/system.cpp

        src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
)
# cmake-format: on