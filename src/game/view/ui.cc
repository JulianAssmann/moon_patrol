#include "ui.h"

GameplayUI::GameplayUI(std::shared_ptr<SDL_Renderer> renderer) : 
    renderer(renderer),
    containerRect(Rect(0.0f, 0.0f, 1.0f, uiHeight)),
    progressBarBackgroundRect(Rect(subcontainerRect.x, 0.85 * uiHeight, subcontainerRect.width, 0.1f * uiHeight)),
    progressBarForegroundRect(Rect(subcontainerRect.x, 0.85 * uiHeight, 0.25f, 0.1f * uiHeight)),
    pointsTextPos(Vector2(0.05f, 0.15 * uiHeight)),
    pointsSinceLastCheckpointTextPos(Vector2(0.00f, 0.45 * uiHeight)),
    lastCheckpointTextPos(Vector2(subcontainerRect.getTopLeft() + Vector2(0.01f, 0.01f))),
    timeTextPos(Vector2(subcontainerRect.getBottomLeft() + Vector2(0.01f, -0.05f))),
    livesTextPos(Vector2(1.0f - 0.03f, subcontainerRect.getCenter().y - 0.02f)),
    crownSprite(Sprite("assets/crown.png", renderer)),
    roverSprite(Sprite("assets/rover-lives.png", renderer)),
    pointSprite(Sprite("assets/point.png", renderer)),
    font("assets/irem-font/irem-font.ttf", renderer),
    fontAttackWarnings("assets/irem-font/irem-font.ttf", renderer),
    fontCheckpoint("assets/irem-font/irem-font.ttf", renderer)
{
    float attackWarningSize = subcontainerRect.getSize().height / 5;
    float attackWarningX = subcontainerRect.getTopLeft().x + subcontainerRect.getSize().width * 0.6;
    float attackWarningYMargin = 0.1 * subcontainerRect.getSize().height;
    
    aerialAttackWarningRect = Rect(
        attackWarningX,
        subcontainerRect.getTopLeft().y + attackWarningYMargin,
        attackWarningSize,
        attackWarningSize
    );
    minefieldWarningRect = Rect(
        attackWarningX,
        subcontainerRect.getTopLeft().y + attackWarningSize + 2 * attackWarningYMargin,
        attackWarningSize,
        attackWarningSize
    );

    terainWarningRect = Rect(
        attackWarningX,
        subcontainerRect.getTopLeft().y + 2 * attackWarningSize + 3 * attackWarningYMargin,
        attackWarningSize,
        attackWarningSize
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
    rect = camera.cameraToScreen(containerRect).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render subcontainer
    SDL_SetRenderDrawColor(renderer.get(), 97, 255, 255, 255);
    rect = camera.cameraToScreen(subcontainerRect).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render points text
    std::string pointsStr = std::to_string(model.getTotalPoints());
    std::string paddedPointsStr = padLeft(pointsStr, 6, '0');
    previousTextRect = font.render(camera.cameraToScreen(pointsTextPos), paddedPointsStr.c_str(), red);
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
    font.render(camera.cameraToScreen(lastCheckpointTextPos), lastCheckpointStr.c_str(), black);

    // Render time text
    std::string timeInSeconds = std::to_string((int)model.getTimeInLevel());
    std::string timeText = "TIME" + padLeft(timeInSeconds, 3, '0');
    font.render(camera.cameraToScreen(timeTextPos), timeText.c_str(), red);

    // Render points since last checkpoint text
    std::string pointsSinceLastCheckpointStr = std::to_string(model.getPointsSinceLastCheckpoint());
    std::string paddedPointsSinceLastCheckpointStr = padLeft(pointsSinceLastCheckpointStr, 6, '0');
    previousTextRect = font.render(camera.cameraToScreen(pointsSinceLastCheckpointTextPos), "1", yellow);
    previousTextRect = font.render(previousTextRect.getTopRight(), "P-", red);
    previousTextRect = font.render(previousTextRect.getTopRight(), paddedPointsSinceLastCheckpointStr.c_str(), yellow);

    // Render lives remaining
    std::string livesStr = std::to_string(model.getLivesRemaining());
    previousTextRect = font.render(camera.cameraToScreen(livesTextPos), livesStr.c_str(), yellow);

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
    rect = camera.cameraToScreen(progressBarBackgroundRect).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render progress bar foreground
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    rect = camera.cameraToScreen(progressBarForegroundRect).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render attack warnings
    renderAttackWarning(camera.cameraToScreen(aerialAttackWarningRect), model.getIsAerialAttackImminent(), red);
    renderAttackWarning(camera.cameraToScreen(minefieldWarningRect), model.getIsMinefieldImminent(), green);
    renderAttackWarning(camera.cameraToScreen(terainWarningRect), model.getIsTerrainBlockImminent(), red);
}

void GameplayUI::renderAttackWarning(Rect rect, bool isImminent, SDL_Color warningColor)
{
    if (isImminent)
    {
        pointSprite.render(rect, red);
        fontAttackWarnings.render(
            Vector2(rect.getTopRight().x + 0.5f * rect.width,
            rect.getTopLeft().y + rect.height * 0.5f - 0.5f * cautionTextSize.height),
            "CAUTION", red);
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