#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include "camera.h"
#include "terrain.h"
#include "rover.h"
#include "background.h"
#include "../../utils/size.h"
#include "../../utils/rect.h"
#include "level/level.h"

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

    /// @brief Get the level
    Level& getLevel();

    /// @brief Get the camera
    const Camera& getCamera() const;

    /// @brief Shoot a bullet
    void shoot();

    /// @brief Gets the background
    /// @return The background
    const Background& getBackground() const;

    /// @brief Get the upward bullets
    std::vector<Rect> getUpwardBullets() const;

    /// @brief Get the speed the camera is moved to the right with
    float getCameraSpeed() const;

    /// @brief Get the terrain
    const Terrain& getTerrain() const;

    /// @brief Get the time spent in the current level
    /// @return The time spent in the current level in seconds
    const float getTimeInLevel() const;

    /// @brief Get the total points
    /// @return The total points
    const int getTotalPoints() const;

    /// @brief Get the points since the last checkpoint
    /// @return The points since the last checkpoint
    const int getPointsSinceLastCheckpoint() const;

    /// @brief Get the number of lives remaining before game over
    /// @return The number of lives remaining
    const int getLivesRemaining() const;

    /// @brief Get the last checkpoint
    /// @return The last checkpoint
    const char getLastCheckpoint() const;

    /// @brief Get the checkpoint where the last highscore was achieved
    /// @return The checkpoint where the last highscore was achieved
    const char getHighscoreCheckpoint() const;

    /// @brief Get whether an aerial attack is imminent
    /// @return Whether an aerial attack is imminent
    const bool getIsAerialAttackImminent() const;

    /// @brief Get whether a minefield is imminent
    /// @return Whether a minefield is imminent
    const bool getIsMinefieldImminent() const;

    /// @brief Get whether a terrain block is imminent
    /// @return Whether a terrain block is imminent
    const bool getIsTerrainBlockImminent() const;
private:
    std::vector<Rect> upward_bullets;
    std::vector<Rect> forward_bullets;

    Camera camera;

    Rover moonRover;

    Terrain terrain;

    Background background;

    Level level;

    float timeInLevel = 0.0f;

    float lastCraterPos = 0.0f;

    int totalPoints = 0;
    int pointsSinceLastCheckpoint = 0;
    int livesRemaining = 2;

    char lastCheckpoint = 'A';
    char highscoreCheckpoint = 'A';

    bool isAerialAttackImminent = false;
    bool isMinefieldImminent = false;
    bool isTerrainBlockImminent = false;

    /// @brief The speed of the moon rover in screen width multiples per second
    static constexpr float cameraSpeed = 0.33f;
};

#endif