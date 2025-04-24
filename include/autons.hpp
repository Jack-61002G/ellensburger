#include "lib/intake.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "robotconfig.h"



inline void redRingSide() {
  chassis.setPose(-56, 14, -90);
  chassis.moveToPoint(-56, 14, 100);

  // score on alliance stake
  chassis.turnToHeading(-140, 1000);

  lift.setTarget(215);
  pros::delay(450);
  
  // clamp goal
  chassis.moveToPoint(-48, 24, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 6});
  chassis.moveToPoint(-26, 19.5, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  // intake quad stack
  chassis.moveToPoint(-13.7, 32, 1200, {.maxSpeed = 90});
  intake.setDirection(lib::Dir::In);

  chassis.turnToPoint(-12.5, 49, 1000, {.maxSpeed = 100});
  chassis.moveToPoint(-12.5, 49, 1500, {.minSpeed = 10, .earlyExitRange = 1});

  chassis.waitUntilDone();

  // back out
  chassis.moveToPoint(-24, 40, 1000, {.maxSpeed = 90, .minSpeed = 30, .earlyExitRange = 6});
  
  // go for corner
  chassis.turnToPoint(-70, 65.5, 1000);
  chassis.moveToPoint(-70, 65.5, 1000, {.maxSpeed = 95});

  intake.setState(lib::Dir::In, lib::Jam::None, true);

  chassis.waitUntilDone();

  chassis.moveToPoint(-51, 51, 800, {.forwards = false});
  chassis.moveToPoint(-69.5, 71, 900);

  chassis.moveToPoint(-48, 48, 2000, {.forwards = false});
  chassis.turnToPoint(-51.6, 20.7, 1000);
  chassis.moveToPoint(-51.6, 20.7, 1550, {.maxSpeed = 80});
  chassis.waitUntil(28.5);
  
  intake.setState(lib::Dir::In, lib::Jam::Reverse, true);
  leftDoinker.extend();
  pros::delay(280);

  chassis.moveToPoint(-49, 32, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 3});
  chassis.turnToPoint(0, -17, 800);
  pros::delay(250);
  leftDoinker.retract();
  lift.setTarget(85);
  chassis.moveToPoint(-6, 6, 1000, {.maxSpeed = 65});
}



inline void blueRingSide() {
  chassis.setPose(56, 14, 90);
  chassis.moveToPoint(56, 14, 100);

  // score on alliance stake
  chassis.turnToHeading(140, 1000);

  lift.setTarget(215);
  pros::delay(450);
  
  // clamp goal
  chassis.moveToPoint(48, 24, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 6});
  chassis.moveToPoint(26, 19.5, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  // intake quad stack
  chassis.moveToPoint(13.7, 32, 1200, {.maxSpeed = 90});
  intake.setDirection(lib::Dir::In);

  chassis.turnToPoint(15, 49, 1000, {.maxSpeed = 100});
  chassis.moveToPoint(15, 49, 1500, {.minSpeed = 10, .earlyExitRange = 1});

  chassis.waitUntilDone();

  // back out
  chassis.moveToPoint(24, 40, 1000, {.maxSpeed = 90, .minSpeed = 30, .earlyExitRange = 6});
  
  // go for corner
  chassis.turnToPoint(70, 65.5, 1000);
  chassis.moveToPoint(70, 65.5, 1000, {.maxSpeed = 95});

  intake.setState(lib::Dir::In, lib::Jam::None, true);

  chassis.waitUntilDone();

  chassis.moveToPoint(51, 51, 800, {.forwards = false});
  chassis.moveToPoint(69.5, 71, 900);

  chassis.moveToPoint(48, 48, 2000, {.forwards = false});
  chassis.turnToPoint(52.5, 20.7, 1000);
  chassis.moveToPoint(52.5, 20.7, 1550, {.maxSpeed = 80});
  chassis.waitUntil(28.5);

  intake.setState(lib::Dir::In, lib::Jam::Reverse, true);
  rightDoinker.extend();
  pros::delay(280);

  chassis.moveToPoint(49, 32, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 3});
  chassis.turnToPoint(0, -17, 800);
  pros::delay(250);
  rightDoinker.retract();
  lift.setTarget(85);
  chassis.moveToPoint(6, 6, 1000, {.maxSpeed = 65});
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

  chassis.turnToPoint(-21.5, -16.5, 1000);
  chassis.moveToPoint(-21.5, -16.5, 1000, {.maxSpeed = 100});
  pros::delay(180);
  intake.setDirection(lib::Dir::Idle);
  chassis.waitUntilDone();

  rightDoinker.extend();
  pros::delay(200);

  chassis.swingToPoint(0, -5.7, lemlib::DriveSide::RIGHT, 750);
  chassis.waitUntilDone();
  leftDoinker.extend();
  pros::delay(200);

  chassis.moveToPoint(-39, -38, 1200, {.forwards = false, .maxSpeed = 100});
  pros::delay(800);
  leftDoinker.retract();
  rightDoinker.retract();
  intake.setDirection(lib::Dir::In);

  chassis.moveToPoint(-22, -28, 1000);
  chassis.moveToPoint(-30, -18, 1000, {.maxSpeed = 100});

  chassis.turnToPoint(-29, -48, 1000);
  intake.setDirection(lib::Dir::Idle);
  chassis.moveToPoint(-29, -48, 1000);
  pros::delay(100);
  intake.setDirection(lib::Dir::In);

  chassis.turnToPoint(-74, -72, 1000);
  chassis.moveToPoint(-74, -72, 1000, {.maxSpeed = 90});
  lift.setTarget(100);

  chassis.moveToPoint(-55, -55, 1000, {.forwards = false});
  chassis.moveToPoint(-66, -70, 1000);
  chassis.moveToPoint(-24, -24, 2000);
  lift.setTarget(70);
  pros::delay(900);
  intake.setDirection(lib::Dir::Idle);
}



inline void blueMogo() {
  chassis.setPose(55.5, -24, 90);
  chassis.setPose(55.5, -24, 90);

  chassis.turnToPoint(24, -24, 1000, {.forwards = false});
  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .maxSpeed = 70});
  chassis.waitUntil(21);
  intake.setDirection(lib::Dir::In);
  chassis.waitUntil(21.75);
  clamp.extend();
  chassis.waitUntilDone();

  chassis.turnToHeading(0, 450);
  chassis.moveToPoint(16.33, -16.25, 1000, {.maxSpeed = 100});
  pros::delay(180);
  intake.setDirection(lib::Dir::Idle);
  chassis.waitUntilDone();

  rightDoinker.extend();
  pros::delay(200);

  chassis.swingToPoint(0, 4, lemlib::DriveSide::LEFT, 750);
  chassis.waitUntilDone();
  leftDoinker.extend();
  pros::delay(200);

  chassis.moveToPoint(39, -38, 1200, {.forwards = false, .maxSpeed = 100});
  pros::delay(800);
  leftDoinker.retract();
  rightDoinker.retract();
  intake.setDirection(lib::Dir::In);

  chassis.moveToPoint(22, -28, 1000);
  chassis.moveToPoint(31, -18.5, 1000, {.maxSpeed = 100});

  chassis.turnToPoint(30, -48, 1000);
  intake.setDirection(lib::Dir::Idle);
  chassis.moveToPoint(30, -48, 1000);
  pros::delay(100);
  intake.setDirection(lib::Dir::In);

  chassis.turnToPoint(74.5, -73, 1000);
  chassis.moveToPoint(74.5, -73, 1000, {.maxSpeed = 90});
  lift.setTarget(100);

  chassis.moveToPoint(55, -55, 1000, {.forwards = false});
  chassis.moveToPoint(65, -70, 1000);
  chassis.moveToPoint(24, -24, 2000);
  lift.setTarget(70);
  pros::delay(900);
  intake.setDirection(lib::Dir::Idle);
}



inline void redMogoStake() {
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