# <== Project properties ===>
cmake_minimum_required(VERSION 3.16)
project(CentiCore VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

# <== UI Setup ===>
file(GLOB VIEW_COMPONENTS "view/components/*.cpp" "view/components/include/*.hpp")
file(GLOB VIEW_UI "view/ui/*.ui")
file(GLOB UTILS "utils/*.cpp" "utils/*.hpp")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/view/components/include/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h
)

qt_add_resources(CentiCoreResources view/resources/resources.qrc)
qt_add_executable(centicore_ui
    view/view.cpp
    ${VIEW_UI}
    ${VIEW_COMPONENTS}
    ${UTILS}
    ${CentiCoreResources}
)

# <== UI Library linking ===>
target_include_directories(centicore_ui PRIVATE 
    src
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)
target_link_libraries(centicore_ui PRIVATE Qt6::Core Qt6::Widgets)


# <== Backend Setup ===>
qt_add_executable(centicore_backend
    main.cpp
    ${UTILS}
)

# <== Backend Library linking ===>
target_include_directories(centicore_backend PRIVATE 
    src
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)

target_link_libraries(centicore_backend PRIVATE Qt6::Core)

if(WIN32)
    set_target_properties(centicore_ui PROPERTIES WIN32_EXECUTABLE ON)
    set_target_properties(centicore_backend PROPERTIES WIN32_EXECUTABLE ON)
elseif(APPLE)
    set_target_properties(centicore_ui PROPERTIES MACOSX_BUNDLE ON)
    set_target_properties(centicore_backend PROPERTIES MACOSX_BUNDLE ON)
endif()
