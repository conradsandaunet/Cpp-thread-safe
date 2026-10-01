cmake_minimum_required(VERSION 3.14)
project(thread_safe_queue)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
# Usage: cmake .. -DENABLE_ASAN=ON
option(ENABLE_ASAN "Build with AddressSanitizer + UndefinedBehaviorSanitizer" OFF)
 
find_package(Threads REQUIRED)
 
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)
 
add_executable(tests tests/test_thread_safe_queue.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE Threads::Threads Catch2::Catch2WithMain)
 
if(ENABLE_ASAN)
    message(STATUS "AddressSanitizer + UBSan enabled")
    target_compile_options(tests PRIVATE -fsanitize=address,undefined -g -O0)
    target_link_options(tests PRIVATE -fsanitize=address,undefined)
endif()
 
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
