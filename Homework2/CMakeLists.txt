cmake_minimum_required(VERSION 3.30)

project(CounterExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64")

find_package(Qt6Core REQUIRED)

add_executable(CounterExample
    main.cpp
    counter.cpp
)

target_link_libraries(CounterExample Qt6::Core)

set_target_properties(CounterExample PROPERTIES
    AUTOMOC ON
)