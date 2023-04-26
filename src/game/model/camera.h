#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "../../utils/rect.h"
#include "../../utils/vector2.h"
#include "../../utils/size.h"

/// @brief A camera with a position in world space and a size in screen space
/// that is used to transform between world space, camera space and screen space
class Camera {
public:
    Camera();

    /// @brief Creates a camera with the given screen size at world position (0, 0)
    /// @param screenSize The size of the camera (in pixels)
    Camera(Size screenSize);

    /// @brief Creates a camera with the given position and screen size
    /// @param position The position of the camera (in world coordinates)
    /// @param screenSize The size of the camera (in pixels)
    Camera(Vector2 position, Size screenSize);

    /// @brief Transforms the rectangle from camera space to world space
    /// @param worldRect The rectangle to transform from camera space to world space
    /// @return The transformed rectangle
    Rect cameraToWorld(const Rect& worldRect) const;

    /// @brief Transforms the worldPos from camera space to world space
    /// @param worldPos The vector to transform from camera space to world space
    /// @return The transformed vector
    Vector2 cameraToWorld(const Vector2& worldPos) const;

    /// @brief Transforms the rectangle from world space to camera space
    /// @param worldRect The rectangle to transform from world space to camera space
    /// @return The transformed rectangle
    Rect worldToCamera(const Rect& worldRect) const;

    /// @brief Transforms the vector from world space to camera space
    /// @param worldPos The vector to transform from world space to camera space
    /// @return The transformed vector
    Vector2 worldToCamera(const Vector2& worldPos) const;

    /// @brief Transforms the rectangle from camera space to screen space
    /// @param cameraRect The rectangle to transform from camera space to screen space
    /// @return The transformed rectangle
    Rect worldToScreen(const Rect& worldRect) const;

    /// @brief Transforms the vector from camera space to screen space
    /// @param cameraPos The vector to transform from camera space to screen space
    /// @return The transformed vector
    Vector2 worldToScreen(const Vector2& worldPos) const;

    /// @brief Transforms the rectangle from screen space to camera space
    /// @param screenRect The rectangle to transform from screen space to camera space
    /// @return The transformed rectangle
    Rect screenToWorld(const Rect& screenRect) const;

    /// @brief Transforms the vector from screen space to camera space
    /// @param screenPos The vector to transform from screen space to camera space
    /// @return The transformed vector
    Vector2 screenToWorld(const Vector2& screenPos) const;

    /// @brief Transforms the rectangle from screen space to camera space
    /// @param screenRect The rectangle to transform from screen space to camera space
    /// @return The transformed rectangle
    Rect screenToCamera(const Rect& screenRect) const;

    /// @brief Transforms the vector from screen space to camera space
    /// @param screenPos The vector to transform from screen space to camera space
    /// @return The transformed vector
    Vector2 screenToCamera(const Vector2& screenPos) const;

    /// @brief Transforms the rectangle from camera space to screen space
    /// @param cameraRect The rectangle to transform from camera space to screen space
    /// @return The transformed rectangle
    Rect cameraToScreen(const Rect& cameraRect) const;

    /// @brief Transforms the vector from camera space to screen space
    /// @param cameraPos The vector to transform from camera space to screen space
    /// @return The transformed vector
    Vector2 cameraToScreen(const Vector2& cameraPos) const;
    
    /// @brief Set the position of the camera
    /// @param x The x coordinate of the camera
    /// @param y The y coordinate of the camera
    void setPosition(float x, float y);

    /// @brief Set the position of the camera
    /// @param position The position of the camera
    void setPosition(Vector2 position);

    /// @brief Move the camera
    /// @param dx The x translation of the camera
    /// @param dy The y translation of the camera
    void move(float dx, float dy);

    /// @brief Move the camera
    /// @param translation The translation of the camera
    void move(Vector2 translation);

    /// @brief Update the size of the camera
    /// @param size The new size of the camera
    void setSize(Size size);

    /// @brief Get the position of the camera
    /// @return The position of the camera
    Vector2 getPosition() const;

    /// @brief Get the size of the camera
    /// @return The size of the camera
    Size getSize() const;

    /// @brief Get the rectangle representing the camera
    /// @return The rectangle representing the camera
    Rect getCamera() const;

private:
    /// @brief The screen space size of the camera
    Size screenSize;

    /// @brief The camera position in world space
    Vector2 position;
};

#endif // !CAMERA_H