#include "model.h"

GameplayModel::GameplayModel() : 
    moonRover(Rover(Rect::fromCenter(0.5, 0.775, 0.13, 0.1), cameraSpeed)),
    background(Background()),
    upward_bullets(std::vector<Rect>()),
    forward_bullets(std::vector<Rect>()),
    terrain(Terrain(0.775 + 0.1 * 0.5, 70, 0.004, 0.012))
{ }

void GameplayModel::init(Size windowSize) 
{
    camera = Camera(windowSize);
    terrain.generateTerrainTo(camera.getPosition().x + 1.0);
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
    for (auto& bullet : upward_bullets) {
        bullet += Vector2(moonRover.getCurrentVelocity(), -2.0f) * dt;
        if (bullet.y > 1.0f) {
            upward_bullets.erase(upward_bullets.begin());
        }
    }

    // Create new terrain if necessary
    terrain.removeTerrainTo(camera.getPosition().x - 1.5);
    terrain.generateTerrainTo(camera.getPosition().x + 1.5);
    if (camera.getPosition().x > lastCraterPos) {
        lastCraterPos += 2.0f;
        terrain.generateCrater(lastCraterPos, Size(0.12f, 0.2f));
    }
}

void GameplayModel::shoot() {
    upward_bullets.push_back(Rect(moonRover.getRect().getTopLeft() + Vector2(9 * moonRover.getRect().getSize().width / 32, 0), 0.005f, 0.05f));
}

std::vector<Rect> GameplayModel::getUpwardBullets() const {
    return this->upward_bullets;
}

const Terrain& GameplayModel::getTerrain() const {
    return this->terrain;
}

Rover& GameplayModel::getMoonRover() {
    return this->moonRover;
}

const Camera& GameplayModel::getCamera() const {
    return this->camera;
}

const Background& GameplayModel::getBackground() const {
    return this->background;
}

float GameplayModel::getCameraSpeed() const {
    return this->cameraSpeed;
}