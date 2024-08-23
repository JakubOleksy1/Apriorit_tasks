cmake_minimum_required(VERSION 3.13)

project(MyQtApp)

set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Network Sql)

qt6_wrap_ui(UI_HEADERS MainWindow.ui)

qt6_wrap_cpp(MOC_SOURCES MainWindow.h)

include_directories(${CMAKE_BINARY_DIR})

add_executable(MyQtApp
    Factory_method.cpp 
    main.cpp 
    MainWindow.cpp 
    ${UI_HEADERS}
    ${MOC_SOURCES}
)

set_target_properties(MyQtApp PROPERTIES CXX_STANDARD 17)

if (MSVC)
    target_compile_options(MyQtApp PRIVATE /Zc:__cplusplus)
endif()

target_link_libraries(MyQtApp
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
)