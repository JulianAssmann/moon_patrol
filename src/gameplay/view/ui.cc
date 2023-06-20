#include "ui.h"

GameplayUI::GameplayUI(std::shared_ptr<SDL_Renderer> renderer) :
    renderer(renderer),
    containerRect(Rect(0.0f, 0.0f, 1.0f, 1.0f)),
    progressBarBackgroundRect(Rect(subcontainerRect.x, 0.85f, subcontainerRect.width, 0.1f)),
    progressBarForegroundRect(Rect(subcontainerRect.x, 0.85f, 0.25f, 0.1f)),
    pointsTextPos(Vector2(0.05f, 0.15f)),
    pointsSinceLastCheckpointTextPos(Vector2(0.00f, 0.45)),
    lastCheckpointTextPos(Vector2(subcontainerRect.getTopLeft() + Vector2(0.01f, 0.02f))),
    timeTextPos(Vector2(subcontainerRect.getBottomLeft() + Vector2(0.01f, -0.22f))),
    livesTextPos(Vector2(1.0f - 0.03f, subcontainerRect.getCenter().y - 0.02f)),
    crownSprite(Sprite("assets/textures/crown.png", renderer)),
    roverSprite(Sprite("assets/textures/rover-lives.png", renderer)),
    pointSprite(Sprite("assets/textures/point.png", renderer)),
    font("assets/textures/irem-font/irem-font.ttf", renderer),
    fontAttackWarnings("assets/textures/irem-font/irem-font.ttf", renderer),
    fontCheckpoint("assets/textures/irem-font/irem-font.ttf", renderer)
{
    float attackWarningX = subcontainerRect.getTopLeft().x + subcontainerRect.getSize().width * 0.5;
    float attackWarningYMargin = 0.25 * subcontainerRect.getSize().height;

    aerialAttackWarningPoint = Vector2(
        attackWarningX,
        subcontainerRect.getTopLeft().y + 0.5 * attackWarningYMargin
    );
    minefieldWarningPoint = Vector2(
        attackWarningX,
        subcontainerRect.getTopLeft().y + 1.5 * attackWarningYMargin
    );
    terrainWarningPoint = Vector2(
        attackWarningX,
        subcontainerRect.getTopLeft().y + 2.5 * attackWarningYMargin
    );
}

void GameplayUI::init()
{
    int width, height;
    SDL_GetRendererOutputSize(renderer.get(), &width, &height);

    int fontSizeScaled = (int)(26 * height / 800.0f);
    font.init(fontSizeScaled);

    int fontSizeAttackWarningsScaled = (int)(12 * height / 800.0f);
    fontAttackWarnings.init(fontSizeAttackWarningsScaled);
    cautionTextSize = fontAttackWarnings.getTextureSize("CAUTION");

    int fontSizeCheckpointScaled = (int)(6 * height / 800.0f);
    fontCheckpoint.init(fontSizeCheckpointScaled);

    crownSprite.init();
    roverSprite.init();
    pointSprite.init();
}

void GameplayUI::render(const GameplayModel &model)
{
    Camera camera = model.getCamera();
    Rect previousTextRect;

    SDL_Rect rect;

    // Render main UI container
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255);
    rect = camera.uiToScreen(containerRect).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render subcontainer
    SDL_SetRenderDrawColor(renderer.get(), 97, 255, 255, 255);
    rect = camera.uiToScreen(subcontainerRect).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render points text
    std::string pointsStr = std::to_string(model.getTotalPoints());
    std::string paddedPointsStr = padLeft(pointsStr, 6, '0');
    previousTextRect = font.render(camera.uiToScreen(pointsTextPos), paddedPointsStr.c_str(), red);
    std::string lastHighscoreCheckpointStr = "-" + std::string(1, model.getHighscoreCheckpoint());
    font.render(previousTextRect.getTopRight(), lastHighscoreCheckpointStr.c_str(), black);

    float crownSizeMultiplier = 0.8f;
    Size crownSize = Size(previousTextRect.getTopLeft().x, previousTextRect.height);
    Vector2 crownPos = Vector2(
        0.0f + crownSize.width * (1 - crownSizeMultiplier) * 0.5f,
        previousTextRect.getTopLeft().y + (1 - crownSizeMultiplier) * 0.5f);
    crownSprite.render(Rect(crownPos, crownSize * crownSizeMultiplier));

    // Render last checkpoint text
    std::string lastCheckpointStr = "POINT " + std::string(1, model.getLastCheckpoint());
    font.render(camera.uiToScreen(lastCheckpointTextPos), lastCheckpointStr.c_str(), black);

    // Render time text
    std::string timeInSeconds = std::to_string((int)model.getTimeInLevel());
    std::string timeText = "TIME" + padLeft(timeInSeconds, 3, '0');
    font.render(camera.uiToScreen(timeTextPos), timeText.c_str(), red);

    // Render points since last checkpoint text
    std::string pointsSinceLastCheckpointStr = std::to_string(model.getPointsSinceLastCheckpoint());
    std::string paddedPointsSinceLastCheckpointStr = padLeft(pointsSinceLastCheckpointStr, 6, '0');
    previousTextRect = font.render(camera.uiToScreen(pointsSinceLastCheckpointTextPos), "1", yellow);
    previousTextRect = font.render(previousTextRect.getTopRight(), "P-", red);
    previousTextRect = font.render(previousTextRect.getTopRight(), paddedPointsSinceLastCheckpointStr.c_str(), yellow);

    // Render lives remaining
    std::string livesStr = std::to_string(model.getLivesRemaining());
    previousTextRect = font.render(camera.uiToScreen(livesTextPos), livesStr.c_str(), yellow);

    float roverSizeMultiplier = 0.8f;
    Size roverSize = Size(
        previousTextRect.height * roverSprite.getSize().width / roverSprite.getSize().height,
        previousTextRect.height);
    Vector2 roverPos = Vector2(
        previousTextRect.getTopLeft().x - roverSize.width * roverSizeMultiplier * 1.2f - (1 - roverSizeMultiplier) * roverSize.width * 0.5f,
        previousTextRect.getTopLeft().y + (1 - roverSizeMultiplier) * roverSize.height * 0.5f);
    roverSprite.render(Rect(roverPos, roverSize * roverSizeMultiplier));

    // Render progress bar background
    SDL_SetRenderDrawColor(renderer.get(), 97, 255, 255, 255);
    rect = camera.uiToScreen(progressBarBackgroundRect).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render progress bar foreground
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    rect = camera.uiToScreen(progressBarForegroundRect).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render attack warnings
    float attackWarningHeight = subcontainerRect.getSize().height / 5;
    Size attackWarningSize = Size(attackWarningHeight / camera.getUIAspectRatio(), attackWarningHeight);

    renderAttackWarning(
        camera.uiToScreen(
            Rect(
                aerialAttackWarningPoint,
                attackWarningSize)),
        model.getIsAerialAttackImminent(), red);

    renderAttackWarning(
        camera.uiToScreen(
            Rect(
                minefieldWarningPoint,
                attackWarningSize)),
        model.getIsMinefieldImminent(), green);

    renderAttackWarning(
        camera.uiToScreen(
            Rect(
                terrainWarningPoint,
                attackWarningSize)),
        model.getIsTerrainBlockImminent(), red);
}

void GameplayUI::renderAttackWarning(Rect rect, bool isImminent, SDL_Color warningColor)
{
    if (isImminent)
    {
        pointSprite.render(rect, warningColor);
        fontAttackWarnings.render(
            Vector2(
                rect.getTopRight().x + 0.5f * rect.width,
                rect.getTopLeft().y + rect.height * 0.5f - 0.5f * cautionTextSize.height),
            "CAUTION", warningColor);
    }
    else
    {
        pointSprite.render(rect, black);
    }
}

std::string GameplayUI::padLeft(std::string &str, int n, char c)
{
    if (str.size() < n)
        return std::string(n - str.size(), c) + str;
    else
        return str;
}

// void GameplayUI::renderProgressBar(const GameplayModel& model) {

// }