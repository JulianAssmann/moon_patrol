#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <SDL2/SDL.h>
#include "vector2.h"
#include "size.h"

/// @brief A rectangle with a position (x, y) and a size (width and height)
struct Rect
{
    /// @brief The x coordinate of the rectangle
    float x;

    /// @brief The y coordinate of the rectangle
    float y;

    /// @brief The width of the rectangle
    float width;

    /// @brief The height of the rectangle
    float height;

    /// @brief Create a rectangle
    /// @param x The x coordinate of the top left corner of the rectangle
    /// @param y The y coordinate of the top left corner of the rectangle
    /// @param width The width of the rectangle
    /// @param height The height of the rectangle
    Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

    /// @brief Create a rectangle
    /// @param x The x coordinate of the top left corner of the rectangle
    /// @param y The y coordinate of the top left corner of the rectangle
    /// @param size The size of the rectangle
    Rect(float x, float y, Size size) : x(x), y(y), width(size.width), height(size.height) {}

    /// @brief Create a rectangle
    /// @param position The top left corner of the rectangle
    /// @param width The width of the rectangle
    /// @param height The height of the rectangle
    Rect(Vector2 position, float width, float height) : x(position.x), y(position.y), width(width), height(height) {}

    /// @brief Create a rectangle
    /// @param position The top left corner of the rectangle
    /// @param size The size of the rectangle
    Rect(Vector2 position, Size size) : x(position.x), y(position.y), width(size.width), height(size.height) {}

    /// @brief Create a rectangle at position (0, 0) with size (0, 0)
    Rect() : x(0), y(0), width(0), height(0) {}

    /// @brief Convert the rectangle to a string
    /// @return The string representation of the rectangle
    std::string toString() const
    {
        return "Rect(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(width) + ", " + std::to_string(height) + ")";
    }

    /// @brief Create a rectangle from the center with the given width and height
    /// @param center The center of the rectangle
    /// @param width The width of the rectangle
    /// @param height The height of the rectangle
    /// @return A rectangle constructed from the given center with the given width and height
    static Rect fromCenter(Vector2 center, float width, float height)
    {
        return Rect(Vector2(center.x - width * 0.5f, center.y - height * 0.5f), width, height);
    }

    /// @brief Create a rectangle from the center with the given size
    /// @param x The x coordinate of the center of the rectangle
    /// @param y The y coordinate of the center of the rectangle
    /// @param size The size of the rectangle
    /// @return A rectangle constructed from the given center coordinates with the given size
    static Rect fromCenter(float x, float y, Size size)
    {
        return Rect(x - size.width * 0.5f, y - size.height * 0.5f, size.width, size.height);
    }

    /// @brief Create a rectangle from the center with the given width and height
    /// @param x The x coordinate of the center of the rectangle
    /// @param y The y coordinate of the center of the rectangle
    /// @param width The width of the rectangle
    /// @param height The height of the rectangle
    /// @return A rectangle constructed from the given center coordinates with the given width and height
    static Rect fromCenter(float x, float y, float width, float height)
    {
        return Rect(x - width * 0.5f, y - height * 0.5f, width, height);
    }

    /// @brief Create a rectangle from the point of the bottom center of the rectangle with the given size
    /// @param bottomCenter The bottom center of the rectangle
    /// @param size The size of the rectangle 
    /// @return A rectangle constructed with the given bottom center and size
    static Rect fromBottomCenter(Vector2 bottomCenter, Size size)
    {
        return Rect(bottomCenter.x - size.width * 0.5f, bottomCenter.y - size.height, size.width, size.height);
    }

    /// @brief Create a rectangle from the center with the given size
    /// @param center The center of the rectangle
    /// @param size The size of the rectangle
    /// @return A rectangle constructed from the given center with the given size
    static Rect fromCenter(Vector2 center, Size size)
    {
        return Rect(center.x - size.width * 0.5f, center.y - size.height * 0.5f, size.width, size.height);
    }

    /// @brief Converts the rectangle to an SDL_Rect
    /// @return The SDL_Rect
    SDL_Rect toSDLRect() const
    {
        return SDL_Rect{static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
    }

    /// @brief Check if the rectangle contains the given point
    /// @param point The point to check
    /// @return True if the rectangle contains the point, false otherwise
    bool contains(Vector2 point) const
    {
        return point.x >= x && point.x <= x + width && point.y >= y && point.y <= y + height;
    }

    /// @brief Check if the rectangle intersects with another rectangle
    /// @param other The other rectangle to check
    /// @return True if the rectangles intersect, false otherwise
    bool intersects(const Rect& other) const
    {
        return x < other.x + other.width &&
            x + width > other.x &&
            y < other.y + other.height &&
            y + height > other.y;
    }

    /// @brief Translates the rectangle by the given vector
    /// @param other The vector to translate by
    /// @return The translated rectangle
    Rect operator+(const Vector2& other) const
    {
        return Rect(x + other.x, y + other.y, width, height);
    }
    /// @brief Translates the rectangle by the given vector
    /// @param other The vector to translate by 
    /// @return The translated rectangle
    Rect operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    /// @brief Translates the rectangle by the negative direction of the given vector
    /// @param other The vector to translate by
    /// @return The translated rectangle
    Rect operator-(const Vector2& other) const
    {
        return Rect(x - other.x, y - other.y, width, height);
    }

    /// @brief Translates the rectangle by the negative direction of the given vector
    /// @param other The vector to translate by
    /// @return The translated rectangle
    Rect operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /// @brief Get the center of the rectangle
    /// @return The center of the rectangle
    Vector2 getCenter() const
    {
        return Vector2(x + width / 2, y + height / 2);
    }

    /// @brief Set the center of the rectangle
    /// @param center The new center of the rectangle
    void setCenter(Vector2 center)
    {
        x = center.x - width / 2;
        y = center.y - height / 2;
    }

    /// @brief Get the size of the rectangle
    /// @return The size of the rectangle
    Size getSize() const
    {
        return Size(width, height);
    }

    /// @brief Get the top left corner of the rectangle
    /// @return The top left corner of the rectangle
    Vector2 getTopLeft() const
    {
        return Vector2(x, y);
    }

    /// @brief Get the top right corner of the rectangle
    /// @return The top right corner of the rectangle
    Vector2 getTopRight() const
    {
        return Vector2(x + width, y);
    }

    /// @brief Get the bottom left corner of the rectangle
    /// @return The bottom left corner of the rectangle
    Vector2 getBottomLeft() const
    {
        return Vector2(x, y + height);
    }

    /// @brief Get the bottom right corner of the rectangle
    /// @return The bottom right corner of the rectangle
    Vector2 getBottomRight() const
    {
        return Vector2(x + width, y + height);
    }
};

#endif