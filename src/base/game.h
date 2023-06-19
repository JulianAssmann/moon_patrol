#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <iostream>
#include <algorithm>
#include "./scene.h"
#include "../utils/size.h"

class Game {
public:
    /// @brief Create a game
    /// @param title The title of the game window
    /// @param screenWidth The width of the game window
    /// @param screenHeight The height of the game window
    Game(const char* title, Size screenSize, uint targetFps = 60);

    /// @brief Destroy the game
    ~Game();

    /// @brief Set the current scene
    /// @param scene The scene to set
    void setScene(Scene* scene);

    /// @brief Get the screen size
    Size getScreenSize();

    /// @brief Exit the game
    void exitGame();

    /// @brief Run the game loop until the game is over
    void run();

    /// @brief Get the renderer the game is rendered with
    std::shared_ptr<SDL_Renderer> get_renderer() { return renderer; }

    /// @brief Get the window the game is rendered in
    std::shared_ptr<SDL_Window> get_window() { return window; }

private:
    /// @brief Initialize SDL
    void init_sdl();

    /// @brief Handle events
    void handleEvent(SDL_Event event, float dt);

    /// @brief Update the game
    void update(float dt);

    /// @brief Clear the screen
    void clearScreen();

    /// @brief Render the game
    void render();

    /// @brief The title of the game window
    const char* title;

    /// @brief The size of the game window
    Size screen_size;

    /// @brief Whether the game is running
    bool is_running;

    /// @brief The renderer the game is rendered with
    std::shared_ptr<SDL_Renderer> renderer = nullptr;

    /// @brief The window the game is rendered in
    std::shared_ptr<SDL_Window> window = nullptr;

    /// @brief The current scene of the game
    Scene* currentScene = nullptr;

    /// @brief The target framerate
    uint targetFps;

    /// @brief The time between frames
    uint targetFrameTime;
};

#endif // !GAME_H