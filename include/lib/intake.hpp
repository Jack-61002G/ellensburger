#pragma once
#include "lib/TaskWrapper.hpp"
#include "lib/StateMachine.hpp"
#include "color.hpp"
#include "pros/motor_group.hpp"

namespace lib {

enum class IntakeState {In, Out, Jam, Idle};

class Intake : public StateMachine<IntakeState, IntakeState::Idle>, public ryan::TaskWrapper {

private:
  std::shared_ptr<pros::MotorGroup> motors;
  std::shared_ptr<lib::Color> color;
  int sort_time = 0;


public:

  bool sort_override = false;
  bool jam_override = false;
  bool sort_primed = false;
  bool arm_loading = false;

  Intake(pros::MotorGroup *motors, lib::Color *color) : motors(motors), color(color) {}
  void loop() override;

  };
}