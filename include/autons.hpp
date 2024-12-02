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

  intake.setState(lib::IntakeState::In);
  lift.setTarget(90);
  chassis.moveToPoint(-8, 39, 1500, {.earlyExitRange = 0});
  chassis.moveToPose(-24, 20, 45, 1000, {.forwards = false});
  pros::delay(500);
  intake.setState(lib::IntakeState::Idle);
  chassis.waitUntilDone();
  clamp.toggle();
  pros::delay(150);
  chassis.moveToPoint(-24, 56, 1000);
  intake.setState(lib::IntakeState::In);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.moveToPose(-4, 48, 90, 2000);
  chassis.moveToPose(-55, 8, 35, 2000, {.forwards = false});
  chassis.turnToPoint(-64, 0, 1000);
  chassis.waitUntilDone();
  lift.setTarget(170);
  pros::delay(1500);
  chassis.moveToPoint(-36, 8, 1000, {.forwards = false});
  chassis.moveToPose(-20, 0, 90, 1000, {.lead = .1});
}

inline void blueRingSide() {

  chassis.setPose(52, 36, -90);

  intake.setState(lib::IntakeState::In);
  lift.setTarget(90);
  chassis.moveToPoint(8, 39, 1500, {.earlyExitRange = 0});
  chassis.moveToPose(24, 20, -45, 1000, {.forwards = false});
  pros::delay(350);
  intake.setState(lib::IntakeState::Idle);
  chassis.waitUntilDone();
  clamp.toggle();
  pros::delay(150);
  chassis.moveToPoint(24, 56, 1000);
  intake.setState(lib::IntakeState::In);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.moveToPose(4, 48, -90, 2000);
  chassis.moveToPose(55, 8, -35, 2000, {.forwards = false});
  chassis.turnToPoint(64, 0, 1000);
  chassis.waitUntilDone();
  lift.setTarget(170);
  pros::delay(1500);
  chassis.moveToPoint(36, 8, 1000, {.forwards = false});
  chassis.moveToPose(20, 0, -90, 1000, {.lead = .1});
}

inline void redMogo() {
  chassis.setPose(-52, -56, 90);

  chassis.moveToPoint(-12, -53, 1000);
  doinker.toggle();
  chassis.waitUntil(25);
  rushClamp.toggle();
  chassis.moveToPoint(-30, -56, 1000, {.forwards = false});
  chassis.waitUntil(5);
  rushClamp.toggle();
  chassis.waitUntilDone();
  doinker.toggle();

  chassis.turnToPoint(-8, -49, 1000, {.forwards = false});
  chassis.moveToPoint(-8, -49, 1000, {.forwards = false});
  chassis.waitUntilDone();
  clamp.toggle();
  intake.setState(lib::IntakeState::In);
  pros::delay(1000);

  chassis.moveToPose(-36, -36, -35, 1000);
  pros::Task redring = pros::Task{[=] {
    while (!(color.get_hue() > 180 && color.get_hue() < 330)) {
      pros::delay(15);
      intake.setState(lib::IntakeState::Idle);
    }
  }};
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