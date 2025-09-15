# <== Project properties ===>
cmake_minimum_required(VERSION 3.16)
project(CentiCore VERSION 0.6.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)
qt_standard_project_setup()

# <== General Setup ===>
file(GLOB UTILS "utils/*.cpp" "utils/*.hpp")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h
)

# <== View Classes ===>
file(GLOB VIEW_COMPONENTS "view/components/pages/*.cpp" "view/components/dialogs/*.cpp" "view/components/*.cpp" "view/components/include/*.hpp")
file(GLOB VIEW_UI "view/ui/*.ui")

# <== Model Classes ===>
file(GLOB MODELS "model/*.cpp" "model/include/*.hpp")

# <== Controller Classes ===>
file(GLOB CONTROLLERS "controller/*.cpp" "controller/include/*.hpp")

# <== ApiServices Classes ===>
file(GLOB SERVICES "services/*.cpp" "services/include/*.hpp")

# <== Resources ===>
qt_add_resources(RESOURCES "view/resources/resources.qrc")

# <== Compile ===>
qt_add_executable(centicore
    main.cpp
    ${VIEW_UI}
    ${VIEW_COMPONENTS}
    ${MODELS}
    ${CONTROLLERS}
    ${SERVICES}
    ${UTILS}
    ${RESOURCES}
)

# <== Library linking ===>
target_include_directories(centicore PRIVATE
    src
    ${CMAKE_CURRENT_BINARY_DIR}/generated
    ${PROJECT_SOURCE_DIR}/utils/include
    ${PROJECT_SOURCE_DIR}/view/components/include
    ${PROJECT_SOURCE_DIR}/controller/include
    ${PROJECT_SOURCE_DIR}/model/include
    ${PROJECT_SOURCE_DIR}/services/include
)
target_link_libraries(centicore PRIVATE Qt6::Core Qt6::Widgets Qt6::Network)

if(WIN32)
    set_target_properties(centicore PROPERTIES WIN32_EXECUTABLE ON)
elseif(APPLE)
    set_target_properties(centicore PROPERTIES MACOSX_BUNDLE ON)
endif()
