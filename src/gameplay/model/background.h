#ifndef BACKGOUND_H
#define BACKGOUND_H

#include <vector>
#include "../../utils/rect.h"

class GameplayModel;

class Background {
public:
    Background(float foregroundParallaxFactor = 0.8, float backgroundParallaxFactor = 0.5);

    void update(const GameplayModel& model, float dt);

    const std::vector<Rect>& getForegroundMountains() const;

    const std::vector<Rect>& getBackgroundMountains() const;
private:
    std::vector<Rect> mountainsForeground;
    std::vector<Rect> mountainsBackground;

    float foregroundParallaxFactor;
    float backgroundParallaxFactor;
};

#endif // BACKGOUND_H