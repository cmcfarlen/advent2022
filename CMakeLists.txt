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


add_executable(day1 day1.cpp util.cpp)
target_link_libraries(day1 range-v3 fmt::fmt)
add_executable(day2 day2.cpp util.cpp)
target_link_libraries(day2 range-v3 fmt::fmt)
add_executable(day3 day3.cpp util.cpp)
target_link_libraries(day3 range-v3 fmt::fmt)
