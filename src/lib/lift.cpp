#include "lib/lift.hpp"
#include "pros/abstract_motor.hpp"
#include "robotconfig.h"
#include <cstdint>
#include <iostream>

using namespace lib;

void Lift::loop() {

  uint32_t now = pros::millis();
  motors->tare_position();
  motors->set_brake_mode_all(pros::MotorBrake::hold);
  while (true) {
    switch (getState()) {

    case LiftState::Stored:

      armLoading = false;
      if (target != DOWN_ANGLE) {
        pid.variables_reset();
        target = DOWN_ANGLE;
      }

      break;

    case LiftState::Recieve:

      armLoading = true;
      if (target != MID_ANGLE) {
        pid.variables_reset();
        target = MID_ANGLE;
      }

      break;

    case LiftState::Manual:
      motors->move(vol);
      break;

    case LiftState::Score:

      if (target != UP_ANGLE) {
        pid.variables_reset();
        target = UP_ANGLE;
      }

      break;

    case lib::LiftState::Custom:
      break;
    }

    if (getState() != LiftState::Manual) {
      pid.target_set(target / gearRatio);
      double error = (target / gearRatio) - motors->get_position();
      motors->move(pid.compute_error(error, motors->get_position()));
      // std::cout<<error<<std::endl;
    }
    pros::Task::delay_until(&now, 15);
  }
}

void Lift::itterateState(bool delta) {
  if (getState() == LiftState::Stored) {
    setState(LiftState::Recieve);
  } else {
    setState(LiftState::Stored);
  }
}

float Lift::getAngle() { return target; }
void Lift::setTarget(float angle) { target = angle; setState(LiftState::Custom);}
void Lift::setVoltage(int voltage) { vol = voltage; }