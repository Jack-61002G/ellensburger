#include "lib/TaskWrapper.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"



namespace lib {

enum class NewLiftStates {Position, Voltage};

class NewLift : public ryan::TaskWrapper {



private:

    pros::MotorGroup motors = pros::MotorGroup({-2, 21});
    pros::Rotation rotation = pros::Rotation(6);

    NewLiftStates state;

    float target;

    float p = 2.5;
    float d = 15;
    float prev_error = 0;



public:

    void loop() override {
        setTarget();

        while (true) {
            switch (state) {

            case NewLiftStates::Voltage:
                motors.move(target);
                break;
        
            case NewLiftStates::Position:
                float error = target - rotation.get_angle() / 100.0;
                motors.move(error * p + (error - prev_error) * d);
                prev_error = error;
                break;
            }
        }
    };

    void setTarget() { target = rotation.get_angle() / 100.0; state = NewLiftStates::Position; }
    void setTarget(float newTarget) { target = newTarget; state = NewLiftStates::Position; }
    void setVoltage(float newVoltage) { target = newVoltage; state = NewLiftStates::Voltage; }
    float getAngle() { return rotation.get_angle() / 100.0; };
    NewLiftStates getState() {return state;}
};
}