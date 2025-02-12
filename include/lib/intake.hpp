#pragma once
#include "lib/TaskWrapper.hpp"
#include "lib/StateMachine.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include <cstdint>

namespace lib {

enum class IntakeState {In, Out, Jam, Idle};

class Intake : public StateMachine<IntakeState, IntakeState::Idle>, public ryan::TaskWrapper {

private:
  std::shared_ptr<pros::MotorGroup> motors;
  std::shared_ptr<pros::Optical> color;
  int sort_time = 0;


public:

  bool sort_override = false;
  bool jam_override = false;
  bool sort_primed = false;
  bool arm_loading = false;

  Intake(pros::MotorGroup *motors, pros::Optical *color) : motors(motors), color(color) {
    color->set_led_pwm(100);
  }
  void loop() override;

  };
}