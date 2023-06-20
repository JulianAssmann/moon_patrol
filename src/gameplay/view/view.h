#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <SDL2/SDL.h>
#include "../../assets/sprite.h"
#include "../model/model.h"
#include "../model/camera.h"
#include "ui.h"

class GameplayView {
public:
    /// @brief Create the view and initialize resources used by it
    GameplayView(std::shared_ptr<SDL_Renderer> renderer);

    /// @brief Destroy the view and free resources used by it
    virtual ~GameplayView();

    /// @brief Initiliaze the view
    virtual void init();

    /// @brief Render the model
    /// @param model The model to render from
    void render(GameplayModel &model);

private:
    Sprite roverSprite;
    Sprite mountainsForegroundSprite;
    Sprite mountainsBackgroundSprite;
    Sprite bulletSprite;
    Sprite wheelSprite;
    Sprite bomberSprite;
    Sprite impactBomberSprite;

    GameplayUI gameplayUI;
    std::shared_ptr<SDL_Renderer> renderer;

    void renderBackground(GameplayModel &model);
    void renderTerrain(GameplayModel &model);
    void renderRover(GameplayModel &model);
    void renderLevelEntities(GameplayModel &model);
};

#endif // MAIN_VIEW_H