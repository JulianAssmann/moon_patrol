#include "view.h"

GameplayView::GameplayView(std::shared_ptr<SDL_Renderer> renderer) : 
    renderer(renderer), 
    roverSprite(Sprite("assets/rover.png", renderer)),
    mountainsForegroundSprite(Sprite("assets/mountains-foreground.png", renderer)),
    mountainsBackgroundSprite(Sprite("assets/mountains-background.png", renderer)),
    bulletSprite(Sprite("assets/bullet.png", renderer)),
    wheelSprite(Sprite("assets/wheel.png", renderer)),
    gameplayUI(GameplayUI(renderer)) { }

GameplayView::~GameplayView() { }

void GameplayView::init() {
    roverSprite.init();
    mountainsForegroundSprite.init();
    mountainsBackgroundSprite.init();
    bulletSprite.init();
    wheelSprite.init();
    gameplayUI.init();
}

void GameplayView::render(GameplayModel &model) {
    for (Rect background : model.getBackground().getForegroundMountains()) {
        this->mountainsBackgroundSprite.render(model.getCamera().worldToScreen(background));
    }
    for (Rect background : model.getBackground().getBackgroundMountains()) {
        this->mountainsForegroundSprite.render(model.getCamera().worldToScreen(background));
    }
    for (Rect terrain : model.getTerrain().getTerrainSegments()) {
        SDL_SetRenderDrawColor(renderer.get(), 252, 150, 79, 255);
        SDL_Rect rect = model.getCamera().worldToScreen(terrain).toSDLRect();
        SDL_RenderFillRect(renderer.get(), &rect);
    }

    roverSprite.render(model.getCamera().worldToScreen(model.getMoonRover().getRect()));
    for (Rect wheel : model.getMoonRover().getWheels()) {
        this->wheelSprite.render(model.getCamera().worldToScreen(wheel));
    }

    for (Rect bullet : model.getUpwardBullets()) {
        this->bulletSprite.render(model.getCamera().worldToScreen(bullet));
    }

    gameplayUI.render(model);
}