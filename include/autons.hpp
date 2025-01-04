#include "lemlib/chassis/chassis.hpp"
#include "lib/intake.hpp"
#include "lib/lift.hpp"
#include "pros/llemu.hpp"
#include "robotconfig.h"
#include <functional>

ASSET(mogo1_txt)
ASSET(wall1_txt)
ASSET(mogo3_txt)
ASSET(mogo2_txt)
ASSET(mogo3rings_txt)
ASSET(mogo3ring_txt)
ASSET(mogo4rush_txt)
ASSET(nyoooom_txt)



inline void redRingSide() {
  chassis.setPose(-60, 6, -90);

  chassis.swingToPoint(-67.5, 0, lemlib::DriveSide::LEFT, 1000);
  pros::delay(200);

  lift.setTarget(200);
  pros::delay(750);
  chassis.moveToPoint(-23.5, 19.5, 2000, {.forwards = false, .maxSpeed = 70});
  //pros::delay(200);
  lift.setTarget(-20);

  chassis.waitUntil(28);
  clamp.extend();
  pros::delay(1000);

  chassis.moveToPoint(-17.5, 27, 1000, {.maxSpeed = 80});

  chassis.turnToPoint(-16.25, 45, 500, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-16.25, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(-30, 45, 500, {.maxSpeed = 90});
  chassis.moveToPoint(-30, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(-55, 45, 500, {.maxSpeed = 90});
  chassis.moveToPoint(-55, 45, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-65, 60, 1000, {.maxSpeed = 90});
  pros::delay(500);

  chassis.moveToPoint(-50, 45, 500, {.forwards = false, .maxSpeed = 90});
  chassis.moveToPoint(-15, 8, 2000, {.maxSpeed = 90});
  lift.setTarget(30);
  pros::delay(500);
  intake.setState(lib::IntakeState::Idle);
}



inline void blueRingSide() {
  chassis.setPose(60, 6, -135);
  chassis.moveToPoint(52, 36, 100);

  lift.setTarget(150);
  pros::delay(750);
  chassis.moveToPoint(12, 30, 1500, {.forwards = false});

  chassis.waitUntil(24);
  clamp.extend();

  chassis.turnToPoint(6, 52, 500);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(6, 52, 1000);

  chassis.turnToPoint(28, 45, 500);
  chassis.moveToPoint(28, 45, 1000);

  chassis.turnToPoint(67, 67, 500);
  chassis.moveToPoint(67, 67, 1000);
  pros::delay(500);

  chassis.moveToPoint(48, 48, 500, {.forwards = false});
  chassis.moveToPoint(10, 10, 1000, {.maxSpeed = 90});
  lift.setTarget(30);
}



inline void redMogoRush() {
  chassis.setPose(-57.25, -48, 90);
  chassis.moveToPoint(-57, -48, 100);

  chassis.moveToPoint(-14, -48, 2000, {.earlyExitRange=1});
  lift.setTarget(150);
  intake.setState(lib::IntakeState::In);
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    pros::delay(1200);
    intake.setState(lib::IntakeState::Idle);
  }};

  chassis.waitUntil(39);
  lift.setTarget(250);
  intake.sort_override = false;
  chassis.moveToPose(-30, -46, 180, 1500, {.forwards = false});
  pros::delay(700);
  lift.setTarget(-20);
  pros::delay(800);
  
  chassis.turnToPoint(-24, -24, 1000, {.forwards = false});
  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  clamp.extend();

  intake.setState(lib::IntakeState::In);
  pros::delay(500);
  chassis.turnToPoint(-60, -60, 1000, {.maxSpeed = 80});

  chassis.moveToPose(-65, -65, -135, 2000);
  chassis.waitUntil(36);
  intake.setState(lib::IntakeState::Out);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::In);

  pros::delay(1000);

  chassis.moveToPoint(-50, -50, 500, {.forwards = false});
  chassis.moveToPoint(-10, -10, 2000, {.maxSpeed = 90});
  lift.setTarget(30);

  pros::delay(1000);
  intake.setState(lib::IntakeState::Idle);

}



inline void blueMogoRush() {
  chassis.setPose(57.25, -48, -90);
  chassis.moveToPoint(57, -48, 100);

  chassis.moveToPoint(14, -48, 2000);
  lift.setTarget(150);
  intake.setState(lib::IntakeState::In);
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    pros::delay(1200);
    intake.setState(lib::IntakeState::Idle);
  }};

  chassis.waitUntil(38);
  lift.setTarget(230);
  intake.sort_override = false;
  chassis.moveToPose(30, -46, 180, 1500, {.forwards = false});
  pros::delay(250);
  lift.setTarget(90);
  

  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  clamp.extend();

  intake.setState(lib::IntakeState::In);
  pros::delay(1500);
  chassis.turnToPoint(60, -60, 1000);

  chassis.moveToPose(65, -60, -135, 2000);
  chassis.waitUntil(36);
  intake.setState(lib::IntakeState::Out);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::In);
}



inline void skills() {

  chassis.setPose(-54, 0, -90);
  chassis.moveToPoint(-54, 0, 100);

  lift.setTarget(200);
  pros::delay(500);
  chassis.moveToPoint(-46, 0, 500, {.forwards = false});

  // Grab first mogo
  chassis.turnToPoint(-46, 24, 1000, {.forwards = false});
  lift.setState(lib::LiftState::Reset);
  chassis.moveToPoint(-46, 24, 3000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(20);
  clamp.toggle();
  pros::delay(250);

  chassis.follow(mogo1_txt, 10, 8000);
  intake.setState(lib::IntakeState::In);

  chassis.waitUntil(105);
  lift.setState(lib::LiftState::Recieve);

  chassis.turnToPoint(1, 58, 500);
  chassis.moveToPoint(1, 58, 1500);
  chassis.waitUntil(36);
  lift.setTarget(60);
  while (!(color.get_hue() < 30 || color.get_hue() > 300)) { pros::delay(10); }
  intake.setState(lib::IntakeState::Idle);
  return;

  chassis.turnToPoint(0, 72, 500);
  chassis.turnToPoint(0, 72, 500);

  lift.setState(lib::LiftState::Score);
  
  return;
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