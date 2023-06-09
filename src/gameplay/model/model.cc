#include "model.h"
#include "../view/ui.h"

GameplayModel::GameplayModel() :
    moonRover(Rover(Rect::fromCenter(0.5, 0.775, 0.13, 0.1), cameraSpeed)),
    background(Background()),
    upward_bullets(std::vector<Rect>()),
    forward_bullets(std::vector<Rect>()),
    terrain(Terrain(0.775 + 0.1 * 0.5, 70, 0.004, 0.012)) {}

void GameplayModel::init(Size windowSize) {
    camera = Camera(windowSize, GameplayUI::uiHeight);
    terrain.generateTerrainTo(camera.getPosition().x + 1.0);
    level = Level::load("assets/levels/level1.txt");
}

void GameplayModel::update(float dt) {
    // Increase the time spent in the current level
    // by the delta time since the last update
    timeInLevel += dt;

    // Move the camera
    camera.move(Vector2(cameraSpeed, 0) * dt);

    // Update the background (mountains with parallax effect)
    background.update(*this, dt);

    // Update the moon rover
    moonRover.update(*this, dt);

    // Update the bullets
    for (auto &bullet : upward_bullets) {

        bullet += Vector2(moonRover.getCurrentVelocity(), -2.0f) * dt;

        if (bullet.y > 1.0f) {
            upward_bullets.erase(upward_bullets.begin());
        }
    }

    // Create new terrain if necessary
    terrain.removeTerrainTo(camera.getPosition().x - 1.5);
    terrain.generateTerrainTo(camera.getPosition().x + 1.5);

    level.update(*this, dt);
}

void GameplayModel::shoot() {
    upward_bullets.push_back(Rect(moonRover.getRect().getTopLeft() + Vector2(9 * moonRover.getRect().getSize().width / 32, 0), 0.005f, 0.05f));
}

std::vector<Rect> GameplayModel::getUpwardBullets() const {
    return this->upward_bullets;
}

const Terrain &GameplayModel::getTerrain() const {
    return this->terrain;
}

Rover &GameplayModel::getMoonRover() {
    return this->moonRover;
}

const Camera &GameplayModel::getCamera() const {
    return this->camera;
}

const Background &GameplayModel::getBackground() const {
    return this->background;
}

float GameplayModel::getCameraSpeed() const {
    return this->cameraSpeed;
}

const float GameplayModel::getTimeInLevel() const {
    return this->timeInLevel;
}

const int GameplayModel::getTotalPoints() const {
    return this->totalPoints;
}

const int GameplayModel::getPointsSinceLastCheckpoint() const {
    return this->pointsSinceLastCheckpoint;
}

const int GameplayModel::getLivesRemaining() const {
    return this->livesRemaining;
}

const char GameplayModel::getLastCheckpoint() const {
    return this->lastCheckpoint;
}

const bool GameplayModel::getIsTerrainBlockImminent() const {
    return this->isTerrainBlockImminent;
}

const bool GameplayModel::getIsMinefieldImminent() const {
    return this->isMinefieldImminent;
}

const bool GameplayModel::getIsAerialAttackImminent() const {
    return this->isAerialAttackImminent;
}

const char GameplayModel::getHighscoreCheckpoint() const {
    return this->highscoreCheckpoint;
}

Level& GameplayModel::getLevel() {
    return this->level;
}