#include "lib/TaskWrapper.hpp"
#include "pid.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include <cmath>

namespace lib {


enum class LiftStates { Position, Voltage, Hold };


class Lift : public ryan::TaskWrapper {

private:

  pros::MotorGroup motors = pros::MotorGroup({-2, 21});
  pros::Rotation rotation = pros::Rotation(6);

  LiftStates state = LiftStates::Hold;
  PID pid = PID(3, 0, 15);

  float target;


public:

  void loop() override {
    motors.set_brake_mode_all(pros::MotorBrake::hold);

    while (true) {
      float position = rotation.get_angle() / 100.0;
      if (position > 330) { position -= 360; }

      switch (state) {
      case LiftStates::Voltage:
        motors.move(target);
        break;

      case LiftStates::Position:
        motors.move(pid.compute(target - position));
        break;

      case LiftStates::Hold:
        motors.brake();
        break;
      }

      pros::delay(10);
    }
  };

  void hold() { state = LiftStates::Hold; }

  void setTarget(float newTarget) { target = newTarget; state = LiftStates::Position; }

  void setVoltage(float newVoltage) { target = newVoltage; state = LiftStates::Voltage; }

  float getAngle() { return rotation.get_angle() / 100.0; };
};
} // namespace lib