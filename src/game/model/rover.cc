#include "rover.h"
#include "gameplay_model.h"

Rover::Rover(Rect rect, float velocity) : rect(rect), horizontalVelocity(velocity), wheels(3) {
    wheels[0] = Rect::fromCenter(0.0f, 0.0f, Size(wheelWidth, wheelHeight));
    wheels[1] = Rect::fromCenter(0.0f, 0.0f, Size(wheelWidth, wheelHeight));
    wheels[2] = Rect::fromCenter(0.0f, 0.0f, Size(wheelWidth, wheelHeight));
}

const std::vector<Rect>& Rover::getWheels() const {
    return wheels;
}

void Rover::init(const Rect& rect, const GameplayModel& model) {
    this->rect = rect;
    this->isJumping = false;
    updateWheels(model);
}

void Rover::updateWheels(const GameplayModel& model) {
    float offset = 0.15f;
    float rover_x = rect.getCenter().x;

    if (isJumping) {
        float height = rect.y + rect.height - rect.height * 0.1f;
        wheels[0].setCenter(Vector2(rover_x - 0.35 * rect.width, height));
        wheels[1].setCenter(Vector2(rover_x - 0.1 * rect.width, height));
        wheels[2].setCenter(Vector2(rover_x + 0.3 * rect.width, height));
    } else {
        float height = model.getTerrain().getHeightAt(wheels[0].x);
        wheels[0].setCenter(Vector2(rover_x - 0.35 * rect.width, height - offset * rect.height));

        height = model.getTerrain().getHeightAt(wheels[1].x);
        wheels[1].setCenter(Vector2(rover_x - 0.1 * rect.width, height - offset * rect.height));

        height = model.getTerrain().getHeightAt(wheels[2].x);
        wheels[2].setCenter(Vector2(rover_x + 0.3 * rect.width, height - offset * rect.height));
    }

}

void Rover::driveFaster() {
    additional_velocity = 0.1;
}

void Rover::driveSlower() {
    additional_velocity = -0.1;
}

void Rover::driveNormally() {
    additional_velocity = 0;
}

void Rover::update(const GameplayModel& model, float dt) {
    Vector2 vel = Vector2(getCurrentVelocity(), verticalVelocity);
    rect += vel * dt;

    Vector2 moon_rover_center_camera_space = model.getCamera().worldToCamera(rect.getCenter());
    if (moon_rover_center_camera_space.x > 0.8f) {
        rect = Rect::fromCenter(
            model.getCamera().cameraToWorld(Vector2(0.8f, moon_rover_center_camera_space.y)),
            rect.getSize());
    } else if (moon_rover_center_camera_space.x < 0.2f) {
        rect = Rect::fromCenter(
            model.getCamera().cameraToWorld(Vector2(0.2f, moon_rover_center_camera_space.y)),
            rect.getSize());
    }

    float terrainHeight = model.getTerrain().getHeightAt(rect.getCenter().x);
    float heightDiff = abs(rect.y + rect.height - terrainHeight);

    if (isJumping) {
        if (heightDiff < 0.01f && verticalVelocity > 0) {
            isJumping = false;
            verticalVelocity = 0;
            rect.y = terrainHeight - rect.height;
        } else {
            verticalVelocity += 1.0f * dt;
        }
    } else {
        rect.y = terrainHeight - rect.height;
    }

    updateWheels(model);
}

void Rover::jump() {
    if (!isJumping) {
        isJumping = true;
        verticalVelocity = -0.5f;
    }
}

const Rect& Rover::getRect() const {
    return rect;
}

float Rover::getCurrentVelocity() const {
    return horizontalVelocity + additional_velocity;
}