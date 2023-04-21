#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/// @brief A class to load and manage a texture atlas
class TextureAtlas {
public:
    /// @brief Create a texture atlas from the given texture and info file
    /// @param renderer The renderer to use to create the texture
    /// @param textureFile The file containing the texture
    /// @param infoFile The file containing the texture info
    TextureAtlas(std::shared_ptr<SDL_Renderer> renderer, const std::string& textureFile, const std::string& infoFile);

    /// @brief Get the texture
    /// @return The texture
    std::shared_ptr<SDL_Texture> getTexture();

    /// @brief Check if the sprite exists
    /// @param spriteName The name of the sprite
    /// @return True if the sprite exists, false otherwise
    bool doesSpriteExist(const std::string& spriteName);

    /// @brief Get the source rectangle containing the sprite of the given name
    /// @param spriteName The name of the sprite
    /// @return The source rectangle containing the sprite in the atlas
    SDL_Rect getSourceRectForSprite(const std::string& spriteName);

private:
    // The texture that contains all the textures
    std::shared_ptr<SDL_Texture> atlasTexture;

    // A map of texture names to source rectangles
    std::map<std::string, SDL_Rect> textureInfoMap;


};

#endif // TEXTURE_ATLAS_H

