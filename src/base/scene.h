#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>

class Game;

/// @brief A scene represents a single screen in the game (e. g. main menu, level)
/// @details A scene is responsible for handling events, updating and rendering
/// the game. A scene can be swapped out for another scene, which will cause the
/// game to switch to that scene.
class Scene {
public:
    /// @brief Create a scene
    /// @param game The game object
    Scene(Game* game) : game(game) {}

    /// @brief Destroy the scene
    virtual ~Scene() {}

    /// @brief Initialize the scene
    virtual void init() = 0;

    /// @brief Handle an event
    /// @param event The event to handle
    /// @param dt The delta time since the last update
    virtual void handleEvent(SDL_Event& event, float dt) = 0;

    /// @brief Update the scene
    /// @param dt The delta time since the last update
    virtual void update(float dt) = 0;

    /// @brief Render the scene
    virtual void render() = 0;

protected:
    /// @brief The game object
    Game* game;
};

#endif // SCENE_H