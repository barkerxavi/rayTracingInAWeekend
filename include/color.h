#ifndef COLOR_H
#define COLOR_H

#include <vec3.h>
#include <vector>
#include <cstdint>
#include <interval.h>

using color = vec3;

// Appends RGB values to the vector at a given index and updates the index
inline uint8_t* convertNormalisedToBit(uint8_t* pixels, int& index, const color& pixelColor) {
    
    static const interval intensity (0.000, 0.999);
    auto r = static_cast<int>(255.999 * intensity.clamp(pixelColor.x()));
    auto g = static_cast<int>(255.999 * intensity.clamp(pixelColor.y()));
    auto b = static_cast<int>(255.999 * intensity.clamp(pixelColor.z()));


    
    pixels[index++] = static_cast<uint8_t>(r);
    pixels[index++] = static_cast<uint8_t>(g);
    pixels[index++] = static_cast<uint8_t>(b);

    return pixels; // returns reference to the same vector
}

#endif
