#include "main.h"
#include "autons.hpp"
#include "autoselect/selection.h"
#include "lemlib/chassis/chassis.hpp"
#include "lib/intake.hpp"
#include "lib/lift.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "robotconfig.h"
#include <string>

void measure_offsets() {
    // Number of times to test
    const int iterations = 10;
    // Final offsets
    double vert_offset = 0.0, horz_offset = 0.0;
    
    for (int i = 0; i < iterations; i++) {
        // Reset robot position and sensors
        chassis.setPose(0, 0, 0);
        chassis.resetLocalPosition();
        
        // Get initial angle
        double start_angle = chassis.getPose().theta;
        
        // Alternate between turning 90 and 270 degrees
        double target = i % 2 == 0 ? 90 : 270;
        
        // Turn to target angle at half speed
        chassis.turnToHeading(target, 2000, {.maxSpeed = 100}); // Using maximum speed of 100
        pros::delay(250); // Wait for robot to settle
        
        // Calculate angle change in radians
        double angle_delta = fabs(chassis.getPose().theta - start_angle) * (M_PI / 180.0);
        
        // Get tracker changes
        double vert_delta = verticalwheel.getDistanceTraveled();
        double horz_delta = horizontalwheel.getDistanceTraveled();
        
        // Calculate radius of turn for each tracker
        vert_offset += vert_delta / angle_delta;
        horz_offset += horz_delta / angle_delta;
    }
    
    // Average the offsets
    vert_offset /= iterations;
    horz_offset /= iterations;

    // Print results
    pros::lcd::set_text(1, std::to_string(vert_offset));
    pros::lcd::set_text(2, std::to_string(horz_offset));

}


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
  //pros::lcd::initialize();
  auton_check_loop();

  chassis.calibrate();
  pros::delay(500);

  lift.startTask();
  intake.startTask();
  lights.startTask();
  color.set_integration_time(5);

}



void disabled() {
  intake.sort_override = false;
}



void competition_initialize() {}



void autonomous() {
  teamColor = team::blue;
  blueRingSide();
  if (selector::auton == 1) {
    redRingSide();
  }
  if (selector::auton == -1) {
    blueRingSide();
  }
  if (selector::auton == 2) {
    redMogoRush();
  }
  if (selector::auton == -2) {
    blueMogoRush();
  }
  if (selector::auton == 0) {
    skills();
  }

}



void opcontrol() {
  lift.setStart(20);

  lights.startTimer();
  float liftTarget = -1;

  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  while (true) {

    if (selector::auton == 0) {
      intake.sort_override = true;
    } else {
      intake.sort_override = false;
    }

    chassis.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                   controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    lib::IntakeState newState =
        (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
            ? lib::IntakeState::In
        : (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
            ? lib::IntakeState::Out
            : lib::IntakeState::Idle;

    if (intake.getState() != newState && intake.getState() != lib::IntakeState::Jam) {
      intake.setState(newState);
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
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && lift.getState() != lib::LiftState::Reset) {
      liftButtonHeld = true;
      lift.setState(lib::LiftState::Manual);
      lift.setVoltage(-127);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && lift.getState() != lib::LiftState::Reset) {
      liftButtonHeld = true;
      lift.setState(lib::LiftState::Manual);
      lift.setVoltage(127);
    } else if (liftButtonHeld) {
      liftButtonHeld = false;
      //lift.setTarget(lift.getAngle());
      lift.setVoltage(0);
    }
  
    pros::delay(15);
  }
}
