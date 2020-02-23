cmake_minimum_required(VERSION 3.15)
project(CroMaCk)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON #Only for .ui files
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Tell cmake where Qt is located
set(Qt5_DIR "~/mansion/zander/Qt/5.12.2/clang_64/lib/cmake/Qt5")
# Tell cmake to find the modules Qt5Core and Qt5widgets
find_package(Qt5 COMPONENTS Core Widgets Quick REQUIRED)

add_executable(CroMaCk main.cpp mainwindow.cpp mainwindow.hpp qml.qrc)

# Link the Qt libraries to the executable
target_link_libraries(CroMaCk Qt5::Core Qt5::Widgets Qt5::Quick)

