#include "bomber.h"
#include "../model.h"

Bomber::Bomber(Vector2 startingPosition)
    : Bomber(
        LevelEntityType::BOMBER,
        Rect(
            startingPosition,
            Size(0.1f, 0.05f))) { }

Bomber::Bomber(Rect rect)
    : Bomber(LevelEntityType::BOMBER, rect) { }

Bomber::Bomber(LevelEntityType type, Vector2 startingPosition)
    : Bomber(type, Rect(startingPosition, Size(0.1f, 0.05f))) { }

Bomber::Bomber(LevelEntityType type, Rect rect) :
    LevelEntity(type, LevelEntityAttackType::AERIAL, rect),
    speed(0.3f),
    bombDropInterval(2.0f),
    bombDropTimer(0.0f),
    currentGoal(rect.getCenter()) { }

void Bomber::onActivation(GameplayModel& model) {
    LevelEntity::onActivation(model);
    this->setRandomGoal(model);
}

void Bomber::update(GameplayModel& model, float dt) {
    LevelEntity::update(model, dt);

    this->bombDropTimer += dt;
    if (this->bombDropTimer >= this->bombDropInterval) {
        this->bombDropTimer = 0.0f;
        this->dropBomb(model);
    }

    Vector2 diff = this->currentGoal - this->currentDeviation;
    float distance = diff.length();
    if (distance < 0.005f) {
        this->setRandomGoal(model);
    } else {
        Vector2 direction = diff / distance;
        currentDeviation += direction * speed * dt;

        this->rect = Rect(
            Vector2(
                model.getMoonRover().getRect().getCenter().x + this->currentDeviation.x,
                currentDeviation.y),
            this->rect.getSize());
    }
}

void Bomber::setRandomGoal(GameplayModel& model) {
    float playerX = model.getMoonRover().getRect().getCenter().x;

    this->currentGoal = Vector2::randomBetween(
        Vector2(-0.3f, 0.05f),
        Vector2(0.3f, 0.15f));
}

void Bomber::dropBomb(GameplayModel& model) {
    // TODO
}