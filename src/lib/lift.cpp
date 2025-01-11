#include "lib/lift.hpp"
#include "pros/abstract_motor.hpp"
#include "robotconfig.h"
#include "autoSelect/selection.h"
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
        //pid.variables_reset();
        target = DOWN_ANGLE;
      }

      break;

    case LiftState::Recieve:

      armLoading = true;
      if (target != MID_ANGLE) {
        //pid.variables_reset();
        target = MID_ANGLE;
      }

      break;

    case LiftState::Manual:
      motors->move(vol);
      break;

    case LiftState::Score:

      if (target != UP_ANGLE) {
        //pid.variables_reset();
        target = UP_ANGLE;
      }

      break;

    case lib::LiftState::Custom:
      break;
    }


    if (getState() != LiftState::Manual && getState() != LiftState::Reset) {
      //pid.target_set(target / gearRatio);
      double meow = ((rot->get_angle() /100.0) > 300) ? (rot->get_angle() /100.0) - 360 : (rot->get_angle() /100.0); // meow
      double error = (target / gearRatio) - (meow);
      //motors->move(pid.compute_error(error, rot->get_angle() /100.0));
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

float Lift::getAngle() { return rot->get_angle(); }
void Lift::setStart(float start) { return; }
void Lift::setTarget(float angle) { target = angle; setState(LiftState::Custom);}
void Lift::setVoltage(int voltage) { vol = voltage; }