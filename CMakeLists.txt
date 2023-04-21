cmake_minimum_required(VERSION 3.24)
project(moon_patrol LANGUAGES CXX)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

# Print some useful information about the build
Message( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
Message( STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )
Message( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )
Message( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )
Message( STATUS "CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME} )

# Find SDL2
find_package(SDL2 REQUIRED)
IF (${SDL2_FOUND})
    Message( STATUS "SDL2_INCLUDE_DIR:" ${SDL2_INCLUDE_DIR})
    Message( STATUS "SDL2_LIBRARY: " ${SDL2_LIBRARY})
ELSE()
    Message( FATAL_ERROR "SDL2 NOT FOUND" )
ENDIF()

# Find SDL2_image
FIND_PACKAGE(SDL2_IMAGE REQUIRED)
IF (${SDL2_IMAGE_FOUND})
    Message( STATUS "SDL2_IMAGE_INCLUDE_DIR: " ${SDL2_IMAGE_INCLUDE_DIR})
    Message( STATUS "SDL2_IMAGE_LIBRARY: " ${SDL2_IMAGE_LIBRARY})
ELSE()
    Message( FATAL_ERROR "SDL2_IMAGE NOT FOUND" )
ENDIF()

add_library(utils SHARED
    src/utils/vector2.h 
    src/utils/size.h 
    src/utils/rect.h
)
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(utils ${SDL2_LIBRARIES})

add_library(textures SHARED
    src/texture/sprite.h
    src/texture/sprite.cc
    src/texture/atlas_sprite.h
    src/texture/atlas_sprite.cc
    src/texture/texture_atlas.h
    src/texture/texture_atlas.cc
)
target_link_libraries(textures utils ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
set_target_properties(textures PROPERTIES LINKER_LANGUAGE CXX)

add_library(mvc SHARED
    src/mvc/scene.h
    src/mvc/game.h
    src/mvc/game.cc
)
target_link_libraries(mvc utils ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
set_target_properties(mvc PROPERTIES LINKER_LANGUAGE CXX)

add_library(game SHARED
    src/game/exit_game_controller.h
    src/game/gameplay_controller.h
    src/game/gameplay_controller.cc
    src/game/gameplay_model.h
    src/game/gameplay_model.cc
    src/game/gameplay_view.h
    src/game/gameplay_view.cc
    src/game/gameplay_scene.h
    src/game/gameplay_scene.cc
    src/game/camera.h
    src/game/camera.cc
    src/game/rover.h
    src/game/rover.cc
    src/game/terrain.h
    src/game/terrain.cc
)
target_link_libraries(game utils mvc textures ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
set_target_properties(game PROPERTIES LINKER_LANGUAGE CXX)

# Copy assets to runtime directory
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(${PROJECT_NAME} src/main.cc)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image utils textures mvc game)