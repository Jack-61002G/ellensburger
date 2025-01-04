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
  std::shared_ptr<pros::adi::Pneumatics> sort;
  std::shared_ptr<pros::adi::Button> limit;
  int sort_time = 0;


public:

  bool sort_override = false;

  Intake(pros::MotorGroup *motors, pros::Optical *color, pros::adi::Pneumatics *sort, pros::adi::Button *limit) : motors(motors), color(color), sort(sort), limit(limit) {
    color->set_led_pwm(100);
  }
  void loop() override;

  };
}