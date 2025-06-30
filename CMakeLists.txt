cmake_minimum_required(VERSION 3.16)
project(CentiCore VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(CentiCore
    src/main.cpp
    src/gui/ui/main_interface.ui
    src/gui/components/main_interface.cpp
)

qt_add_resources(CentiCoreResources resources/resources.qrc)
target_sources(CentiCore PRIVATE ${CentiCoreResources})

target_link_libraries(CentiCore PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(CentiCore PRIVATE src)

set_target_properties(CentiCore PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
