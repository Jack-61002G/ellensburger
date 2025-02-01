#pragma once
#include "pros/adi.hpp"
#include "lib/TaskWrapper.hpp"
#include <cstdint>


namespace lib {


class Lights : public ryan::TaskWrapper {

private:

    pros::adi::Led leftDriveLed = pros::adi::Led('H', 40);
    pros::adi::Led rightDriveLed = pros::adi::Led('E', 40);
    pros::adi::Led alignerLed = pros::adi::Led('F', 40);
    //pros::adi::Led indicatorLed1 = pros::adi::Led('G', 6);


public:
    int startTime = -1;
    float brightness = 0.7;

    void loop() override;

};


}