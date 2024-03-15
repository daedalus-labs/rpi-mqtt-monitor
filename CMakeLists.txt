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

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED VERSION)
    set(VERSION "0.0.0+${BUILD_TIME}")
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/driver_info.cpp.in
  ${CMAKE_BINARY_DIR}/generated/driver_info.cpp @ONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/data/rpi-monitor.service.in
    ${CMAKE_CURRENT_BINARY_DIR}/rpi-monitor.service
)

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
        generated/driver_info.cpp

        src/sensors/system.cpp

        src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
)

#############
## INSTALL ##
#############

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install (
    FILES ${CMAKE_CURRENT_BINARY_DIR}/fanshim-driver.service
    DESTINATION /etc/systemd/system/
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
)

set(CPACK_PACKAGE_VERSION "${VERSION}")
set(CPACK_PACKAGE_CONTACT "jporembski@contractor.swri.us")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Joe Porembski")
set(CPACK_PACKAGE_VENDOR "Daedalus Labs, LLC")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libuv1 (>= 1.43.0) libspdlog1 (>= 1.9.2)")
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
set(CPACK_RPM_PACKAGE_RELOCATABLE TRUE)
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION ${CMAKE_INSTALL_LIBDIR}/cmake)
include(CPack)

# cmake-format: on