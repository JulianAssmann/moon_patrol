cmake_minimum_required(VERSION 3.24)
project(moon_patrol LANGUAGES CXX)

# Set C++ standard to C++17
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

# Find SDL2_TTF
FIND_PACKAGE(SDL2_TTF REQUIRED)
IF (${SDL2_TTF_FOUND})
    Message( STATUS "SDL2_TTF_INCLUDE_DIR: " ${SDL2_TTF_INCLUDE_DIR})
    Message( STATUS "SDL2_TTF_LIBRARY: " ${SDL2_TTF_LIBRARY})
ELSE()
    Message( FATAL_ERROR "SDL2_TTF NOT FOUND" )
ENDIF()

add_library(utils SHARED
    src/utils/vector2.h
    src/utils/size.h
    src/utils/rect.h
)
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(utils ${SDL2_LIBRARIES})

add_library(assets SHARED
    src/assets/sprite.h
    src/assets/sprite.cc
    src/assets/atlas_sprite.h
    src/assets/atlas_sprite.cc
    src/assets/texture_atlas.h
    src/assets/texture_atlas.cc
    src/assets/font.h
    src/assets/font.cc
)
target_link_libraries(assets utils ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
set_target_properties(assets PROPERTIES LINKER_LANGUAGE CXX)

add_library(base SHARED
    src/base/scene.h
    src/base/game.h
    src/base/game.cc
)
target_link_libraries(base utils ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
set_target_properties(base PROPERTIES LINKER_LANGUAGE CXX)

add_library(gameplay SHARED
    src/gameplay/gameplay_scene.h
    src/gameplay/gameplay_scene.cc

    src/gameplay/controller/controller.h
    src/gameplay/controller/controller.cc

    src/gameplay/model/model.h
    src/gameplay/model/model.cc
    src/gameplay/model/camera.h
    src/gameplay/model/camera.cc
    src/gameplay/model/rover.h
    src/gameplay/model/rover.cc
    src/gameplay/model/terrain.h
    src/gameplay/model/terrain.cc
    src/gameplay/model/background.h
    src/gameplay/model/background.cc

    src/gameplay/model/level/level.h
    src/gameplay/model/level/level.cc
    src/gameplay/model/level/level_entity.h
    src/gameplay/model/level/level_entity.cc
    src/gameplay/model/level/bomber.h
    src/gameplay/model/level/bomber.cc

    src/gameplay/view/view.h
    src/gameplay/view/view.cc
    src/gameplay/view/ui.h
    src/gameplay/view/ui.cc
)
target_link_libraries(gameplay utils base assets ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
set_target_properties(gameplay PROPERTIES LINKER_LANGUAGE CXX)

# Copy assets to runtime directory
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(${PROJECT_NAME} src/main.cc)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf utils assets base gameplay)