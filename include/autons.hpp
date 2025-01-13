#include "lemlib/chassis/chassis.hpp"
#include "lib/intake.hpp"
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
  teamColor = team::red;
  chassis.setPose(-60, 6, -90);

  chassis.swingToPoint(-67.5, 0, lemlib::DriveSide::LEFT, 1000);
  pros::delay(150);
  lift.setTarget(200);
  chassis.waitUntilDone();

  pros::delay(300);
  chassis.moveToPoint(-23.5, 19.5, 2000, {.forwards = false, .maxSpeed = 70});
  // lift.setTarget(150);

  chassis.waitUntil(28);
  lift.setTarget(75);
  clamp.extend();
  pros::delay(500);

  chassis.moveToPoint(-17.5, 27, 1000, {.maxSpeed = 80});

  chassis.turnToPoint(-16, 45, 500, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-16, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(-30, 45, 500, {.maxSpeed = 90});
  chassis.moveToPoint(-30, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(-24, 0, 1000);
  chassis.moveToPoint(-24, 0, 1000);
  chassis.waitUntilDone();
  lift.setTarget(150);
}

inline void blueRingSide() {
  teamColor = team::blue;
  chassis.setPose(60, 6, 90);

  chassis.swingToPoint(67.5, 0, lemlib::DriveSide::RIGHT, 1000);
  pros::delay(150);
  lift.setTarget(200);
  chassis.waitUntilDone();

  pros::delay(300);
  chassis.moveToPoint(23.5, 19.5, 2000, {.forwards = false, .maxSpeed = 70});
  // lift.setTarget(150);

  chassis.waitUntil(28);
  lift.setTarget(75);
  clamp.extend();
  pros::delay(500);

  chassis.moveToPoint(18, 27, 1000, {.maxSpeed = 80});

  chassis.turnToPoint(16.5, 45, 500, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(16.5, 45, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(30, 40, 500, {.maxSpeed = 90});
  chassis.moveToPoint(30, 40, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(25, 0, 1000);
  lift.setTarget(203);
  pros::delay(200);
  chassis.moveToPoint(25, 0, 1000);
  chassis.waitUntilDone();
  lift.setTarget(25);
}

inline void redMogoRush() {
  chassis.setPose(-57.25, -48, 90);
  chassis.moveToPoint(-57, -48, 100);

  chassis.moveToPoint(-15, -48, 2000);
  lift.setTarget(150);
  intake.setState(lib::IntakeState::In);
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    while (!((color.get_hue() < 30 || color.get_hue() > 300) &&
             color.get_proximity() > 200)) {
      pros::delay(15);
    }
    intake.setState(lib::IntakeState::Idle);
  }};

  chassis.waitUntil(38);
  lift.setTarget(230);
  intake.sort_override = false;
  chassis.moveToPose(-28, -46, 180, 1500, {.forwards = false});
  pros::delay(250);
  lift.setTarget(90);

  chassis.moveToPoint(-22, -24, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  clamp.extend();

  intake.setState(lib::IntakeState::In);
  pros::delay(1500);
  chassis.turnToPoint(0, 0, 1000);

  chassis.moveToPose(-16, -12, 45, 2000);
  chassis.waitUntilDone();
  lift.setTarget(135);
}

inline void blueMogoRush() {
  chassis.setPose(57.25, -48, -90);
  chassis.moveToPoint(57, -48, 100);

  chassis.moveToPoint(14, -48, 2000);
  chassis.waitUntil(2);
  lift.setTarget(150);
  intake.setState(lib::IntakeState::In);
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    while (!((color.get_hue() > 180 && color.get_hue() < 330) &&
             color.get_proximity() > 200)) {
      pros::delay(15);
    }
    intake.setState(lib::IntakeState::Idle);
  }};

  chassis.waitUntil(38);
  lift.setTarget(230);
  intake.sort_override = false;
  chassis.moveToPose(28, -46, 180, 1500, {.forwards = false});
  pros::delay(250);
  lift.setTarget(90);

  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  clamp.extend();

  intake.setState(lib::IntakeState::In);
  pros::delay(1500);
  chassis.turnToPoint(0, 0, 1000);

  chassis.moveToPose(12, -12, -45, 2000);
  chassis.waitUntilDone();
  lift.setTarget(135);
}

inline void skills() {

  chassis.setPose(-54, 0, -90);
  chassis.moveToPoint(-54, 0, 100);

  lift.setTarget(200);
  pros::delay(500);
  chassis.moveToPoint(-46, 0, 500, {.forwards = false});

  // Grab first mogo
  chassis.turnToPoint(-46, 24, 1000, {.forwards = false});
  chassis.waitUntilDone();
  lift.setTarget(0);
  chassis.moveToPoint(-46, 24, 3000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(20);
  clamp.toggle();
  pros::delay(250);

  chassis.follow(mogo1_txt, 10, 8000);
  intake.setState(lib::IntakeState::In);

  chassis.waitUntil(105);
  lift.setTarget(25);

  chassis.turnToPoint(1, 58, 500);
  chassis.moveToPoint(1, 58, 1500);
  chassis.waitUntil(36);
  lift.setTarget(60);
  while (!(color.get_hue() < 30 || color.get_hue() > 300)) {
    pros::delay(10);
  }
  intake.setState(lib::IntakeState::Idle);
  return;

  chassis.turnToPoint(0, 72, 500);
  chassis.turnToPoint(0, 72, 500);

  lift.setTarget(135);

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
  chassis.waitUntilDone();
  lift.setTarget(0);
  chassis.moveToPoint(-46, 24, 3000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(20);
  clamp.toggle();
  pros::delay(250);

  // rings on mogo + 1 wall

  // ring 1
  chassis.turnToPoint(-24, 24, 1000);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-24, 24, 1000);

  // second ring on the wall
  chassis.turnToPoint(24, 48, 1000);
  chassis.moveToPoint(24, 48, 1500);
  chassis.waitUntil(24);
  lift.setTarget(25);
  intake.jam_override = true;

  chassis.turnToPoint(0, 48, 1000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::Idle);

  chassis.moveToPoint(4, 48, 1000, {.maxSpeed = 80});
  chassis.waitUntil(6);
  lift.setTarget(75);
  intake.jam_override = false;
  chassis.waitUntil(12);
  intake.setState(lib::IntakeState::In);

  chassis.turnToHeading(0, 1000);
  chassis.moveToPoint(4, 63, 1000);
  lift.setTarget(135);
  chassis.waitUntilDone();

  // back up and go to fill up mogo in left corner

  chassis.moveToPoint(0, 40, 1000, {.forwards = false, .maxSpeed = 80});
  lift.setTarget(0);
  chassis.turnToPoint(-24, 40, 1000);

  // long intake
  chassis.moveToPoint(-50, 40, 3000, {.maxSpeed = 65});

  // last guy before mogo drop
  chassis.turnToPoint(-48, 50, 1000);
  chassis.moveToPoint(-48, 50, 1000);

  // drop the mogo
  chassis.turnToPoint(-65, 65, 1000, {.forwards = false});
  chassis.moveToPoint(-65, 65, 1000, {.forwards = false});
  clamp.set_value(false);

  // grab red ring from red/blue corner stack, grab blue goal, sweep corner,
  // place goal
  chassis.turnToPoint(48, 45, 1000);
  chassis.moveToPoint(48, 45, 2500, {.maxSpeed = 90});

  pros::Task ring = pros::Task{[=] {
    while (!((color.get_hue() < 30 || color.get_hue() > 300) &&
             color.get_proximity() > 200)) {
      pros::delay(15);
    }
    intake.setState(lib::IntakeState::Idle);
  }};

  chassis.turnToPoint(54, 24, 1000, {.forwards = false});
  chassis.moveToPoint(54, 24, 1500, {.forwards = false, .maxSpeed = 80});
  //breaks here

  chassis.turnToPoint(32, 50, 1000);
  chassis.moveToPoint(32, 50, 1000, {.maxSpeed = 90});

  chassis.turnToPoint(65, 65, 1000);
  chassis.moveToPoint(65, 65, 1000);
  doinker.set_value(1);
  chassis.turnToHeading(180, 1000);
  chassis.waitUntilDone();
  clamp.set_value(0);
  doinker.set_value(0);
};