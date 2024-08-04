cmake_minimum_required(VERSION 3.13)

project(MyQtApp)

# Set the CMAKE_PREFIX_PATH to your Qt installation directory
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64")

# Find the required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Network Sql)

# Generate ui_MainWindow.h from MainWindow.ui
qt6_wrap_ui(UI_HEADERS MainWindow.ui)

# Generate moc_MainWindow.cpp from MainWindow.h
qt6_wrap_cpp(MOC_SOURCES MainWindow.h)

# Include the build directory to find the generated ui_MainWindow.h
include_directories(${CMAKE_BINARY_DIR})

# Add the executable target
add_executable(MyQtApp
    Factory_method.cpp 
    main.cpp 
    MainWindow.cpp 
    ${UI_HEADERS}
    ${MOC_SOURCES}
)

# Set the C++ standard to C++17
set_target_properties(MyQtApp PROPERTIES CXX_STANDARD 17)

# Add the /Zc:__cplusplus flag for MSVC
if (MSVC)
    target_compile_options(MyQtApp PRIVATE /Zc:__cplusplus)
endif()

# Link the libraries in the correct order
target_link_libraries(MyQtApp
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
)