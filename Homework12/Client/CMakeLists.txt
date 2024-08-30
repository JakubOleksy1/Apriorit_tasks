cmake_minimum_required(VERSION 3.10)

project(Client)

find_package(Boost REQUIRED COMPONENTS asio)

add_executable(client main.cpp)
target_link_libraries(client Boost::asio)