#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <string>

struct Vector2
{
    float x;
    float y;

    constexpr Vector2(float x, float y) : x(x), y(y) {}
    constexpr Vector2() : x(0), y(0) {}

    std::string toString() const
    {
        return "Vector2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(const float& other) const
    {
        return Vector2(x * other, y * other);
    }
    Vector2 operator/(const float& other) const
    {
        float inv = 1.0f / other;
        return Vector2(x * inv, y * inv);
    }

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(const float& other)
    {
        x *= other;
        y *= other;
        return *this;
    }
    Vector2& operator/=(const float& other)
    {
        float inv = 1.0f / other;
        x *= inv;
        y *= inv;
        return *this;
    }
    
    float lengthSquared() const
    {
        return x * x + y * y;
    }

    float length() const
    {
        return sqrt(lengthSquared());
    }

    Vector2& normalize()
    {
        float len = length();
        if (len > 0.0f)
        {
            float inv = 1.0f / len;
            x *= inv;
            y *= inv;
        }
        return *this;
    }

    Vector2 normalized() const
    {
        Vector2 result = *this;
        result.normalize();
        return result;
    }

    float dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    float cross(const Vector2& other) const
    {
        return x * other.y - y * other.x;
    }

    Vector2& rotate(float angle)
    {
        float s = sin(angle);
        float c = cos(angle);
        float nx = x * c - y * s;
        float ny = x * s + y * c;
        x = nx;
        y = ny;
        return *this;
    }
};

#endif // VECTOR2_H