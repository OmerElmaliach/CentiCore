# <== Project properties ===>
cmake_minimum_required(VERSION 3.16)
project(CentiCore VERSION 0.1.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

# <== General Setup ===>
file(GLOB UTILS "utils/*.cpp" "utils/*.hpp")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h
)

# <== View Classes ===>
file(GLOB VIEW_COMPONENTS "view/components/*.cpp" "view/components/include/*.hpp")
file(GLOB VIEW_UI "view/ui/*.ui")

# <== Model Classes ===>
file(GLOB MODEL_TYPES "model/types/*.cpp" "model/types/include/*.hpp")

# <== Controller Classes ===>
file(GLOB CONTROLLERS "controller/*.cpp" "controller/include/*.hpp")

qt_add_resources(RESOURCES view/resources/resources.qrc)
qt_add_executable(centicore
    main.cpp
    ${VIEW_UI}
    ${VIEW_COMPONENTS}
    ${MODEL_TYPES}
    ${CONTROLLERS}
    ${UTILS}
    ${RESOURCES}
)

# <== Library linking ===>
target_include_directories(centicore PRIVATE
    src
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)
target_link_libraries(centicore PRIVATE Qt6::Core Qt6::Widgets)

if(WIN32)
    set_target_properties(centicore PROPERTIES WIN32_EXECUTABLE ON)
elseif(APPLE)
    set_target_properties(centicore PROPERTIES MACOSX_BUNDLE ON)
endif()
