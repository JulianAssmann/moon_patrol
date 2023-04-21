#include "gameplay_scene.h"

GameplayScene::GameplayScene(Game* game) : 
    Scene(game), 
    model(GameplayModel()), 
    controller(GameplayController()), 
    view(GameplayView(game->get_renderer()))
{ }

GameplayScene::~GameplayScene() { }

void GameplayScene::init() {
    controller.init();
    model.init(game->getScreenSize());
    view.init();
}

void GameplayScene::handleEvent(SDL_Event& event, float dt) {
    controller.handleEvent(event, model, dt);
}

void GameplayScene::update(float dt) {
    model.update(dt);
}

void GameplayScene::render() {
    view.render(model);
}