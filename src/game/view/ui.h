#ifndef GAMEPLAY_UI_H
#define GAMEPLAY_UI_H

#include <iostream>
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "../model/model.h"
#include "../model/camera.h"
#include "../../texture/sprite.h"
#include "../../utils/rect.h"
#include "../../utils/vector2.h"
#include "../../texture/font.h"

class GameplayUI {
public:
    GameplayUI(std::shared_ptr<SDL_Renderer> renderer);
    void init();
    void render(const GameplayModel& model);
    // void renderProgressBar(const GameplayModel& model);
private:
    Rect containerRect;
    Rect progressBarBackgroundRect;
    Rect progressBarForegroundRect;
    Rect aerialAttackWarningRect;
    Rect minefieldWarningRect;
    Rect terainWarningRect;

    Vector2 pointsTextPos;
    Vector2 pointsSinceLastCheckpointTextPos;
    Vector2 timeTextPos;
    Vector2 livesTextPos;
    Vector2 lastCheckpointTextPos;

    Sprite crownSprite;
    Sprite roverSprite;
    Sprite pointSprite;

    Font font;
    Font fontAttackWarnings;
    Font fontCheckpoint;

    Size cautionTextSize;

    static constexpr float uiHeight = 0.19f;
    static constexpr Rect subcontainerRect = Rect(
        0.33f, 0.1f * uiHeight, 0.55f, 0.6 * uiHeight
    );

    std::shared_ptr<SDL_Renderer> renderer;

    std::string padLeft(std::string& str, int n, char c = ' ');
    void renderAttackWarning(Rect rect, bool isImminent, SDL_Color warningColor);

    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};
};

#endif // GAMEPLAY_UI_H