#include "lib/intake.hpp"
#include "pros/rtos.hpp"
#include "robotconfig.h"



using namespace lib;



void Intake::loop() {

  int jamTimer = 0;
  uint32_t now;
  uint32_t jamStartTime = 0;

  while (true) {
    // Intake jam logic
    if (std::abs(motors->get_actual_velocity_all()[0]) < 5 && getState() != IntakeState::Idle and !jam_override) {
      if (jamStartTime == 0) {
        // First time detecting slow velocity
        jamStartTime = pros::millis();
      }

      // Calculate how long we've been in slow velocity state
      uint32_t jamTimer = pros::millis() - jamStartTime;

      if (arm_loading && jamTimer > 25) {
        motors->move(0);
        pros::delay(200);
        motors->move(127);
        pros::delay(200);
        jam_override = true;
        setState(IntakeState::Idle);

      } else if (!arm_loading && jamTimer > 75) {
        setState(IntakeState::Jam);
      }

    } else {
      // Reset the start time when velocity is normal
      jamStartTime = 0;
      jamTimer = 0;
    }

  if (!sort_override) {
    if (teamColor == team::blue ) {
      if (color->seesRed()) {
        sort_primed = true;
      }
      else if (sort_primed == true) {setState(IntakeState::Jam); sort_primed = false;}
    } else {
      if (color->seesBlue()) {
        sort_primed = true;
      }
      else if (sort_primed == true) {setState(IntakeState::Jam); sort_primed = false;}
    }}



    switch (getState()) {

    case IntakeState::Idle:

      motors->move(0);

      break;

    case IntakeState::In:

      motors->move(127);

      break;

    case IntakeState::Out:

      motors->move(-127);
      break;

    case IntakeState::Jam:

      motors->move(-127);
      pros::delay(250);
      setState(IntakeState::In);
      break;
    }
    pros::delay(10);
  }
}