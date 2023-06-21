#include "impact_bomber.h"
#include "../model.h"

ImpactBomber::ImpactBomber(Vector2 startingPosition) : ImpactBomber(Rect(startingPosition, Size(0.1f, 0.07f))) { }
ImpactBomber::ImpactBomber(Rect rect) : Bomber(LevelEntityType::IMPACT_BOMBER, rect) { }

void ImpactBomber::dropBomb(GameplayModel& model) {
}

void ImpactBomber::update(GameplayModel& model, float dt) {
    Bomber::update(model, dt);
}