#ifndef FONT_H
#define FONT_H

#include <string>
#include <memory>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../utils/rect.h"
#include "../utils/size.h"
#include "../utils/vector2.h"

/// @brief A class for rendering text to the screen
class Font {
public:
    /// @brief Create a new font
    /// @param path The path to the font file
    /// @param renderer The renderer to use to render the font
    /// @param fontSize The size of the font
    Font(std::string path, std::shared_ptr<SDL_Renderer> renderer);

    /// @brief Initialize the font
    /// @param fontSize The size of the font
    void init(int fontSize);

    /// @brief Destroy the font
    virtual ~Font();

    /// @brief Render text to the screen into a the given rectangle
    /// @param rect The rectangle to render the text into
    /// @param text The text to render
    /// @param color The color of the text
    /// @return The rectangle that the text was rendered into
    Rect render(SDL_Rect rect, const char* text, SDL_Color color);

    /// @brief Render text to the screen into a the given rectangle
    /// @param rect The rectangle to render the text into
    /// @param text The text to render
    /// @param color The color of the text
    /// @return The rectangle that the text was rendered into
    Rect render(Rect rect, const char* text, SDL_Color color);

    /// @brief Render text to the screen at the given position
    /// @param position The position to render the text at
    /// @param text The text to render
    /// @param color The color of the text
    /// @return The rectangle that the text was rendered into
    Rect render(Vector2 position, const char* text, SDL_Color color);

    /// @brief Get the size of the texture that would be rendered for the given text
    /// @param text The text to get the size of
    Size getTextureSize(const char* text);

    /// @brief Get the size of the texture that would be rendered for the given text
    /// @param text The text to get the size of
    Size getTextureSize(std::string text);
private:
    TTF_Font* font;
    std::shared_ptr<SDL_Renderer> renderer;
    std::string path;
    bool isLoaded = false;
    int fontSize;
    std::string cachedText;
    SDL_Texture* cachedTexture;
};

#endif // FONT_H