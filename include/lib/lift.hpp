#include "lib/TaskWrapper.hpp"
#include "pid.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"


namespace lib {

enum class LiftStates {Position, Voltage};

class Lift : public ryan::TaskWrapper {


private:

    pros::MotorGroup motors = pros::MotorGroup({-2, 21});
    pros::Rotation rotation = pros::Rotation(6);

    LiftStates state;
    PID pid = PID(2.5, 0.001, 15);

    float target;


public:

    void loop() override {
        setTarget();

        while (true) {
            switch (state) {

            case LiftStates::Voltage:
                motors.move(target);
                break;
        
            case LiftStates::Position:
                motors.move(pid.compute(target - rotation.get_angle() / 100.0));
                break;
            }

            pros::delay(10);
        }
    };

    void setTarget() { target = rotation.get_angle() / 100.0; state = LiftStates::Position; }
    void setTarget(float newTarget) { target = newTarget; state = LiftStates::Position; }
    void setVoltage(float newVoltage) { target = newVoltage; state = LiftStates::Voltage; }
    float getAngle() { return rotation.get_angle() / 100.0; };
};}