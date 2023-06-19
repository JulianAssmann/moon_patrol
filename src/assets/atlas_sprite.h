#ifndef ATLAS_SPRITE_H
#define ATLAS_SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include "texture_atlas.h"
#include "sprite.h"
#include "../utils/size.h"

/// @brief A sprite that uses a texture atlas
class AtlasSprite : public Sprite
{
public:
    /// @brief Create a texture from the given texture atlas
    /// @param name The name of the texture
    /// @param atlas The texture atlas to use
    AtlasSprite(std::string name, std::shared_ptr<TextureAtlas> atlas, std::shared_ptr<SDL_Renderer> renderer);

    /// @brief Destroy the texture and free resources used by it
    virtual ~AtlasSprite();

    /// @brief Load the sprite from the texture atlas
    virtual void init() override;

    /// @brief Render the texture
    /// @param rect The rectangle to render the texture in
    void render(SDL_Rect rect, SDL_Color color = {255, 255, 255, 255});

private:
    std::shared_ptr<TextureAtlas> atlas;
    SDL_Rect src_rect;
};

#endif // ATLAS_SPRITE_H