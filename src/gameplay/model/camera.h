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
    /// @brief Creates a camera with a screen size of (0, 0) at world position (0, 0)
    Camera();

    /// @brief Creates a camera with the given screen size at world position (0, 0)
    /// @param screenSize The size of the camera (in pixels)
    Camera(Size screenSize, float uiHeight = 0.2f);

    /// @brief Creates a camera with the given position and screen size
    /// @param position The position of the camera (in world coordinates)
    /// @param screenSize The size of the camera (in pixels)
    Camera(Vector2 position, Size screenSize, float uiHeight = 0.2f);

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

    /// @brief Transforms the rectangle from UI space to screen space
    /// @param uiRect The rectangle to transform from UI space to screen space
    /// @return The transformed rectangle
    Vector2 uiToScreen(const Vector2& uiPos) const;

    /// @brief Transforms the vector from screen space to UI space
    /// @param screenPos The vector to transform from screen space to UI space
    /// @return The transformed vector
    Vector2 screenToUI(const Vector2& screenPos) const;

    /// @brief Transforms the rectangle from UI space to screen space
    /// @param uiRect The rectangle to transform from UI space to screen space
    /// @return The transformed rectangle
    Rect uiToScreen(const Rect& uiRect) const;

    /// @brief Transforms the vector from screen space to UI space
    /// @param screenPos The vector to transform from screen space to UI space
    /// @return The transformed vector
    Rect screenToUI(const Rect& screenRect) const;

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

    /// @brief Get the height of the UI in camera space
    /// @return The height of the UI in camera space
    float getUIHeight() const;

    /// @brief Set the height of the UI in camera space
    /// @param uiHeight The height of the UI in camera space
    void setUIHeight(float uiHeight);

    /// @brief Get the aspect ratio of the camera for the gameplay area (width / height)
    float getAspectRatio() const;

    /// @brief Get the aspect ratio of the camera for the UI area (width / height)
    float getUIAspectRatio() const;
private:
    /// @brief The screen space size of the camera
    Size screenSize;

    /// @brief The camera position in world space
    Vector2 position;

    /// @brief The height of the UI in camera space
    float uiHeight;
};

#endif // !CAMERA_H