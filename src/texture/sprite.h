#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include "texture_atlas.h"
#include "sprite.h"
#include "../utils/size.h"
#include "../utils/rect.h"

/// @brief A sprite is a texture that can be rendered
class Sprite
{
public:
    /// @brief Create a sprite from the given image
    /// @param path The path to the image
    /// @param renderer The renderer to use
    Sprite(std::string path, std::shared_ptr<SDL_Renderer> renderer);

    /// @brief Destroy the sprite and free resources used by it
    virtual ~Sprite();

    /// @brief Load the sprite
    virtual void init();

    /// @brief Render the sprite
    /// @param rect The rectangle to render the sprite in
    virtual void render(SDL_Rect rect) const;

    /// @brief Render the sprite
    /// @param rect The rectangle to render the sprite in
    virtual void render(Rect rect) const;

    /// @brief Get the size of the sprite
    /// @return The size of the sprite
    Size getSize() const { return size; }
protected:
    SDL_Texture* texture;
    std::shared_ptr<SDL_Renderer> renderer;
    Size size;
    std::string path;
    bool is_loaded = false;
};

#endif // SPRITE_H