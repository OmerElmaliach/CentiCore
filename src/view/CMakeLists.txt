# Define versions // REMINDER: UPDATE EACH CENTICORE VERSION WITH PULLS TO MAIN.
cmake_minimum_required(VERSION 3.16)
project(CentiCore VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

# Define and add executables.
file(GLOB VIEW_COMPONENTS
    "components/*.cpp"
    "components/include/*.h"
)

file(GLOB VIEW_UI
    "ui/*.ui"
)

qt_add_resources(CentiCoreResources resources/resources.qrc)
qt_add_executable(CentiCore
    main.cpp
    ${VIEW_UI}
    ${VIEW_COMPONENTS}
    ${CentiCoreResources}
)

# QT Libraries.
target_link_libraries(CentiCore PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(CentiCore PRIVATE src)

set_target_properties(CentiCore PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
