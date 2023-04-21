#ifndef ROVER_H
#define ROVER_H

#include <vector>
#include "../utils/rect.h"
#include "../utils/vector2.h"

class GameplayModel;

class Rover {
public:
    /// @brief Initialize the moon rover
    Rover(Rect rect, float velocity = 0.15f);

    /// @brief Get the rectangle for the moon rover
    const Rect& getRect() const;

    /// @brief Get the wheels of the rover
    const std::vector<Rect>& getWheels() const;

    /// @brief Initialize the rover
    void init(const Rect& rect, const GameplayModel& model);

    /// @brief Drive the moon rover faster
    void driveFaster();

    /// @brief Drive the moon rover slower
    void driveSlower();

    /// @brief Drive the moon rover slower
    void driveNormally();

    /// @brief Return the velocity of the rover
    float getCurrentVelocity() const;

    /// @brief Update the rover
    void update(float dt, const GameplayModel& model);
private:
    void updateWheels(const GameplayModel& model);

    Rect rect;
    std::vector<Rect> wheels;
    float additional_velocity = 0;
    float velocity;
    const float wheelHeight = 0.035f;
    const float wheelWidth = 0.03f;
};

#endif // ROVER_H
