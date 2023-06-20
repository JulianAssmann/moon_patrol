#include "view.h"

GameplayView::GameplayView(std::shared_ptr<SDL_Renderer> renderer) :
    renderer(renderer),
    roverSprite(Sprite("assets/textures/rover.png", renderer)),
    mountainsForegroundSprite(Sprite("assets/textures/mountains-foreground.png", renderer)),
    mountainsBackgroundSprite(Sprite("assets/textures/mountains-background.png", renderer)),
    bulletSprite(Sprite("assets/textures/bullet.png", renderer)),
    wheelSprite(Sprite("assets/textures/wheel.png", renderer)),
    bomberSprite(Sprite("assets/textures/bomber.png", renderer)),
    impactBomberSprite(Sprite("assets/textures/impact-bomber.png", renderer)),
    gameplayUI(GameplayUI(renderer)) { }

GameplayView::~GameplayView() { }

void GameplayView::init() {
    roverSprite.init();
    mountainsForegroundSprite.init();
    mountainsBackgroundSprite.init();
    bulletSprite.init();
    wheelSprite.init();
    bomberSprite.init();
    impactBomberSprite.init();
    gameplayUI.init();
}

void GameplayView::render(GameplayModel &model) {
    renderBackground(model);
    renderTerrain(model);
    renderRover(model);
    renderLevelEntities(model);

    for (Rect bullet : model.getUpwardBullets()) {
        this->bulletSprite.render(model.getCamera().worldToScreen(bullet));
    }

    gameplayUI.render(model);
}

void GameplayView::renderBackground(GameplayModel &model) {
    for (Rect background : model.getBackground().getForegroundMountains()) {
        this->mountainsBackgroundSprite.render(model.getCamera().worldToScreen(background));
    }
    for (Rect background : model.getBackground().getBackgroundMountains()) {
        this->mountainsForegroundSprite.render(model.getCamera().worldToScreen(background));
    }
}

void GameplayView::renderTerrain(GameplayModel &model) {
    for (Rect terrain : model.getTerrain().getTerrainSegments()) {
        SDL_SetRenderDrawColor(renderer.get(), 252, 150, 79, 255);
        SDL_Rect rect = model.getCamera().worldToScreen(terrain).toSDLRect();
        SDL_RenderFillRect(renderer.get(), &rect);
    }
}

void GameplayView::renderRover(GameplayModel &model) {
    roverSprite.render(model.getCamera().worldToScreen(model.getMoonRover().getRect()));
    for (Rect wheel : model.getMoonRover().getWheels()) {
        this->wheelSprite.render(model.getCamera().worldToScreen(wheel));
    }
}

void GameplayView::renderLevelEntities(GameplayModel &model) {
    // std::cout << "Rendering " << model.getLevel().getActiveEntities().size() << " level entities" << std::endl;
    for (auto levelEntity : model.getLevel().getActiveEntities()) {

        // std::cout << "Rendering level entity of type " << static_cast<int>(levelEntity.getType()) << std::endl;

        SDL_Rect rect = model.getCamera().worldToScreen(levelEntity.getRect()).toSDLRect();

        switch (levelEntity.getType())
        {
        case LevelEntityType::BOMBER:
            this->bomberSprite.render(rect);
            break;
        case LevelEntityType::IMPACT_BOMBER:
            this->impactBomberSprite.render(rect);
            break;
        default:
            break;
        }
    }
}