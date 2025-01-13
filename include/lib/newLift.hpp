#include "lib/TaskWrapper.hpp"
#include "lib/pid.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"



namespace lib {

enum class NewLiftStates {Position, Voltage};

class NewLift : public ryan::TaskWrapper {



private:

    pros::MotorGroup motors = pros::MotorGroup({-2, 21});
    pros::Rotation rotation = pros::Rotation(6);

    NewLiftStates state;
    PID pid = PID(2.5, 0, 15);

    float target;



public:

    void loop() override {
        setTarget();

        while (true) {
            switch (state) {

            case NewLiftStates::Voltage:
                motors.move(target);
                break;
        
            case NewLiftStates::Position:
                motors.move(pid.compute(target - rotation.get_angle() / 100.0));
                break;
            }

            pros::delay(10);
        }
    };

    void setTarget() { target = rotation.get_angle() / 100.0; state = NewLiftStates::Position; }
    void setTarget(float newTarget) { target = newTarget; state = NewLiftStates::Position; }
    void setVoltage(float newVoltage) { target = newVoltage; state = NewLiftStates::Voltage; }
    float getAngle() { return rotation.get_angle() / 100.0; };
    NewLiftStates getState() {return state;}
};
}