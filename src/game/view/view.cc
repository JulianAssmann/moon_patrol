#include "view.h"

GameplayView::GameplayView(std::shared_ptr<SDL_Renderer> renderer) : 
    renderer(renderer), 
    rover_sprite(Sprite("assets/rover.png", renderer)),
    mountains_foreground_sprite(Sprite("assets/mountains-foreground.png", renderer)),
    mountains_background_sprite(Sprite("assets/mountains-background.png", renderer)),
    bullet_sprite(Sprite("assets/bullet.png", renderer)),
    wheel_sprite(Sprite("assets/wheel.png", renderer)) { }

GameplayView::~GameplayView() { }

void GameplayView::init() {
    rover_sprite.init();
    mountains_foreground_sprite.init();
    mountains_background_sprite.init();
    bullet_sprite.init();
    wheel_sprite.init();
}

void GameplayView::render(GameplayModel &model) {
    for (Rect background : model.getBackground().getForegroundMountains()) {
        this->mountains_background_sprite.render(model.getCamera().worldToScreen(background));
    }
    for (Rect background : model.getBackground().getBackgroundMountains()) {
        this->mountains_foreground_sprite.render(model.getCamera().worldToScreen(background));
    }
    for (Rect terrain : model.getTerrain().getTerrainSegments()) {
        SDL_SetRenderDrawColor(renderer.get(), 252, 150, 79, 255);
        SDL_Rect rect = model.getCamera().worldToScreen(terrain).toSDLRect();
        SDL_RenderFillRect(renderer.get(), &rect);
    }

    rover_sprite.render(model.getCamera().worldToScreen(model.getMoonRover().getRect()));
    for (Rect wheel : model.getMoonRover().getWheels()) {
        this->wheel_sprite.render(model.getCamera().worldToScreen(wheel));
    }

    for (Rect bullet : model.getUpwardBullets()) {
        this->bullet_sprite.render(model.getCamera().worldToScreen(bullet));
    }

    gameplayUI.render(renderer, model.getCamera());
}