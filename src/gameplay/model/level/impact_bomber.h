#ifndef IMPACT_BOMBER_H
#define IMPACT_BOMBER_H

#include "bomber.h"

class ImpactBomber : public Bomber {
public:
    ImpactBomber(Vector2 startingPosition);
    ImpactBomber(Rect rect);
    virtual void update(GameplayModel& model, float dt) override;
    void dropBomb(GameplayModel& model) override;
};

#endif // IMPACT_BOMBER_H