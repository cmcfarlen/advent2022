cmake_minimum_required(VERSION 3.23)
project(advent2022)

Include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        8.1.1
)
FetchContent_Declare(
        range-v3
        GIT_REPOSITORY "https://github.com/ericniebler/range-v3"
        GIT_TAG "0.12.0"
)

FetchContent_MakeAvailable(fmt range-v3)

set(CMAKE_CXX_STANDARD 23)

add_executable(advent2022 main.cpp)
target_link_libraries(advent2022 range-v3 fmt::fmt)
