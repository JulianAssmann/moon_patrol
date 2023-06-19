#include "font.h"

Font::Font(std::string path, std::shared_ptr<SDL_Renderer> renderer) :
    renderer(renderer), path(path) { }

Font::~Font() {
    if (cachedTexture) {
        SDL_DestroyTexture(cachedTexture);
    }

    TTF_CloseFont(font);
}

void Font::init(int fontSize) {

    this->fontSize = fontSize;
    std::cout << "Loading font " << path << std::endl;

    font = TTF_OpenFont(path.c_str(), fontSize);
    if (!font) {
        std::cout << "Unable to load font " << path.c_str() << "! SDL_TTF Error: " << TTF_GetError() << std::endl;
    } else {
        isLoaded = true;
    }
}

Rect Font::render(SDL_Rect rect, const char* text, SDL_Color color) {
    if (!isLoaded) {
        return Rect(rect);
    }

    std::string textStr = text;
    if (cachedText != textStr) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
        if (!textSurface) {
            std::cout << "Failed to render text: " << textSurface << "; SDL_TTF Error: " << TTF_GetError() << std::endl;
        }

        cachedTexture = SDL_CreateTextureFromSurface(renderer.get(), textSurface);
        cachedText = textStr;
        if (!cachedTexture) {
            std::cout << "Failed to create texture from surface: " << textSurface << "; SDL_TTF Error: " << TTF_GetError() << std::endl;
        }

        SDL_FreeSurface(textSurface);
    }

    SDL_RenderCopy(renderer.get(), cachedTexture, nullptr, &rect);
    return Rect(rect);
}

Rect Font::render(Rect rect, const char* text, SDL_Color color) {
    this->render(rect.toSDLRect(), text, color);
    return rect;
}

Rect Font::render(Vector2 position, const char* text, SDL_Color color) {
    Rect rect = Rect(position, this->getTextureSize(text));
    this->render(rect, text, color);
    return rect;
}

Size Font::getTextureSize(const char* text) {
    if (!isLoaded) {
        return Size(0, 0);
    }

    int w, h;
    TTF_SizeText(font, text, &w, &h);
    return Size(w, h);
}

Size Font::getTextureSize(std::string text) {
    return this->getTextureSize(text.c_str());
}