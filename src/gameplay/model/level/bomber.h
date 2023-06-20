#ifndef BOMBER_H
#define BOMBER_H

#include <cmath>
#include "level_entity.h"
#include "../../../utils/vector2.h"
#include "../../../utils/size.h"
#include "../../../utils/rect.h"

class Bomber : public LevelEntity {

public:
    Bomber(Vector2 startingPosition);
    Bomber(Rect rect);

    void update(GameplayModel& model, float dt) override;
    virtual void dropBomb(GameplayModel& model);

private:
    float speed;
    float bombDropInterval;
    float bombDropTimer;
    float swirrTimer;
    float swirrInterval;
    float swirrDeviation;
};

#endif // BOMBER_H