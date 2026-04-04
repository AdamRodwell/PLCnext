cmake_minimum_required(VERSION 3.13)

project(Valves)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set (ArpProgramming_ARP_IO_PROFIBUS_LIBRARY FALSE)

file(GLOB_RECURSE Headers CONFIGURE_DEPENDS src/*.h src/*.hpp src/*.hxx)
file(GLOB_RECURSE PublicHeaders CONFIGURE_DEPENDS include/*.h include/*.hpp include/*.hxx)
file(GLOB_RECURSE Sources CONFIGURE_DEPENDS src/*.cpp)
add_library(${CMAKE_PROJECT_NAME} SHARED ${Headers} ${PublicHeaders} ${Sources})

string(REGEX REPLACE "^.*\\(([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+).*$" "\\1" _ARP_SHORT_DEVICE_VERSION ${ARP_DEVICE_VERSION})
set(INCLUDE_INSTALL_DIR ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/include)
set(LIB_INSTALL_DIR ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/lib/${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>)

list(INSERT CMAKE_MODULE_PATH 0 "${ARP_TOOLCHAIN_CMAKE_MODULE_PATH}")

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows" AND NOT "$ENV{SHELL}" MATCHES ".*[\/\\]bash($|.exe$)")
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "-Wl,-rpath,\$$ORIGIN")
else()
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES INSTALL_RPATH $ORIGIN)
endif()

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE LINKER:--no-undefined)

find_package(ArpDevice REQUIRED)
find_package(ArpProgramming REQUIRED)

find_package(Utils REQUIRED
    HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../Utils/bin/${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/cmake")

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${Utils_INCLUDE_DIR}>)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ArpDevice ArpProgramming Utils)

include(CMakePackageConfigHelpers)
configure_package_config_file(
  "Config.cmake.in"
  "${CMAKE_PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/cmake
  PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion)

file(GLOB _DEPLOY_HEADERS_AND_DIRS include/*)
set(_DIRS_TO_DEPLOY "")
set(_FILES_TO_DEPLOY "")
foreach(ITEM ${_DEPLOY_HEADERS_AND_DIRS})
   if(IS_DIRECTORY "${ITEM}")
      list(APPEND _DIRS_TO_DEPLOY "${ITEM}")
   endif()
endforeach()
install(DIRECTORY ${_DIRS_TO_DEPLOY} DESTINATION ${INCLUDE_INSTALL_DIR})
unset(_FILES_TO_DEPLOY)
unset(_DIRS_TO_DEPLOY)
unset(_DEPLOY_HEADERS_AND_DIRS)

install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${CMAKE_PROJECT_NAME}-targets DESTINATION ${LIB_INSTALL_DIR})
install(EXPORT ${CMAKE_PROJECT_NAME}-targets DESTINATION ${LIB_INSTALL_DIR})
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/cmake")
unset(_ARP_SHORT_DEVICE_VERSION)
