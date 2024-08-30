cmake_minimum_required(VERSION 3.10)
project(FileTransfer)

# Set the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/Boost/vcpkg-master/scripts/buildsystems/vcpkg.cmake")

add_subdirectory(client)
add_subdirectory(server)