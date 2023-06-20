#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../../../utils/rect.h"
#include "../../../utils/vector2.h"
#include "../../../utils/size.h"

class GameplayModel;

/// @brief The type of level entity.
/// @details This is used to determine the texture for the level entity.
enum class LevelEntityType {
    /// @brief A bomb dropped by a bomber
    BOMB,

    /// @brief A bomb dropped by an impact bomber (explodes on impact with the ground)
    IMPACT_BOMB,

    /// @brief A tank shell
    TANK_SHELL,

    /// @brief A bomber
    BOMBER,

    /// @brief An impact bomber
    IMPACT_BOMBER,

    /// @brief A minefield
    MINEFIELD,

    /// @brief A ground-to-ground missile
    GROUND_TO_GROUND_MISSILE,

    /// @brief A tank
    TANK,

    /// @brief A crater
    CRATER,

    /// @brief A stone
    STONE,

    /// @brief A big stone
    BIG_STONE,
};

/// @brief The type of attack, used to determine the warning lights
enum class LevelEntityAttackType {
    /// @brief Aerial attacks with bombs (bombers and impact bombers)
    AERIAL,

    /// @brief Ground-based attacks (minefields, ground-to-ground missiles and tanks)
    GROUND,

    /// @brief Terrain-based blockades (craters and stones)
    TERRAIN,

    /// @brief No attack warning lights
    NONE
};

enum class LevelEntityState {
    /// @brief The level entity is inactive and should not be updated and drawn
    WAITING_FOR_ACTIVATION,

    /// @brief The level entity is active and should be updated and drawn
    ACTIVE,

    /// @brief The level entity is dead and should be removed
    /// @details This is used for level entities that are destroyed or have reached the end of their life
    INACTIVE
};

/// @brief The base class for all level entities (enemies, craters, mines, etc.) that are not the player or the terrain
class LevelEntity {
public:
    /// @brief
    /// @param type The type of the level entity
    /// @param rect
    LevelEntity(LevelEntityType type, LevelEntityAttackType attackType, Vector2 startingPosition, Size size);
    LevelEntity(LevelEntityType type, LevelEntityAttackType attackType, Rect rect);

    /// @brief Updates the level entity
    /// @param model The gameplay model
    /// @param dt The delta time between frames in seconds
    virtual void update(GameplayModel& model, float dt);

    /// @brief Gets the rectangle of the level entity
    /// @return The rectangle of the level entity
    Rect getRect() const;

    /// @brief Gets the type of the level entity
    /// @return The type of the level entity
    LevelEntityType getType() const;

    /// @brief Gets the state of the level entity
    /// @return The state of the level entity
    LevelEntityState getState() const;

    /// @brief Activates the level entity so that it can be updated and drawn
    void activate(GameplayModel& model);

    /// @brief Destroys the level entity, i.e. sets its state to INACTIVE to indicate that it should be removed
    void destroy(GameplayModel& model);
protected:
    Rect rect;
    LevelEntityType type;
    LevelEntityState state;
    LevelEntityAttackType attackType;

    virtual void onActivation(GameplayModel& model);
};

#endif // GAME_OBJECT_H