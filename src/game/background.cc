#include "background.h"

#include "gameplay_model.h"

Background::Background(float foregroundParallaxFactor, float backgroundParallaxFactor) :
    mountainsForeground({Rect(0.0f, 0.0f, 1.0f, 1.0f), Rect(1.0f, 0.0f, 1.0f, 1.0f)}),
    mountainsBackground({Rect(0.0f, 0.0f, 1.0f, 1.0f), Rect(1.0f, 0.0f, 1.0f, 1.0f)}),
    foregroundParallaxFactor(foregroundParallaxFactor),
    backgroundParallaxFactor(backgroundParallaxFactor) {}

void Background::update(const GameplayModel& model, float dt) {
    float cameraSpeed = model.getCameraSpeed();

    // Continously repeat the background textures to the right
    if (mountainsForeground[0].x < model.getCamera().getPosition().x - 1.0f) {
        mountainsForeground[0] += Vector2(2, 0);
    } else if (mountainsForeground[1].x < model.getCamera().getPosition().x - 1.0f) {
        mountainsForeground[1] += Vector2(2, 0);
    }

    // Move the background textures slower than the foreground
    mountainsForeground[0] += Vector2(cameraSpeed * foregroundParallaxFactor, 0) * dt;
    mountainsForeground[1] += Vector2(cameraSpeed * foregroundParallaxFactor, 0) * dt;

    // Continously repeat the background textures to the right
    if (mountainsBackground[0].x < model.getCamera().getPosition().x - 1.0f) {
        mountainsBackground[0] += Vector2(2, 0);
    } else if (mountainsBackground[1].x < model.getCamera().getPosition().x - 1.0f) {
        mountainsBackground[1] += Vector2(2, 0);
    }

    mountainsBackground[0] += Vector2(cameraSpeed * backgroundParallaxFactor, 0) * dt;
    mountainsBackground[1] += Vector2(cameraSpeed * backgroundParallaxFactor, 0) * dt;
}

const std::vector<Rect>& Background::getForegroundMountains() const {
    return this->mountainsForeground;
}

const std::vector<Rect>& Background::getBackgroundMountains() const {
    return this->mountainsBackground;
}