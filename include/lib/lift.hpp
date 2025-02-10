#include "lib/TaskWrapper.hpp"
#include "pid.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"

namespace lib {



enum class LiftStates { Position, Voltage };



class Lift : public ryan::TaskWrapper {

private:
  pros::MotorGroup motors = pros::MotorGroup({-2, 21});
  pros::Rotation rotation = pros::Rotation(6);

  LiftStates state;
  PID pid = PID(2.5, 0, 15);

  float target;

public:
  void loop() override {
    motors.set_brake_mode_all(pros::MotorBrake::hold);
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

  void setTarget() {
    target = rotation.get_angle() / 100.0;
    state = LiftStates::Position;
  }

  void setTarget(float newTarget) {
    target = newTarget;
    state = LiftStates::Position;
  }
  void setVoltage(float newVoltage) {
    target = newVoltage;
    state = LiftStates::Voltage;
  }
  float getAngle() { return rotation.get_angle() / 100.0; };
};
} // namespace lib