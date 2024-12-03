#include "main.h"
#include "autons.hpp"
#include "autoselect/selection.h"
#include "lemlib/chassis/chassis.hpp"
#include "lib/intake.hpp"
#include "lib/lift.hpp"
#include "pros/misc.h"
#include "robotconfig.h"



void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}



void auton_check_first() {
  FILE* file = fopen("auto", "r");
  if (file != nullptr) {
    fread(&current_auto, sizeof(int), 1, file);
    fclose(file);
  }
  if (current_auto < 0) {
    teamColor = team::blue;
  } else {
    teamColor = team::red;
  }
}
void auton_check_loop() {
  pros::Task task = pros::Task{[=] {
    while (true) {
      if (current_auto != selector::auton) {
        current_auto = selector::auton;

        if (current_auto < 0) {
          teamColor = team::blue;
        } else {
          teamColor = team::red;
        }

        FILE* file = fopen("auto", "w");
        fwrite(&current_auto, sizeof(int), 1, file);
        fclose(file);
      }

      pros::delay(100);
    }
  }};
}



void initialize() {
  auton_check_first();
  selector::init(360, current_auto);
  auton_check_loop();

  chassis.calibrate();
  pros::delay(500);

  lift.startTask();
  intake.startTask();
  lights.startTask();
}



void disabled() {}



void competition_initialize() {}



void autonomous() {
  if (selector::auton == 1) {
    redMogoRush();
  }
  if (selector::auton == -1) {
    blueMogoRush();
  }
}



void opcontrol() {

  lights.startTimer();
  float liftTarget = -1;

  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  while (true) {

    chassis.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                   controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    lib::IntakeState newState =
        (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
            ? lib::IntakeState::In
        : (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
            ? lib::IntakeState::Out
            : lib::IntakeState::Idle;

    if (intake.getState() != newState) {
      intake.setState(newState);
    }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      intake.sort_override = true;
    } else {
      intake.sort_override = false;
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      doinker.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      clamp.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      lift.setState(lib::LiftState::Recieve);
    }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      lift.setState(lib::LiftState::Manual);
      lift.setVoltage(-127);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      lift.setState(lib::LiftState::Manual);
      lift.setVoltage(127);
    } else {
      lift.setVoltage(0);
    }

    pros::delay(15);
  }
}
