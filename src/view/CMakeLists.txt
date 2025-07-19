cmake_minimum_required(VERSION 3.16)
project(CentiCore VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

file(GLOB VIEW_COMPONENTS "components/*.cpp" "components/include/*.h")
file(GLOB VIEW_UI "ui/*.ui")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/components/include/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h
)

qt_add_resources(CentiCoreResources resources/resources.qrc)

qt_add_executable(CentiCore
    view.cpp
    ${VIEW_UI}
    ${VIEW_COMPONENTS}
    ${CentiCoreResources}
)

target_include_directories(CentiCore PRIVATE 
    src
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)

target_link_libraries(CentiCore PRIVATE Qt6::Core Qt6::Widgets)

if(WIN32)
    set_target_properties(CentiCore PROPERTIES WIN32_EXECUTABLE ON)
elseif(APPLE)
    set_target_properties(CentiCore PROPERTIES MACOSX_BUNDLE ON)
endif()
