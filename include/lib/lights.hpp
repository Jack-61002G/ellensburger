#pragma once
#include "pros/adi.hpp"
#include "lib/TaskWrapper.hpp"
#include <cstdint>


namespace lib {


class Lights : public ryan::TaskWrapper {

private:

    pros::adi::Led leftDriveLed = pros::adi::Led('E', 40);
    pros::adi::Led rightDriveLed = pros::adi::Led('G', 40);
    pros::adi::Led indicatorLed1 = pros::adi::Led('A', 6);


public:
    int startTime = -1;

    void startTimer() { startTime = pros::millis(); }
    void stopTimer() { startTime = -1; }
    void loop() override;

};


}