cmake_minimum_required(VERSION 3.24...3.30)
project(raylib-game-template)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 6.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

# Our Project
set(SOURCES
        src/main.cpp
        src/GameState/GameState.h
        src/GameState/GameState.cpp
        src/Menu/Menu.h
        src/Menu/Menu.cpp
        src/Game/Game.h
        src/Game/Game.cpp
        src/Grid/Grid.h
        src/Grid/Grid.cpp
        src/UI/Hotbar/Hotbar.cpp
        src/UI/Hotbar/Hotbar.h
        src/Grid/Tile.h
        src/Grid/Tile.cpp
        src/AssetManager/AssetManager.h
        src/AssetManager/AssetManager.cpp
        src/Game/Spawner.h
        src/Game/Spawner.cpp
        src/GameOver/GameOver.h
        src/GameOver/GameOver.cpp
        src/UI/Button/Button.h
        src/UI/Button/Button.cpp
        src/GameWin/GameWin.h
        src/GameWin/GameWin.cpp
        src/Progress/Progress.h
        src/Progress/Progress.cpp
        src/UI/TableElement/TableElement.h
        src/UI/TableElement/TableElement.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
add_subdirectory(src)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if ("${PLATFORM}" STREQUAL "Web")
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/../resources
    )
    #DEPENDS ${PROJECT_NAME}
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    )
    #DEPENDS ${PROJECT_NAME}
endif()

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC
            -sUSE_GLFW=3
            --preload-file resources
    )
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
