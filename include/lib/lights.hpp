#pragma once
#include "pros/adi.hpp"
#include "lib/TaskWrapper.hpp"
#include <vector>



struct RGB {
    uint8_t r, g, b;
    RGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};
struct HSV {
    double h; // Range: 0-360 (degrees)
    double s; // Range: 0-1 (percentage, normalized)
    double v; // Range: 0-1 (percentage, normalized)
    HSV(double h, double s, double v) : h(h), s(s), v(v) {}
};



RGB hsvToRgb(const HSV &hsv);

int RgbToHex(RGB color);

std::vector<int> readImage(const char *filename);

int wrapDegrees(float degrees);

float lerpf(float from, float to, float alpha);

std::vector<int> interpolateSingle(HSV start, HSV end, int length);

std::vector<int> interpolateDouble(HSV start, HSV end, int length);



namespace lib {



class Light : public pros::adi::Led, public ryan::TaskWrapper {
protected:
    bool on = true;
    uint tickDelay = 10;

public:
    Light(uint port, uint length, uint delay = 10)
    : pros::adi::Led(port, length), tickDelay(delay)
    { startTask(); }

    void turn(bool on) {
        this->on = on;
        if (!on) { clear(); }
    }

    void loop() override {
        while (true) {
            if (on) { update(); }
            pros::delay(tickDelay);
        }
    }
    virtual void update() {}
};



class FlowingGradient : public Light {
protected:
    uint ticksPassed = 0;

    std::vector<int> blueGradient;
    std::vector<int> redGradient;

    void update() override;

public:
    FlowingGradient(uint port, uint length, std::vector<int> redGradient, std::vector<int> blueGradient, uint delay = 10)
    : Light(port, length, delay), redGradient(redGradient), blueGradient(blueGradient) {}
};



class BreathingGradient : public Light {
protected:
    uint ticksPassed = 0;

    std::vector<int> blueGradient;
    std::vector<int> redGradient;

    void update() override;

public:
    BreathingGradient(uint port, uint length, std::vector<int> redGradient, std::vector<int> blueGradient, uint delay = 10)
    : Light(port, length, delay), redGradient(redGradient), blueGradient(blueGradient) {}
};



class AnimationReader : public Light {
protected:
    bool playDirection = false;
    uint playPosition = 0;
    uint animationLength;
    
    std::vector<int> redAnimation;
    std::vector<int> blueAnimation;

    void update() override;

public:
    AnimationReader(uint port, uint length, std::vector<int> redAnimation, std::vector<int> blueAnimation, uint delay = 10)
        : Light(port, length, delay), redAnimation(redAnimation), blueAnimation(blueAnimation)
        { animationLength = redAnimation.size() / length; }

    void setDirection(bool dir) { playDirection = dir; };
};

}