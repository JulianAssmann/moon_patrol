#include "level_entity.h"
#include "../model.h"

LevelEntity::LevelEntity(LevelEntityType type, LevelEntityAttackType attackType, Vector2 startingPosition, Size size)
    : LevelEntity(type, attackType, Rect(startingPosition, size)) { }

LevelEntity::LevelEntity(LevelEntityType type, LevelEntityAttackType attackType, Rect rect)
    : type(type), rect(rect), state(LevelEntityState::WAITING_FOR_ACTIVATION), attackType(attackType) { }

Rect LevelEntity::getRect() const {
    return this->rect;
}
LevelEntityType LevelEntity::getType() const {
    return this->type;
}

LevelEntityState LevelEntity::getState() const {
    return this->state;
}

void LevelEntity::activate(GameplayModel& model) {
    this->state = LevelEntityState::ACTIVE;
    onActivation(model);
}

void LevelEntity::destroy(GameplayModel& model) {
    this->state = LevelEntityState::INACTIVE;
}

void LevelEntity::update(GameplayModel& model, float dt) {
    if (this->state != LevelEntityState::ACTIVE) {
        return;
    }
}

void LevelEntity::onActivation(GameplayModel& model) { }