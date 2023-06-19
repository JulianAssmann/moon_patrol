#ifndef TERRAIN_H
#define TERRAIN_H

#include <random>
#include <vector>
#include <cmath>
#include <iostream>
#include "../../utils/rect.h"
#include "../../utils/vector2.h"

class Terrain {
public:
    /// @brief Initialize the terrain
    /// @param base_height The base height of the terrain
    Terrain(float base_height, int num_segments, float segment_dy = 0.005, float deviation = 0.03, int random_seed = 42);

    /// @brief Generate terrain segments until the given x position
    /// @param x The x position to generate terrain to
    void generateTerrainTo(float x);

    /// @brief Remove terrain segments until the given x position
    /// @param x The x position to remove terrain to
    void removeTerrainTo(float x);

    /// @brief Get the terrain segments
    /// @return The terrain segments
    std::vector<Rect> getTerrainSegments() const;

    /// @brief Get the height of the terrain at the given x position
    /// @param x The x position to get the height at
    /// @return The height of the terrain at the given x position
    float getHeightAt(float x) const;

    /// @brief Generate a crater at the given position with the given size
    /// @param x The x position of the crater
    /// @param size The size of the crater
    void generateCrater(float x, Size size);
private:

    /// @brief Generate a terrain segment at the given x position
    /// @param x The x position to generate terrain at
    void generateTerrainSegment(float x);

    /// @brief The number of terrain segments visible at once
    int num_segments = 300;

    /// @brief The width of each terrain segment
    float segment_width;

    /// @brief The last generated segment's x position
    float last_segment_x;

    /// @brief The last generated segment's height
    float last_segment_height;

    /// @brief The maximum height deviation from the base height
    float max_height_deviation;

    /// @brief The terrain segments
    std::vector<Rect> terrain_segments;

    /// @brief The base height of the terrain
    float base_height;

    /// @brief The last generated segment's dy
    float last_segment_dy = 0;

    /// @brief The difference in height between two segments
    float segment_dy = 0.02f;

    const int total_probability = 100;

    static const int crater_segments_per_segment = 3;

    // The random number generator
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> height_change_distribution;
};

#endif // TERRAIN_H