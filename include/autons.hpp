#include "lib/intake.hpp"
#include "lib/lift.hpp"
#include "robotconfig.h"

ASSET(mogo1_txt)
ASSET(wall1_txt)
ASSET(mogo3_txt)
ASSET(mogo2_txt)
ASSET(mogo3rings_txt)
ASSET(mogo3ring_txt)



inline void redRingSide() {

  chassis.setPose(-52, 36, 90);

  lift.setTarget(90);
  chassis.moveToPoint(-8, 39, 1500, {.earlyExitRange = 0});

  pros::delay(200);
  intake.setState(lib::IntakeState::In);

  chassis.moveToPose(-24, 20, 45, 1000, {.forwards = false});
  pros::delay(500);
  intake.setState(lib::IntakeState::Idle);
  chassis.waitUntilDone();
  clamp.toggle();
  pros::delay(150);
  chassis.moveToPoint(-25, 55, 1000);
  intake.setState(lib::IntakeState::In);
  chassis.waitUntilDone();
  pros::delay(500);

  chassis.moveToPose(-4, 48, 90, 2000);
  chassis.moveToPose(-55, 8, 35, 2000, {.forwards = false});
  chassis.turnToPoint(-64, 0, 1000);
  chassis.waitUntilDone();
  lift.setTarget(180);
  pros::delay(1500);
  chassis.moveToPoint(-36, 8, 1000, {.forwards = false});
  chassis.waitUntilDone();
  lift.setTarget(140);
  chassis.moveToPose(-20, 0, 90, 1000, {.lead = .1});
}



inline void blueRingSide() {

  chassis.setPose(52, 36, -90);

  lift.setTarget(90);
  chassis.moveToPoint(8, 39, 1500, {.earlyExitRange = 0});

  pros::delay(200);
  intake.setState(lib::IntakeState::In);

  chassis.moveToPose(24, 20, -45, 1000, {.forwards = false});
  pros::delay(350);
  intake.setState(lib::IntakeState::Idle);
  chassis.waitUntilDone();
  clamp.toggle();
  pros::delay(150);
  chassis.moveToPoint(25, 55, 1000);
  intake.setState(lib::IntakeState::In);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.moveToPose(4, 48, -90, 2000);
  chassis.moveToPose(55, 8, -35, 2000, {.forwards = false});
  chassis.turnToPoint(64, 0, 1000);
  chassis.waitUntilDone();
  lift.setTarget(180);
  pros::delay(1500);
  chassis.moveToPoint(36, 8, 1000, {.forwards = false});
  chassis.waitUntilDone();
  lift.setTarget(140);
  chassis.moveToPose(20, 0, -90, 1000, {.lead = .1});
}



inline void redMogoRush() {
  chassis.setPose(-57.25, -48, 90);
  chassis.moveToPoint(-57, -48, 100);
  intake.setState(lib::IntakeState::In);

  chassis.moveToPoint(-12, -52.5, 2000);
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    pros::delay(1150);
    intake.setState(lib::IntakeState::Idle);
  }};

  doinker.extend();
  chassis.waitUntil(40.25);
  rushClamp.extend();
  pros::delay(100);
  intake.sort_override = false;

  chassis.moveToPoint(-30, -56, 1000, {.forwards = false});
  chassis.waitUntilDone();
  rushClamp.retract();
  pros::delay(400);

  chassis.turnToPoint(-13, -38, 1000, {.forwards = false});
  chassis.waitUntilDone();

  doinker.retract();

  chassis.moveToPoint(-13, -38, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.extend();

  intake.setState(lib::IntakeState::In);
  pros::delay(1500);
  chassis.turnToPoint(-60, -30, 1000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::Idle);
  clamp.retract();

  chassis.moveToPoint(-22, -24, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.extend();
  pros::delay(100);

  chassis.moveToPoint(-52, -41, 1000);
  lift.setTarget(140);
  intake.setState(lib::IntakeState::In);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.waitUntilDone();

  chassis.moveToPoint(-13, -13, 1400);
  chassis.waitUntilDone();
  pros::delay(500);
  intake.setState(lib::IntakeState::Idle);
}



inline void blueMogoRush() {
  chassis.setPose(57.25, -48, -90);
  chassis.moveToPoint(57, -48, 100);
  intake.setState(lib::IntakeState::In);

  chassis.moveToPoint(11, -43.5, 2000);
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    pros::delay(1175);
    intake.setState(lib::IntakeState::Idle);
  }};

  doinker.extend();
  chassis.waitUntil(41);
  rushClamp.extend();
  pros::delay(100);
  intake.sort_override = false;

  chassis.moveToPoint(30, -56, 1000, {.forwards = false});
  chassis.waitUntilDone();
  rushClamp.retract();
  pros::delay(400);

  chassis.turnToPoint(13, -38, 1000, {.forwards = false});
  chassis.waitUntilDone();

  doinker.retract();

  chassis.moveToPoint(12, -44, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.extend();

  intake.setState(lib::IntakeState::In);
  pros::delay(1500);
  chassis.turnToPoint(60, -30, 1000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::Idle);
  clamp.retract();

  chassis.moveToPoint(22, -24, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.extend();
  pros::delay(100);

  chassis.moveToPoint(52, -41, 1000);
  lift.setTarget(140);
  intake.setState(lib::IntakeState::In);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.waitUntilDone();

  chassis.moveToPoint(12.5, -12.5, 1400);
  chassis.waitUntilDone();
  pros::delay(500);
  intake.setState(lib::IntakeState::Idle);
}



inline void skills() {

  chassis.setPose(-56, 0, 90);
  intake.setState(lib::IntakeState::In);
  pros::delay(250);

  chassis.turnToPoint(-42, 24, 1000, {.forwards = false});
  intake.setState(lib::IntakeState::Idle);
  chassis.moveToPoint(-41, 25, 3000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(20);
  clamp.toggle();
  pros::delay(250);

  chassis.follow(mogo1_txt, 10, 8000);
  intake.setState(lib::IntakeState::In);

  chassis.turnToPoint(-70, 70, 1000, {.forwards = false});
  chassis.moveToPoint(-70, 70, 1000, {.forwards = false});
  chassis.waitUntilDone();
  clamp.toggle();

  pros::delay(100);
  chassis.moveToPoint(-48, 0, 2000);
  chassis.turnToPoint(-44, -24, 1500, {.forwards = false});
  chassis.moveToPoint(-44, -24, 1500, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(20);
  clamp.toggle();
  pros::delay(100);
  chassis.turnToHeading(90, 1000);
  chassis.follow(mogo2_txt, 10, 5000);

  chassis.turnToPoint(-70, -70, 1000, {.forwards = false});
  chassis.moveToPoint(-70, -70, 1000, {.forwards = false});
  chassis.waitUntilDone();
  clamp.toggle();

  pros::delay(150);

  chassis.follow(mogo3_txt, 10, 3500);
  intake.setState(lib::IntakeState::In);

  pros::Task redring = pros::Task{[=] {
    while (!(color.get_hue() < 30 || color.get_hue() > 300)) {
      pros::delay(15);
    }
    intake.setState(lib::IntakeState::Idle);
  }};

  chassis.turnToPoint(48, 0, 1000, {.forwards = false});
  chassis.moveToPoint(55, 5, 1500, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(24);
  clamp.toggle();

  pros::delay(150);
  chassis.follow(mogo3rings_txt, 10, 4000);
  intake.setState(lib::IntakeState::In);

  chassis.turnToHeading(-45, 1000);
  chassis.follow(mogo3ring_txt, 10, 6000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::Idle);
  doinker.toggle();
  pros::delay(150);
  chassis.turnToHeading(90, 1000);
  chassis.turnToPoint(75, 70, 1000, {.forwards = false});
  chassis.moveToPoint(85, 80, 1000, {.forwards = false});
  chassis.waitUntilDone();
  clamp.toggle();
  chassis.moveToPoint(0, 0, 1000, {.maxSpeed = 45});

}