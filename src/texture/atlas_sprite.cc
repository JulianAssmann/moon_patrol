#include "atlas_sprite.h"

AtlasSprite::AtlasSprite(std::string name, std::shared_ptr<TextureAtlas> atlas, std::shared_ptr<SDL_Renderer> renderer)
        : Sprite(name, renderer), atlas(atlas) { }

AtlasSprite::~AtlasSprite() { }

void AtlasSprite::init()
{
    this->src_rect = atlas.get()->getSourceRectForSprite(this->path);
    is_loaded = true;
}

void AtlasSprite::render(SDL_Rect rect, SDL_Color color) {
    SDL_SetTextureColorMod(atlas->getTexture().get(), color.r, color.g, color.b);
    SDL_RenderCopy(renderer.get(), atlas->getTexture().get(), &src_rect, &rect);
}
