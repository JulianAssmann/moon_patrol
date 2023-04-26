#ifndef GAMEPLAY_UI_H
#define GAMEPLAY_UI_H

#include <string>
#include <SDL2/SDL.h>
#include "../../utils/rect.h"
#include "../model/model.h"
#include "../model/camera.h"

class GameplayUI {
public:
    GameplayUI();
    void render(std::shared_ptr<SDL_Renderer> renderer, const Camera& camera) const;
private:
    Rect container;
    Rect subcontainer;
    Rect progressBarBackground;
    Rect progressBarForeground;

    static constexpr float uiHeight = 0.19f;
};

#endif // GAMEPLAY_UI_H