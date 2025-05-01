cmake_minimum_required(VERSION 3.24)
project(anti_cheat_with_cpp_cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(third_party/abseil-cpp SYSTEM)
add_subdirectory(third_party/googletest SYSTEM)
add_subdirectory(third_party/spdlog SYSTEM)

add_subdirectory(src/common)
add_subdirectory(src/platform)
add_subdirectory(src/target)
add_subdirectory(src/app)
add_subdirectory(src/main)