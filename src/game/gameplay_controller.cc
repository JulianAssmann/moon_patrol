#include "gameplay_controller.h"

void GameplayController::init() {
    dt_since_last_shot = 0.0f;
}

void GameplayController::handleEvent(SDL_Event& event, GameplayModel& model, float dt) {
    dt_since_last_shot += dt;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_d:
                model.getMoonRover().driveFaster();
                break;
            case SDLK_a:
                model.getMoonRover().driveSlower();
                break;
            case SDLK_SPACE:
                if (dt_since_last_shot > shot_cooldown && !is_shooting) {
                    dt_since_last_shot = 0.0f;
                    model.shoot();
                    is_shooting = true;
                }
                break;
            case SDLK_j:
                model.getMoonRover().jump();
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_d:
            case SDLK_a:
                model.getMoonRover().driveNormally();
                break;
            case SDLK_SPACE:
                is_shooting = false;
                break;
        }
    }
}