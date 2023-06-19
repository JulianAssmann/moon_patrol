#ifndef GAMEPLAY_CONTROLLER_H
#define GAMEPLAY_CONTROLLER_H

#include <iostream>
#include <memory>
#include "../model/model.h"
#include "../../utils/size.h"
#include "../../utils/vector2.h"

class GameplayController {
public:
    /// @brief Initialize the controller
    void init();

    /// @brief Handle input
    /// @param model The model to update
    /// @param dt The delta time since the last update
    void handleEvent(SDL_Event& event, GameplayModel& model, float dt);
private:
    float dt_since_last_shot;
    bool is_shooting = false;
    const float shot_cooldown = 0.01f;
};

#endif // GAMEPLAY_CONTROLLER_H