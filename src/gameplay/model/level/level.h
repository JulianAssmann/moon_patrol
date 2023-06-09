#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "level_entity.h"
#include <memory>
#include "bomber.h"
#include "impact_bomber.h"

class GameplayModel;

class Level {
public:
    Level();
    static Level load(const std::string& path);
    void save(const std::string& path) const;
    void update(GameplayModel& model, float dt);

    std::vector<std::shared_ptr<LevelEntity>>& getActiveEntities();
private:
    std::map<float, std::shared_ptr<LevelEntity>> entitiesToBeSpawned;
    std::vector<std::shared_ptr<LevelEntity>> activeEntites;

    static std::string levelEntityTypeToString(LevelEntityType type);
    static LevelEntityType stringToGameLevelEntityType(const std::string& type);
};

#endif // LEVEL_H