#include "level.h"
#include "../model.h"

Level::Level() { }

Level Level::load(const std::string& path) {
    Level level;
    try {

        std::ifstream inFile(path);
        if (!inFile) {
            throw std::runtime_error("Unable to open file: " + path);
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string typeStr;
            float xPos;

            // Read the x position
            ss >> xPos;

            // Read the enemy type
            ss >> typeStr;

            LevelEntityType type = stringToGameLevelEntityType(typeStr);

            // Create the enemy
            switch (type)
            {
            case LevelEntityType::BOMBER:
                level.entitiesToBeSpawned.emplace(
                    std::make_pair(xPos,
                    std::make_shared<Bomber>(Vector2(xPos, -0.2f))));
                std::cout << "Bomber at " << xPos << std::endl;
                break;
            default:
                break;
            }
        }

        inFile.close();
    } catch (std::exception& e) {
        std::cout << "Unable to load level: " << e.what() << std::endl;
    }

    return level;
}

void Level::update(GameplayModel& model, float dt) {
    float xPos = model.getMoonRover().getRect().getCenter().x;

    // Spawn new entities
    auto next = entitiesToBeSpawned.begin();
    while (next->first < xPos && next != entitiesToBeSpawned.end()) {
        std::cout << "Spawning entity of type " << levelEntityTypeToString(next->second->getType()) << " at position " << next->first << std::endl;
        next->second->activate(model);
        activeEntites.push_back(next->second);
        next = entitiesToBeSpawned.erase(next);
    }

    // Update active entities
    for (auto& entity : activeEntites) {
        entity->update(model, dt);
    }

    // Clean up inactive entities
    for (auto it = activeEntites.begin(); it != activeEntites.end();) {
        if ((*it)->getState() == LevelEntityState::INACTIVE) {
            it = activeEntites.erase(it);
        } else {
            ++it;
        }
    }
}

std::vector<std::shared_ptr<LevelEntity>>& Level::getActiveEntities() {
    return activeEntites;
}

std::string Level::levelEntityTypeToString(LevelEntityType type) {
    switch (type)
    {
    case LevelEntityType::BOMBER:
        return "BOMBER";
    case LevelEntityType::IMPACT_BOMBER:
        return "IMPACT_BOMBER";
    case LevelEntityType::TANK:
        return "TANK";
    case LevelEntityType::GROUND_TO_GROUND_MISSILE:
        return "GROUND_TO_GROUND_MISSILE";
    case LevelEntityType::MINEFIELD:
        return "MINEFIELD";
    case LevelEntityType::CRATER:
        return "CRATER";
    case LevelEntityType::STONE:
        return "STONE";
    case LevelEntityType::BIG_STONE:
        return "STONE";
        break;
    default:
        throw std::runtime_error("Unknown level entity type");
    }
}

LevelEntityType Level::stringToGameLevelEntityType(const std::string& type) {
    if (type == "BOMBER") {
        return LevelEntityType::BOMBER;
    } else if (type == "IMPACT_BOMBER") {
        return LevelEntityType::IMPACT_BOMBER;
    } else if (type == "TANK") {
        return LevelEntityType::TANK;
    } else if (type == "GROUND_TO_GROUND_MISSILE") {
        return LevelEntityType::GROUND_TO_GROUND_MISSILE;
    } else if (type == "MINEFIELD") {
        return LevelEntityType::MINEFIELD;
    } else if (type == "CRATER") {
        return LevelEntityType::CRATER;
    } else if (type == "STONE") {
        return LevelEntityType::STONE;
    } else if (type == "BIG_STONE") {
        return LevelEntityType::BIG_STONE;
    } else {
        throw std::runtime_error("Unknown level entity type");
    }
}