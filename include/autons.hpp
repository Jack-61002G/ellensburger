#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "robotconfig.h"



inline void redRingElims() {
  chassis.setPose(-58, 14, -90);

  chassis.swingToHeading(-132, lemlib::DriveSide::LEFT, 1000, {.maxSpeed = 80});
  lift.setTarget(230);
  pros::delay(700);
  
  chassis.moveToPoint(-24, 24, 2000, {.forwards = false, .maxSpeed = 60});
  lift.setTarget(75);
  chassis.waitUntilDone();
  clamp.extend();
  pros::delay(100);

  chassis.turnToPoint(-10, 38, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-10, 38, 1000, {.maxSpeed = 80});
  intake.setDirection(lib::Dir::In);

  chassis.moveToPoint(-16, 32, 1000, {.forwards = false, .maxSpeed = 90});
  chassis.moveToPoint(-24, 48, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(-10, 52, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-10, 52, 1000, {.maxSpeed = 90});

  chassis.moveToPoint(-20, 52, 1000, {.forwards = false, .maxSpeed = 90});
  chassis.turnToPoint(-70, 70, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-70, 70, 2000, {.maxSpeed = 90});

  pros::delay(500);
  chassis.moveToPoint(-50, 50, 1000, {.forwards = false});
  chassis.moveToPoint(-70, 70, 1000, {.maxSpeed = 90});

  chassis.moveToPoint(-48, 48, 1000, {.forwards = false});
  chassis.turnToPoint(-48, 0, 1000);
  chassis.moveToPoint(-48, -24, 2000, {.maxSpeed = 60});
  chassis.waitUntilDone();
  intake.setDirection(lib::Dir::Idle);
}



inline void redRingSide() {
  chassis.setPose(-56, 14, -90);
  chassis.moveToPoint(-56, 14, 100);

  // score on alliance stake
  chassis.turnToHeading(-140, 1000);

  lift.setTarget(215);
  chassis.waitUntilDone();
  
  // clamp goal
  chassis.moveToPoint(-48, 24, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 6});
  chassis.moveToPoint(-26, 19.5, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  // intake quad stack
  pros::delay(50);
  chassis.moveToPoint(-13.5, 32, 1200, {.maxSpeed = 80});
  intake.setDirection(lib::Dir::In);

  chassis.turnToPoint(-12.5, 48, 1000, {.maxSpeed = 100});
  chassis.moveToPoint(-12.5, 48, 1500, {.maxSpeed = 100});

  chassis.waitUntilDone();

  // back out
  chassis.moveToPoint(-24, 48, 1000, {.maxSpeed = 80, .minSpeed = 30, .earlyExitRange = 6});
  
  chassis.turnToPoint(-71, 65.5, 1000);
  chassis.moveToPoint(-71, 65.5, 2500, {.maxSpeed = 68});

  intake.setState(lib::Dir::In, lib::Jam::None, true);

  chassis.waitUntilDone();
  pros::delay(200);

  chassis.moveToPoint(-49, 52, 1000, {.forwards = false});
  chassis.moveToPoint(-70, 70, 1000);

  chassis.moveToPoint(-48, 48, 2000, {.forwards = false, .maxSpeed = 90});
  chassis.turnToPoint(-53, 21, 1000);
  chassis.moveToPoint(-53, 21, 1500, {.maxSpeed = 90});
  chassis.waitUntil(28.5);

  leftDoinker.extend();
  pros::delay(800);

  chassis.turnToPoint(-26, 6, 1000);
  chassis.waitUntilDone();
  leftDoinker.retract();
  chassis.moveToPoint(-30, 6, 1000, {.maxSpeed = 55});

  // get alliance stake stack
  //chassis.turnToPoint(-50, 12, 500);
  //chassis.moveToPoint(-50, 12, 1500, {.minSpeed = 40, .earlyExitRange = 4});
  //chassis.moveToPoint(-46, -6, 1500, {.maxSpeed = 50});

  //intake.setJamMode(lib::Jam::Reverse);

  //chassis.turnToPoint(-24, 0, 750, {.minSpeed = 50, .earlyExitRange = 5});
  //lift.setTarget(200);
  //chassis.moveToPoint(-24, 0, 1000, {.maxSpeed = 50});
}



inline void redMogo() {
  chassis.setPose(-60, -40, 90);

  chassis.moveToPoint(-10, -40, 1500);
  chassis.waitUntil(48);
  rightDoinker.extend();

  chassis.turnToPoint(-24, -24, 1000, {.forwards = false});
  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.extend();

  pros::delay(200);
  chassis.turnToPoint(-10, -10, 1000);
  rightDoinker.retract();

  chassis.moveToPoint(-10, -10, 1000);
  chassis.waitUntilDone();

  rightDoinker.extend();
  pros::delay(200);

  chassis.turnToPoint(0, -20, 1000);
  leftDoinker.extend();
  pros::delay(200);

  chassis.moveToPoint(-36, -36, 1000, {.forwards = false});
  chassis.turnToPoint(0, -36, 1000);
  chassis.waitUntilDone();

  leftDoinker.retract();
  rightDoinker.retract();
  pros::delay(250);

  chassis.turnToPoint(-24, -48, 1000);
  chassis.moveToPoint(-24, -48, 1000);
  intake.setDirection(lib::Dir::In);

  chassis.turnToPoint(-24, -20, 1000);
  chassis.moveToPoint(-24, -20, 1000);

  chassis.turnToPoint(-70, -70, 1000);
  chassis.moveToPoint(-70, -70, 1000);

  chassis.moveToPoint(-50, -50, 1000, {.forwards = false});
  chassis.moveToPoint(-70, -70, 1000);
  chassis.moveToPoint(-50, -50, 1000, {.forwards = false});

}



inline void redSoloAwp() {
  chassis.setPose(-48, -10, -70);

  chassis.moveToPoint(-52, -6, 1000);
  lift.setTarget(200);
  pros::delay(500);

  chassis.moveToPoint(-24, -36, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.extend();
  pros::delay(200);

  chassis.moveToPoint(-36, -10, 1000);
  chassis.waitUntilDone();
  rightDoinker.extend();

  chassis.moveToPoint(-24, -20, 1000, {.forwards = false});
  chassis.waitUntilDone();
  rightDoinker.retract();

  chassis.moveToPoint(-30, -16, 1000);
  intake.setDirection(lib::Dir::In);

  chassis.moveToPoint(-24, -24, 1000, {.forwards = false});
  chassis.turnToPoint(-10, -10, 1000);
  chassis.moveToPoint(-10, -10, 1000);
  chassis.waitUntilDone();

  rightDoinker.extend();
  pros::delay(200);

  chassis.moveToPoint(-24, -20, 1000, {.forwards = false});
  chassis.waitUntilDone();
  rightDoinker.retract();
  pros::delay(200);

  chassis.moveToPoint(-10, -10, 1000);
  chassis.moveToPoint(-24, -20, 1000);

  chassis.turnToPoint(-24, -48, 1000);
  chassis.moveToPoint(-24, -48, 1000);

  while (!color.seesRed()) { pros::delay(10); }

  intake.setDirection(lib::Dir::Idle);
  clamp.retract();
  chassis.turnToPoint(-10, -48, 1000, {.forwards = false});
  chassis.moveToPoint(-10, -48, 1000, {.forwards = false});

  chassis.waitUntilDone();
  clamp.extend();
}