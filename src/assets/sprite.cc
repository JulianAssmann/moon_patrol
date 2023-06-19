#include "sprite.h"

Sprite::Sprite(std::string path, std::shared_ptr<SDL_Renderer> renderer) : renderer(renderer), path(path) { }

void Sprite::render(Rect rect, SDL_Color color) const {
    this->render(rect.toSDLRect(), color);
}

void Sprite::render(SDL_Rect rect, SDL_Color color) const
{
    if (is_loaded) {
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_RenderCopy(renderer.get(), texture, NULL, &rect);
    }
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::init()
{
    std::cout << "Loading sprite " << path << std::endl;

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        // Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
        if (texture == NULL)
        {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            size = Size(surface->w, surface->h);
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(surface);

        // Enable blending for the texture
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

        is_loaded = true;
    }
}
