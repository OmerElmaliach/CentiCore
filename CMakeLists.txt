# Define versions // REMINDER: UPDATE EACH CENTICORE VERSION WITH PULLS TO MAIN.
cmake_minimum_required(VERSION 3.16)
project(CentiCore VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

# Define and add executables.
file(GLOB VIEW_COMPONENTS
    "src/view/components/*.cpp"
    "src/view/components/include/*.h"
)

file(GLOB VIEW_UI
    "src/view/ui/*.ui"
)

qt_add_executable(CentiCore
    src/main.cpp
    ${VIEW_UI}
    ${VIEW_COMPONENTS}
)

qt_add_resources(CentiCoreResources resources/resources.qrc)
target_sources(CentiCore PRIVATE ${CentiCoreResources})

# QT Libraries.
target_link_libraries(CentiCore PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(CentiCore PRIVATE src)

set_target_properties(CentiCore PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
