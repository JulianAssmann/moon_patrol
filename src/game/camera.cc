#include "camera.h"

Camera::Camera() : position(0, 0), screenSize(1, 1) { }

Camera::Camera(Size screenSize) : position(0, 0), screenSize(screenSize) { }

Camera::Camera(Vector2 position, Size screenSize) : position(position), screenSize(screenSize) { }

Vector2 Camera::worldToCamera(const Vector2& worldPos) const {
    return Vector2(worldPos.x - position.x, worldPos.y - position.y);
}

Vector2 Camera::cameraToScreen(const Vector2& cameraPos) const {
    return Vector2(cameraPos.x * screenSize.width, cameraPos.y * screenSize.height);
}

Vector2 Camera::worldToScreen(const Vector2& worldPos) const {
    return cameraToScreen(worldToCamera(worldPos));
}

Rect Camera::worldToCamera(const Rect& worldRect) const {
    Vector2 topLeft = worldToCamera(Vector2(worldRect.x, worldRect.y));
    return Rect(topLeft.x, topLeft.y, worldRect.width, worldRect.height);
}

Rect Camera::cameraToScreen(const Rect& cameraRect) const {
    Vector2 topLeft = cameraToScreen(Vector2(cameraRect.x, cameraRect.y));
    return Rect(topLeft.x, topLeft.y, cameraRect.width * screenSize.width, cameraRect.height * screenSize.height);
}

Rect Camera::worldToScreen(const Rect& worldRect) const {
    return cameraToScreen(worldToCamera(worldRect));
}

Vector2 Camera::screenToWorld(const Vector2& screenPos) const {
    return cameraToWorld(screenToCamera(screenPos));
}

Vector2 Camera::screenToCamera(const Vector2& screenPos) const {
    return Vector2(screenPos.x / screenSize.width, screenPos.y / screenSize.height);
}

Vector2 Camera::cameraToWorld(const Vector2& cameraPos) const {
    return Vector2(cameraPos.x + position.x, cameraPos.y + position.y);
}

Rect Camera::screenToWorld(const Rect& screenRect) const {
    return cameraToWorld(screenToCamera(screenRect));
}

Rect Camera::screenToCamera(const Rect& screenRect) const {
    Vector2 topLeft = screenToCamera(Vector2(screenRect.x, screenRect.y));
    return Rect(topLeft.x / screenSize.width, topLeft.y / screenSize.height, screenRect.width / screenSize.width, screenRect.height / screenSize.height);
}

Rect Camera::cameraToWorld(const Rect& cameraRect) const {
    Vector2 topLeft = cameraToWorld(Vector2(cameraRect.x, cameraRect.y));
    return Rect(topLeft.x, topLeft.y, cameraRect.width, cameraRect.height);
}

void Camera::move(float dx, float dy) {
    move(Vector2(dx, dy));
}

void Camera::move(Vector2 translation) {
    position += translation;
}

void Camera::setSize(Size size) {
    this->screenSize = size;
}

void Camera::setPosition(float x, float y) {
    this->position = Vector2(x, y);
}

void Camera::setPosition(Vector2 position) {
    this->position = position;
}

Vector2 Camera::getPosition() const {
    return position;
}

Size Camera::getSize() const {
    return screenSize;
}