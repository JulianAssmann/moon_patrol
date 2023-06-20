#include "bomber.h"
#include "../model.h"

Bomber::Bomber(Vector2 startingPosition)
    : Bomber(
        Rect(
            startingPosition,
            Size(0.1f, 0.1f))) { }

Bomber::Bomber(Rect rect) :
    LevelEntity(LevelEntityType::BOMBER, LevelEntityAttackType::AERIAL, rect),
    speed(0.1f),
    bombDropInterval(2.0f),
    bombDropTimer(0.0f),
    swirrTimer(0.0f),
    swirrInterval(1.0f),
    swirrDeviation(0.1f) { }

void Bomber::update(GameplayModel& model, float dt) {
    this->swirrTimer += dt;
    float swirrX = std::cos(swirrTimer * 2.0f * M_PI / swirrInterval) * swirrDeviation;
    this->rect.x = model.getMoonRover().getRect().getCenter().x + swirrX;

    this->bombDropTimer += dt;
    if (this->bombDropTimer >= this->bombDropInterval) {
        this->bombDropTimer = 0.0f;
        this->dropBomb(model);
    }
}

void Bomber::dropBomb(GameplayModel& model) {
    // TODO
}