#ifndef SIZE_H
#define SIZE_H

#include <string>

struct Size {
    float width;
    float height;

    constexpr Size(int width, int height) : width(width), height(height) { }
    constexpr Size(float width, float height) : width(width), height(height) { }
    constexpr Size() : width(0), height(0) { }

    bool operator==(const Size &other) const {
        return width == other.width && height == other.height;
    }

    bool operator!=(const Size &other) const {
        return !(*this == other);
    }

    Size operator+(const Size &other) const {
        return Size(width + other.width, height + other.height);
    }
    Size operator+=(const Size &other) {
        width += other.width;
        height += other.height;
        return *this;
    }

    Size operator-(const Size &other) const {
        return Size(width - other.width, height - other.height);
    }
    Size operator-=(const Size &other) {
        width -= other.width;
        height -= other.height;
        return *this;
    }

    Size operator*(float factor) const {
        return Size(width * factor, height * factor);
    }
    Size operator*= (float factor) {
        width *= factor;
        height *= factor;
        return *this;
    }

    std::string toString() {
        return "Size(" + std::to_string(width) + ", " + std::to_string(height) + ")";
    }
};

#endif // SIZE_H