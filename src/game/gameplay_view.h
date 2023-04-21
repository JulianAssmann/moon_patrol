#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <SDL2/SDL.h>
#include "../texture/sprite.h"
#include "gameplay_model.h"
#include "camera.h"

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
    virtual void render(GameplayModel &model);
private:
    Sprite rover_sprite;
    Sprite mountains_foreground_sprite;
    Sprite mountains_background_sprite;
    Sprite bullet_sprite;
    Sprite wheel_sprite;
    std::shared_ptr<SDL_Renderer> renderer;
};

#endif // MAIN_VIEW_H