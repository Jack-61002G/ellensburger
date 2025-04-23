#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "robotconfig.h"



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

}



inline void redMogo() {
  chassis.setPose(-55.5, -24, -90);
  chassis.setPose(-55.5, -24, -90);

  chassis.turnToPoint(-24, -24, 1000, {.forwards = false});
  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .maxSpeed = 70});
  chassis.waitUntil(21);
  intake.setDirection(lib::Dir::In);
  chassis.waitUntil(21.75);
  clamp.extend();
  chassis.waitUntilDone();

  chassis.turnToPoint(-21.3, -16.5, 1000);
  chassis.moveToPoint(-21.3, -16.5, 1000, {.maxSpeed = 90});
  pros::delay(200);
  intake.setDirection(lib::Dir::Idle);
  chassis.waitUntilDone();

  rightDoinker.extend();
  pros::delay(200);

  chassis.swingToPoint(0, -5.5, lemlib::DriveSide::RIGHT, 750);
  chassis.waitUntilDone();
  leftDoinker.extend();
  pros::delay(200);

  chassis.moveToPoint(-36, -36, 1000, {.forwards = false, .maxSpeed = 90});
  chassis.waitUntilDone();
  intake.setDirection(lib::Dir::In);

  leftDoinker.retract();
  rightDoinker.retract();
  pros::delay(200);

  chassis.moveToPoint(-22, -28, 1000);
  chassis.moveToPoint(-33, -17, 1000);

  chassis.turnToPoint(-27, -49, 1000, {.maxSpeed = 85});
  chassis.moveToPoint(-27, -49, 1000);

  chassis.turnToPoint(-72, -72, 1000);
  chassis.moveToPoint(-72, -72, 1000, {.maxSpeed = 90});
  lift.setTarget(100);

  chassis.moveToPoint(-50, -50, 1000, {.forwards = false});
  chassis.moveToPoint(-65, -70, 1000);
  chassis.moveToPoint(0, 0, 2000, {.forwards = false});
  lift.setTarget(34);
}



inline void redSoloAwp() {
  chassis.setPose(-56, -14, -90);

  chassis.turnToHeading(-40, 1000);
  lift.setTarget(210);
  while (armrot.get_angle() < 19500) { pros::delay(10); }

  // clamp mogo
  chassis.cancelMotion();
  chassis.moveToPoint(-23.8, -25, 2000, {.forwards = false, .maxSpeed = 65});
  pros::delay(400);
  lift.setTarget(0);
  chassis.waitUntilDone();
  clamp.extend();

  // doinker alliance stake ring
  pros::delay(200);
  chassis.moveToPoint(-36, -18.667, 1000);
  chassis.waitUntilDone();
  rightDoinker.extend();

  // pull ring back
  pros::delay(350);
  chassis.moveToPoint(-24, -30, 1000, {.forwards = false, .maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 9});
  chassis.moveToPoint(-35, -42, 1500, {.forwards = false});

  chassis.waitUntilDone();
  rightDoinker.retract();
  pros::delay(100);

  // eat ring and move to center stacks
  chassis.moveToPoint(-20.333, -18, 1500, {.maxSpeed = 90});
  intake.setDirection(lib::Dir::In);
  pros::delay(600);
  intake.setDirection(lib::Dir::Idle);
  chassis.waitUntilDone();

  rightDoinker.extend(); // doink
  pros::delay(333);

  // back out
  chassis.moveToPoint(-50, -34, 1000, {.forwards = false, .maxSpeed = 90});
  chassis.waitUntilDone();
  rightDoinker.retract();
  pros::delay(200);

  // eat ring
  chassis.moveToPoint(-27.5, -32, 1000, {.maxSpeed = 80});
  intake.setDirection(lib::Dir::In);

  // move to stack
  chassis.turnToPoint(-27.5, -53, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(-27.5, -53, 2000, {.maxSpeed = 85});
  
  // set down full goal
  chassis.turnToPoint(-48, -53, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.moveToPoint(-48, -53, 1200, {.forwards = false, .maxSpeed = 90});
  chassis.waitUntilDone();
  pros::delay(100);
  intake.setDirection(lib::Dir::Idle);
  clamp.retract();
  pros::delay(100);

  chassis.turnToPoint(-26, -51, 1000, {.forwards = false});
  chassis.moveToPoint(-26, -51, 1000, {.forwards = false, .maxSpeed = 80});
}