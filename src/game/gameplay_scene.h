#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <SDL2/SDL.h>
#include <memory>
#include "../mvc/scene.h"
#include "../mvc/game.h"
#include "gameplay_model.h"
#include "gameplay_view.h"
#include "gameplay_controller.h"

/// @brief The main scene
class GameplayScene : public Scene
{
public:
    GameplayScene(Game* game);
    ~GameplayScene();

    void init() override;
    void handleEvent(SDL_Event& event, float dt) override;
    void update(float dt) override;
    void render() override;
private:
    GameplayModel model;
    GameplayView view;
    GameplayController controller;
};

#endif