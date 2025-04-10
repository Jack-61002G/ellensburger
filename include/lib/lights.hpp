#pragma once
#include "lights.hpp"
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

std::vector<RGB> interpolateSingle2(HSV start, HSV end, int length);

std::vector<int> interpolateDouble(HSV start, HSV end, int length);



namespace lib {



class Light : public pros::adi::Led {
protected:
    bool on = true;

public:
    Light(uint port, uint length, uint tick = 10, uint delay = 0) : pros::adi::Led(port, length) {}

    void turn(bool on) {
        this->on = on;
        if (!on) { clear(); }
    }

    virtual void update() {}
};



class LightManager : public ryan::TaskWrapper {
private:
    Light* arm;
    Light* intake;
    Light* clamp;
    Light* left;
    Light* right;

public:
    LightManager(Light* arm, Light* intake, Light* clamp, Light* left, Light* right) 
    : arm(arm), intake(intake), clamp(clamp), left(left), right(right) {}

    void loop() override {
        while (true) {
            arm->update();
            pros::delay(10);
            intake->update();
            pros::delay(10);
            clamp->update();
            pros::delay(10);
            left->update();
            pros::delay(10);
            right->update();
            pros::delay(10);
        }
    }
};



class FlowingGradient : public Light {
protected:
    uint ticksPassed = 0;

    std::vector<int> blueGradient;
    std::vector<int> redGradient;

    void update() override;

public:
    FlowingGradient(uint port, uint length, std::vector<int> redGradient, std::vector<int> blueGradient)
    : Light(port, length), redGradient(redGradient), blueGradient(blueGradient) {}
};



class BreathingGradient : public Light {
protected:
    uint ticksPassed = 0;

    std::vector<int> blueGradient;
    std::vector<int> redGradient;

    void update() override;

public:
    BreathingGradient(uint port, uint length, std::vector<int> redGradient, std::vector<int> blueGradient)
    : Light(port, length), redGradient(redGradient), blueGradient(blueGradient) {}
};



class Pulser : public Light {
public:
    double delta = -0.1;
    double alpha = 0;

    HSV red;
    HSV blue;

    void update() override;

    Pulser(uint port, uint length, HSV red, HSV blue, double delta = -0.1)
        : Light(port, length), red(red), blue(blue), delta(delta) {}
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
    AnimationReader(uint port, uint length, std::vector<int> redAnimation, std::vector<int> blueAnimation)
        : Light(port, length), redAnimation(redAnimation), blueAnimation(blueAnimation)
        { animationLength = redAnimation.size() / length; }

    void setDirection(bool dir) { playDirection = dir; };
};
}