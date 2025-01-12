#include "main.h"
#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lib/intake.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "robodash/api.h"
#include "robotconfig.h"
#include <cctype>
#include <cmath>
#include <string>

rd::Selector selector({{"red ring", redRingSide},
                       {"blue ring", blueRingSide},
                       {"red mogo", redMogoRush},
                       {"blue mogo", blueMogoRush},
                       {"skills", oldskills}});

void auton_check_loop() {
  pros::Task task = pros::Task {
    [=] {
      while (true) {

        auto lower_name = selector.get_auton()->name;
        
        if (lower_name.find("blue") != std::string::npos) {
          teamColor = team::blue;
        } else {
          teamColor = team::red;
        }

        pros::delay(100);
      }
    }
  };}

  void initialize() {
    current_auto = selector.get_auton();

    auton_check_loop();

        chassis.calibrate();
    pros::delay(500);

    lights.startTask();
    color.set_integration_time(5);
  }

  void disabled() {
    intake.sort_override = false;
    lift.stopTask();
    intake.stopTask();
  }

  void competition_initialize() {}

  void autonomous() {

    wheelsUpPiston.retract();

    lift.startTask();
    intake.startTask();

    if (chassis.getPose().x == NAN || chassis.getPose().y == NAN ||
        chassis.getPose().theta == NAN) {
      chassis.calibrate();
    }

    selector.run_auton();
  }

  void opcontrol() {
    intake.startTask();
    lift.startTask();

    wheelsUpPiston.extend();

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

      if (intake.getState() != newState &&
          intake.getState() != lib::IntakeState::Jam) {
        intake.setState(newState);
      }
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        doinker.toggle();
      }
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        clamp.toggle();
      }
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        lift.setTarget(25);
        intake.jam_override = true;
      }
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        liftButtonHeld = true;
        lift.setVoltage(-127);
        intake.jam_override = false;
      } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        liftButtonHeld = true;
        lift.setVoltage(127);
        intake.jam_override = false;
      } else if (liftButtonHeld) {
        liftButtonHeld = false;
        lift.setTarget();
      }

      pros::delay(15);
    }
  }
