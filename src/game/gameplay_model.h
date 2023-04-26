#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include "camera.h"
#include "terrain.h"
#include "rover.h"
#include "../utils/size.h"
#include "../utils/rect.h"

class GameplayModel
{
public:
    /// @brief Create the model
    GameplayModel();

    /// @brief Initialize the model
    /// @param window_size The size of the window
    virtual void init(Size window_size);

    /// @brief Update the model with the given delta time
    /// @param dt The delta time since the last update
    virtual void update(float dt);

    /// @brief Get the rectangle for the moon rover
    Rover& getMoonRover();

    /// @brief Get the camera
    Camera getCamera() const;

    /// @brief Shoot a bullet
    void shoot();

    /// @brief Get the first layer background rectangles
    std::vector<Rect> getForegroundMountains() const;

    /// @brief Get the second layer background rectangles
    std::vector<Rect> getBackgroundMountains() const;

    /// @brief Get the upward bullets
    std::vector<Rect> getUpwardBullets() const;

    /// @brief Get the terrain
    const Terrain& getTerrain() const;
private:
    Rect mountainsForeground1;
    Rect mountainsForeground2;

    Rect mountainsBackground1;
    Rect mountainsBackground2;
    float parallax_factor = 0.5f;

    std::vector<Rect> upward_bullets;
    std::vector<Rect> forward_bullets;

    Camera camera;

    Rover moon_rover;

    Terrain terrain;

    float lastCraterPos = 0.0f;

    /// @brief The speed of the moon rover in screen width multiples per second
    static constexpr float camera_speed = 0.33f;
};

#endif