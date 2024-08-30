cmake_minimum_required(VERSION 3.10)

project(Server)

find_package(Boost REQUIRED COMPONENTS asio)

add_executable(server main.cpp)
target_link_libraries(server Boost::asio)