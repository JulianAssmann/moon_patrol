#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <SDL2/SDL.h>
#include <memory>
#include "../base/scene.h"
#include "../base/game.h"
#include "model/model.h"
#include "view/view.h"
#include "controller/controller.h"

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