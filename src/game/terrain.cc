#include "terrain.h"

Terrain::Terrain(float base_height, int num_segments, float segment_dy, float deviation, int random_seed) :
    base_height(base_height), 
    num_segments(num_segments), 
    max_height_deviation(deviation),
    segment_width(1.0f / num_segments),
    segment_dy(segment_dy),
    last_segment_x(0.0f),
    last_segment_height(base_height),
    terrain_segments(std::vector<Rect>(num_segments)) {

    // Initialize the random number generator
    this->gen = std::mt19937(random_seed);
    this->height_change_distribution = std::uniform_int_distribution<>(0, total_probability);
}

std::vector<Rect> Terrain::getTerrainSegments() const {
    return this->terrain_segments;
}

void Terrain::generateTerrainTo(float x) {
    while (this->last_segment_x < x) {
        this->generateTerrainSegment(this->last_segment_x);
    }
}

void Terrain::generateTerrainSegment(float x) {
    // Generate a random number between 0 and 4 to determine the height change
    int random_number = this->height_change_distribution(this->gen);

    // As we want the terrain to have a more natural look,
    // the probability of direction of the height change to be
    // the same as the last segment is higher than the probability
    // of the height change to be the opposite of the last segment
    // or to be 0

    int consecutive_flat_probability = 2; // 10 in 100 chance of consecutive flat terrain (10%)
    int other_direction_probability = 28; // 30 in 100 chance of height change in the opposite direction (30%)

    if (abs(last_segment_height - base_height) > max_height_deviation) {
        consecutive_flat_probability = 10;
        other_direction_probability = 90;
    }
    

    std::discrete_distribution<int> dist;
    if (last_segment_dy > 0) {
        dist = std::discrete_distribution<>({
            static_cast<double>(other_direction_probability),
            static_cast<double>(consecutive_flat_probability),
            static_cast<double>(total_probability - other_direction_probability - consecutive_flat_probability)
        });
    } else if (last_segment_dy < 0) {
        dist = std::discrete_distribution<>({
            static_cast<double>(total_probability - other_direction_probability - consecutive_flat_probability),
            static_cast<double>(consecutive_flat_probability),
            static_cast<double>(other_direction_probability)
        });
    } else {
        int up_down_probability = (total_probability - consecutive_flat_probability) / 2;
        dist = std::discrete_distribution<>({
            static_cast<double>(up_down_probability),
            static_cast<double>(consecutive_flat_probability),
            static_cast<double>(up_down_probability)
        });
    }

    // Determine the height change based on the outcome of the randomly generated
    // number and probabilities specified in the discrete distribution
    int choice = dist(this->gen);
    float diff = 0.0f;
    switch (choice) {
        case 0:
            diff = -segment_dy;
            break;
        case 1:
            diff = 0;
            break;
        case 2:
            diff = segment_dy;
            break;
    }

    iterations_with_same_dy += diff == std::min(consecutive_flat_probability, last_segment_dy ? 1 : -iterations_with_same_dy);

    // Calculate the new height
    float height = this->last_segment_height + diff;
    
    // Clamp the height to the base height +- max height deviation
    if (height > base_height + max_height_deviation) {
        height = base_height + max_height_deviation;
    } else if (height < base_height - max_height_deviation) {
        height = base_height - max_height_deviation;
    }
    
    this->terrain_segments.push_back(Rect(x, height, segment_width * 1.1f, 1.0f - height));

    this->last_segment_x = x + segment_width;
    this->last_segment_height = height;
    this->last_segment_dy = diff;
}

void Terrain::removeTerrainTo(float x) {
    this->terrain_segments.erase(
        std::remove_if(
            this->terrain_segments.begin(), 
            this->terrain_segments.end(), 
            [x](Rect segment) { return segment.x < x; }
        ), 
        this->terrain_segments.end()
    );
}

void Terrain::generateCrater(Vector2 position, Size size) {
    for (int i = 0; i < this->terrain_segments.size(); i++) {
        Rect segment = this->terrain_segments[i];
        if (segment.x < position.x + size.width && segment.x + segment.width > position.x) {
            if (segment.y < position.y + size.height && segment.y + segment.height > position.y) {
                this->terrain_segments.erase(this->terrain_segments.begin() + i);
                i--;
            }
        }
    }
}

float Terrain::getHeightAt(float x) const {
    for (int i = 0; i < this->terrain_segments.size(); i++) {
        Rect segment = this->terrain_segments[i];
        if (segment.x < x && segment.x + segment.width > x) {
            return segment.y;
        }
    }
    return 0.0f;
}