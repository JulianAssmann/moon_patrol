#include "texture_atlas.h"

TextureAtlas::TextureAtlas(std::shared_ptr<SDL_Renderer> renderer, const std::string& textureFile, const std::string& infoFile) {
    // Load the texture
    SDL_Surface* surface = IMG_Load(textureFile.c_str());

    // Check for errors
    if (surface == nullptr) {
        std::cerr << "Failed to load texture atlas: " << IMG_GetError() << std::endl;
        return;
    }

    renderer.get();
    // Create the texture
    atlasTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer.get(), surface), SDL_DestroyTexture);
    SDL_CreateTextureFromSurface(renderer.get(), surface);
    SDL_FreeSurface(surface);

    // Read the info file that specifies the location of each texture
    std::ifstream file(infoFile);
    std::string line;
    while (std::getline(file, line)) {
        // Read the texture name and the x, y, width, and height
        std::istringstream iss(line);
        std::string textureName;
        SDL_Rect info;
        char comma;

        iss >> textureName >> comma >> info.x >> comma >> info.y >> comma >> info.w >> comma >> info.h;
        textureInfoMap[textureName] = info;
    }
}


std::shared_ptr<SDL_Texture> TextureAtlas::getTexture() {
    return atlasTexture;
}

SDL_Rect TextureAtlas::getSourceRectForSprite(const std::string& spriteName) {
    return textureInfoMap[spriteName];
}