#include "main.h"
#include "autons.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lib/intake.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "robodash/api.h"
#include "robodash/views/console.hpp"
#include "robotconfig.h"
#include "lib/reset.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>



rd::Selector selector({
  {"Red Ring", redRingSide},
  {"Red Mogo", redMogo},
  {"Red Solo AWP", redSoloAwp}
}); 

rd::Console console;



void measure_offsets() {
    // Number of times to test
    const int iterations = 10;
    // Final offsets
    double vert_offset = 0.0, horz_offset = 0.0;
    double prevdisttravelvert = 0;
    double prevdisttravelhoriz = 0;
    leftMotors.set_brake_mode(pros::MotorBrake::hold);
    rightMotors.set_brake_mode(pros::MotorBrake::hold);
    
    for (int i = 0; i < iterations; i++) {
        // Reset robot position and sensors
        chassis.setPose(0, 0, 0);
        chassis.resetLocalPosition();
        
        // Get initial angle
        double start_angle = chassis.getPose().theta;
        
        // Alternate between turning 90 and 270 degrees
        double target = i % 2 == 0 ? -1 : 1;
        
        chassis.arcade(0, (127/2.0) * target);
        pros::delay(1000);
        chassis.arcade(0, 0);
        leftMotors.brake();
        rightMotors.brake();
        pros::delay(250);
        
        // Calculate angle change in radians
        double angle_delta = fabs(chassis.getPose().theta - start_angle) * (M_PI / 180.0);
        
        // Get tracker changes
        double vert_delta = verticalwheel.getDistanceTraveled() - prevdisttravelvert;
        double horz_delta = horizontalwheel.getDistanceTraveled() - prevdisttravelhoriz;

        // Update previous distances
        prevdisttravelvert = verticalwheel.getDistanceTraveled();
        prevdisttravelhoriz = horizontalwheel.getDistanceTraveled();
        
        // Calculate radius of turn for each tracker
        vert_offset += vert_delta / angle_delta;
        horz_offset += horz_delta / angle_delta;
        pros::delay(10);
    }
    
    // Average the offsets
    vert_offset /= iterations;
    horz_offset /= iterations;

    // Print results
    console.println(std::to_string(vert_offset));
    console.println(std::to_string(horz_offset));

}

inline void tune(){
  chassis.turnToHeading(180, 3000);
  chassis.waitUntilDone();
  console.println(std::to_string(chassis.getPose().x) + "," + std::to_string(chassis.getPose().y) + "," + std::to_string(chassis.getPose().theta));
  
  chassis.turnToHeading(0, 3000);
  chassis.waitUntilDone();
  console.print(std::to_string(chassis.getPose().x) + "," + std::to_string(chassis.getPose().y) + "," + std::to_string(chassis.getPose().theta));
  
};

void auton_check_loop() {
  pros::Task task = pros::Task{[=] {
    while (true) {

      auto lower_name = selector.get_auton()->name;

      if (lower_name.find("blue") != std::string::npos) {
        teamColor = team::blue;
      } else {
        teamColor = team::red;
      }

      pros::delay(100);

      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) || controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) || pros::competition::is_autonomous()) {
        return;
      }
    }
  }};
}



void initialize() {
  current_auto = selector.get_auton();
  auton_check_loop();

  chassis.calibrate();
  pros::delay(500);

  lights.startTask();
}



void disabled() {
  lift.stopTask();
  intake.stopTask();
}



void autonomous() {

  lift.startTask();
  intake.startTask();

  intake.setState(lib::Dir::Idle, lib::Jam::Reverse, true);

  redSoloAwp();
  return;

  selector.run_auton();
}



void opcontrol() {

  console.focus();
  intake.startTask();
  lift.startTask();

  intake.setState(lib::Dir::Idle, lib::Jam::Reverse, true);

  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  chassis.setPose(0, 0, 0);

  while (true) {

    console.clear();
    std::string str = "pos:" + std::to_string(chassis.getPose().x) + "," +
                               std::to_string(chassis.getPose().y) + "," +
                               std::to_string(chassis.getPose().theta);
    console.print(str);

    // Alliance Stake Macro
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      chassis.tank(-65, -65);
      lift.setTarget(220);
      pros::delay(165);
      chassis.tank(0, 0);
      pros::delay(270);
      liftButtonHeld = false;
    }
    
    // Drive control
    chassis.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 
                  controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    double output = driveLedFilter.Run(fmax(fabs(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127.0, fabs(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) / 127.0));
    leftDriveLed.alpha = output; rightDriveLed.alpha = output;

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      lift.setTarget(170);
    } else {
    // Intake control
    intake.setDirection(
      controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) ? lib::Dir::In
      : (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) ? lib::Dir::Out
      : lib::Dir::Idle
    );}
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) || controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      intakeLed.alpha = 1;
      armBraceLeds.alpha = 1;
    }


    // Doinker and clamp
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      leftDoinker.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      rightDoinker.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      clamp.toggle();
      clampLed.alpha = 1;
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      if (teamColor == team::blue) {
        teamColor = team::red;
      } else {
        teamColor = team::blue;
      }
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      intake.sortEnabled = !intake.sortEnabled;
    }

    // Lift control
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) { // reset to loading position
      lift.setTarget(34);
      intake.setJamMode(lib::Jam::Tap);
      armBraceLeds.alpha = 1;
    }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { // manually drive down
      liftButtonHeld = true;
      lift.setVoltage(-127);
      intake.setJamMode(lib::Jam::Reverse);
      armBraceLeds.alpha = 1;
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // manually drive up
      liftButtonHeld = true;
      lift.setVoltage(127);
      intake.setJamMode(lib::Jam::Reverse);
      armBraceLeds.alpha = 1;
    }
    else if (liftButtonHeld) { // set hold target when button is released
      liftButtonHeld = false;
      lift.hold();
    }

    pros::delay(15);
  }
}
