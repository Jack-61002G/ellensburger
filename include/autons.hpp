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
  chassis.waitUntilDone();

  pros::delay(1000);
  chassis.moveToPoint(-23.5, 19.5, 2000, {.forwards = false, .maxSpeed = 70});
  //lift.setTarget(150);

  chassis.waitUntil(28);
  lift.setTarget(40);
  clamp.extend();
  pros::delay(1000);

  chassis.moveToPoint(-17.5, 27, 1000, {.maxSpeed = 80});

  chassis.turnToPoint(-16, 45, 500, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-16, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(-30, 45, 500, {.maxSpeed = 90});
  chassis.moveToPoint(-30, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(-48, 0, 500, {.maxSpeed = 90});
  chassis.moveToPoint(-48, -10, 1500, {.maxSpeed = 80});

  chassis.turnToPoint(-40, 30, 500, {.maxSpeed = 80});
  chassis.moveToPoint(-40, 30, 1000, {.maxSpeed = 80});
  intake.setState(lib::IntakeState::Idle);

  chassis.turnToPoint(-10, 0, 500, {.maxSpeed = 80});
  chassis.moveToPoint(-10, 0, 1000, {.maxSpeed = 80});
}



inline void blueRingSide() {
  chassis.setPose(60, 6, 90);

  chassis.swingToPoint(67.5, -1, lemlib::DriveSide::RIGHT, 1000);
  pros::delay(200);
  lift.setTarget(200);

  chassis.moveToPoint(23.5, 19.5, 2000, {.forwards = false, .maxSpeed = 70});

  chassis.waitUntil(28);
  lift.setTarget(40);
  clamp.extend();
  pros::delay(1000);

  chassis.moveToPoint(17.5, 27, 1000, {.maxSpeed = 80});

  chassis.turnToPoint(16, 45, 500, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(16, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(30, 45, 500, {.maxSpeed = 90});
  chassis.moveToPoint(30, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(48, 0, 500, {.maxSpeed = 90});
  chassis.moveToPoint(48, -10, 1500, {.maxSpeed = 80});

  chassis.turnToPoint(40, 30, 500, {.maxSpeed = 80});
  chassis.moveToPoint(40, 30, 1000, {.maxSpeed = 80});
  intake.setState(lib::IntakeState::Idle);

  chassis.turnToPoint(10, 0, 500, {.maxSpeed = 80});
  chassis.moveToPoint(10, 0, 1000, {.maxSpeed = 80});
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
  chassis.setPose(53, -59.5, -90);
  chassis.moveToPoint(53, -59.5, 100);

  chassis.moveToPoint(24, -59.5, 1000, {.minSpeed = 60, .earlyExitRange = 2});
  lift.setTarget(140);
  chassis.moveToPoint(14.5, -52.5, 1000, {.earlyExitRange = 1});
  chassis.waitUntil(12.5);
  lift.setTarget(250);

  chassis.waitUntilDone();
  pros::delay(200);

  chassis.turnToHeading(180, 1000, {.maxSpeed = 100});
  lift.setTarget(50);

  chassis.moveToPoint(36, -18, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntil(33);
  clamp.extend();
  chassis.waitUntilDone();
  pros::delay(500);

  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(24, -50, 1000);

  chassis.waitUntilDone();
  pros::delay(1000);
  intake.setState(lib::IntakeState::Idle);
  return;

  chassis.turnToPoint(60, -60, 1000, {.maxSpeed = 80});

  chassis.moveToPose(65, -65, -135, 2000);
  chassis.waitUntil(36);
  intake.setState(lib::IntakeState::Out);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::In);

  pros::delay(1000);

  chassis.moveToPoint(50, -50, 500, {.forwards = false});
  chassis.moveToPoint(10, -10, 2000, {.maxSpeed = 90});
  lift.setTarget(30);

  pros::delay(1000);
  intake.setState(lib::IntakeState::Idle);

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

inline void oldskills() {


  // first mogo clamp + alliance stake

  
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

  // rings on mogo + 1 wall 

  //ring 1
  chassis.turnToPoint(-24, 24, 1000);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-24, 24, 1000);

  // second ring on the wall
  lift.setState(lib::LiftState::Recieve);
  chassis.turnToPoint(24, 48, 1000);
  chassis.moveToPoint(24, 48, 1000);

  chassis.turnToPoint(0, 58, 1000);
  chassis.moveToPoint(0, 58, 1000);

  lift.setTarget(70);
  chassis.turnToHeading(0, 1000);
  chassis.moveToPoint(0, 63, 1000);
  chassis.waitUntilDone();
  lift.setTarget(120);
  pros::delay(250);

  //back up and go to fill up mogo in left corner

  chassis.moveToPoint(0, 48, 1000);
  chassis.turnToPoint(-24, 48, 1000);

  //long intake
  chassis.moveToPoint(-56, 24, 3000, {.maxSpeed = 70});

  //last guy before mogo drop
  chassis.turnToPoint(-48, 56, 1000);
  chassis.moveToPoint(-48, 56, 1000);

  //drop the mogo
  chassis.turnToPoint(-65, -65, 1000, {.forwards = false});
  chassis.moveToPoint(-65, -65, 1000, {.forwards = false});
  clamp.set_value(false);

  //grab red ring from red/blue corner stack, grab blue goal, sweep corner, place goal



};