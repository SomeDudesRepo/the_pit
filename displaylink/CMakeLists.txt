set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
project(displaylink)

set(CMAKE_DEBUG_POSTFIX -d)
set(CMAKE_RELWITHDEBINFO_POSTFIX -rwdi)
set(CMAKE_MINSIZEREL_POSTFIX -msr)

if(UNIX)
  set(CMAKE_INCLUDE_SYSTEM_FLAG_C "-isystem ")
  set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-isystem ")
endif()

if(UNIX)
  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/lib/ )
  set(CMAKE_THREAD_PREFER_PTHREAD true)
  find_package(Threads REQUIRED)
  set(SYS_LIB ${CMAKE_THREAD_LIBS_INIT} rt)
endif()

include_directories(${PROJECT_SOURCE_DIR}/src)

###################################################################################################
# Set up all files as GLOBs                                                                       #
###################################################################################################
file(GLOB SOURCE_FILES_DISPLAYLINK_DIR "${PROJECT_SOURCE_DIR}/src/colourramp/*.cc")
file(GLOB HEADER_FILES_DISPLAYLINK_DIR "${PROJECT_SOURCE_DIR}/src/colourramp/*.h")
list(REMOVE_ITEM SOURCE_FILES_DISPLAYLINK_DIR "${PROJECT_SOURCE_DIR}/src/colourramp/main.cc")
set(ALL_FILES_DISPLAYLINK_DIR ${SOURCE_FILES_DISPLAYLINK_DIR} ${HEADER_FILES_DISPLAYLINK_DIR})

set(TEST_MAIN "${PROJECT_SOURCE_DIR}/src/colourramp/tests/test_main.cc")

file(GLOB SOURCE_FILES_DISPLAYLINK_TESTS_DIR "${PROJECT_SOURCE_DIR}/src/colourramp/tests/*.cc")
file(GLOB HEADER_FILES_DISPLAYLINK_TESTS_DIR "${PROJECT_SOURCE_DIR}/src/colourramp/tests/*.h")
set(ALL_FILES_DISPLAYLINK_TESTS_DIR ${SOURCE_FILES_DISPLAYLINK_TESTS_DIR} ${HEADER_FILES_DISPLAYLINK_TESTS_DIR})


###################################################################################################
# Define libraries and executables                                                       #
###################################################################################################
add_library(displaylink ${ALL_FILES_DISPLAYLINK_DIR})
add_executable(display_checker "${PROJECT_SOURCE_DIR}/src/colourramp/main.cc")
add_executable(TESTdisplaylink ${ALL_FILES_DISPLAYLINK_TESTS_DIR} ${TEST_MAIN})

target_link_libraries(displaylink ${SYS_LIB})
target_link_libraries(display_checker displaylink)
target_link_libraries(TESTdisplaylink displaylink gtest)

###################################################################################################
# Set compiler and linker flags                                                                   #
###################################################################################################
include(./standard_flags.cmake)

