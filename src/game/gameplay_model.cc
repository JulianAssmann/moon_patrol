#include "gameplay_model.h"

GameplayModel::GameplayModel() : 
    moon_rover(Rover(Rect::fromCenter(0.5, 0.775, 0.13, 0.1), camera_speed)),
    mountainsForeground1(Rect(0.0f, 0.0f, 1.0f, 1.0f)), 
    mountainsForeground2(Rect(1.0f, 0.0f, 1.0f, 1.0f)), 
    mountainsBackground1(Rect(0.0f, 0.0f, 1.0f, 1.0f)), 
    mountainsBackground2(Rect(1.0f, 0.0f, 1.0f, 1.0f)), 
    parallax_factor(0.5f),
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

    // Move the camera
    camera.move(Vector2(camera_speed, 0) * dt);

    moon_rover.update(dt, *this);

    // Continously repeat the background textures to the right
    if (mountainsForeground1.x < camera.getPosition().x - 1.0f) {
        mountainsForeground1 += Vector2(2, 0);
    } else if (mountainsForeground2.x < camera.getPosition().x - 1.0f) {
        mountainsForeground2 += Vector2(2, 0);
    }

    // Move the background textures slower than the foreground
    mountainsBackground1 += Vector2(camera_speed * parallax_factor, 0) * dt;
    mountainsBackground2 += Vector2(camera_speed * parallax_factor, 0) * dt;

    // Continously repeat the background textures to the right
    if (mountainsBackground1.x < camera.getPosition().x - 1.0f) {
        mountainsBackground1 += Vector2(2, 0);
    } else if (mountainsBackground2.x < camera.getPosition().x - 1.0f) {
        mountainsBackground2 += Vector2(2, 0);
    }

    // Move the bullets
    for (auto& bullet : upward_bullets) {
        bullet += Vector2(moon_rover.getCurrentVelocity(), -2.0f) * dt;
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
    upward_bullets.push_back(Rect(moon_rover.getRect().getTopLeft() + Vector2(9 * moon_rover.getRect().getSize().width / 32, 0), 0.005f, 0.05f));
}

std::vector<Rect> GameplayModel::getUpwardBullets() const {
    return upward_bullets;
}

std::vector<Rect> GameplayModel::getForegroundMountains() const {
    return {mountainsForeground1, mountainsForeground2};
}

std::vector<Rect> GameplayModel::getBackgroundMountains() const {
    return {mountainsBackground1, mountainsBackground2};
}

const Terrain& GameplayModel::getTerrain() const {
    return terrain;
}

Rover& GameplayModel::getMoonRover() {
    return moon_rover;
}

Camera GameplayModel::getCamera() const
{
    return camera;
}