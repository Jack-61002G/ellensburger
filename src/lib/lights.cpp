#include "lib/lights.hpp"
#include "robotconfig.h"
#include <cmath>
#include <vector>



RGB hsvToRgb(HSV color) {
    RGB output(0, 0, 0);

    // Ensure the hue is between 0 and 360 degrees
    color.h = fmod(color.h, 360);
    if (color.h < 0) color.h += 360;

    // Handle the case where saturation is 0 (it's a shade of gray)
    if (color.s == 0) {
        output.r = output.g = output.b = color.v * 255; // All the same value
    } else {
        // Normalize hue to [0, 360]
        color.h /= 60.0f;
        int i = static_cast<int>(color.h);
        float f = color.h - i;
        float p = color.v * (1 - color.s);
        float q = color.v * (1 - f * color.s);
        float t = color.v * (1 - (1 - f) * color.s);

        // Assign colors based on the sector
        switch (i) {
            case 0: output.r = color.v, output.g = t, output.b = p; break;
            case 1: output.r = q, output.g = color.v, output.b = p; break;
            case 2: output.r = p, output.g = color.v, output.b = t; break;
            case 3: output.r = p, output.g = q, output.b = color.v; break;
            case 4: output.r = t, output.g = p, output.b = color.v; break;
            case 5: output.r = color.v, output.g = p, output.b = q; break;
        }

        // Scale the RGB values to [0, 255]
        output.r *= 255;
        output.g *= 255;
        output.b *= 255;
    }

    // Return the result as an RGB struct
    return output;
}


int RgbToHex(RGB color) {
    return (static_cast<uint32_t>(color.r) << 16) | (static_cast<uint32_t>(color.g) << 8) | static_cast<uint32_t>(color.b);
}


std::vector<int> readImage(const char *filename) {
    FILE *f = fopen(filename, "rb");
    unsigned char info[54];
  
    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);
  
    // extract image height and width from header
    int width = *(int *)&info[18];
    int height = *(int *)&info[22];
  
    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    unsigned char *data = new unsigned char[size];
  
    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f);
    fclose(f);
    
    std::vector<int> output;
    output.reserve(width * height);
    int i = 0;
    while (i < size) {
        output.push_back(RgbToHex(RGB(data[i], data[i + 1], data[i + 2])));
        i += 3;
    }
    return output;
}


int wrapDegrees(float degrees) {
    while (degrees > 360) {
        degrees -= 360;
    }
    while (degrees < 0) {
        degrees += 360;
    }
    return degrees;
}


float lerpf(float from, float to, float alpha) {
    return from * (1.0 - alpha) + to * alpha;
}


std::vector<int> interpolateSingle(HSV start, HSV end, int length) {
    std::vector<int> result;
    result.reserve(length);

    for (int i = 0; i < length; i++) {
        float alpha = static_cast<float>(i) / static_cast<float>(length);

        HSV hsv(lerpf(start.h, end.h, alpha), lerpf(start.s, end.s, alpha), lerpf(start.v, end.v, alpha));

        hsv.h = wrapDegrees(hsv.h);

        result.emplace_back(RgbToHex(hsvToRgb(hsv)));
    }
    return result;
}


std::vector<int> interpolateDouble(HSV start, HSV end, int length) {

    if (length % 2 == 1) { length++; }

    std::vector<int> result;
    result.reserve(length);

    for (int i = 0; i < length / 2; i++) {
        float alpha = static_cast<float>(i) / static_cast<float>(length);

        HSV hsv(lerpf(start.h, end.h, alpha), lerpf(start.s, end.s, alpha), lerpf(start.v, end.v, alpha));

        hsv.h = wrapDegrees(hsv.h);

        result.emplace_back(RgbToHex(hsvToRgb(hsv)));
    }
    for (int i = length / 2; i > 0; i--) {
        float alpha = static_cast<float>(i) / static_cast<float>(length);

        HSV hsv(lerpf(start.h, end.h, alpha), lerpf(start.s, end.s, alpha), lerpf(start.v, end.v, alpha));

        hsv.h = wrapDegrees(hsv.h);

        result.emplace_back(RgbToHex(hsvToRgb(hsv)));
    }
    return result;
}



void lib::FlowingGradient::update() {
    ticksPassed++; 
    for (int i = 0; i < length(); i++) {
        set_pixel(
            teamColor == team::blue ? blueGradient[(i + ticksPassed) % blueGradient.size()]
            : redGradient[(i + ticksPassed) % redGradient.size()],
            i);
    }
}



void lib::BreathingGradient::update() {
    ticksPassed++; 
    set_all( teamColor == team::blue ? blueGradient[ticksPassed % blueGradient.size()]
            : redGradient[ticksPassed % redGradient.size()]);
}



void lib::AnimationReader::update() {
    if (playDirection) { playPosition = std::min(playPosition + 1, animationLength); }
    else { playPosition = std::max(int(playPosition) - 1, 0); }
    
    for (int i = 0; i < length(); i++) {
        set_pixel(
            teamColor == team::blue ? blueAnimation[i * animationLength + playPosition]
            : redAnimation[i * animationLength + playPosition],
            i);
    }
}
