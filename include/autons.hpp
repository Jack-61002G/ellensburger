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
  chassis.setPose(-60, 6, -90);

  chassis.swingToPoint(-67.5, -0.5, lemlib::DriveSide::LEFT, 1000);
  pros::delay(150);
  lift.setTarget(210);
  chassis.waitUntilDone();

  pros::delay(300);
  chassis.moveToPoint(-23.5, 19.5, 2000, {.forwards = false, .maxSpeed = 70});

  chassis.waitUntil(28);
  lift.setTarget(75);
  clamp.extend();
  pros::delay(500);

  chassis.moveToPoint(-16.5, 27, 1000, {.maxSpeed = 80});

  chassis.turnToPoint(-16.5, 45, 500, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-16.5, 45, 1000, {.maxSpeed = 90});

  pros::delay(300);

  chassis.swingToHeading(25, lemlib::DriveSide::LEFT, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-20, 24, 500, {.forwards = false, .maxSpeed = 90});

  chassis.turnToPoint(-35, 45, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-35, 45, 1000, {.maxSpeed = 90});
  chassis.turnToPoint(-50, 8, 500, {.maxSpeed = 90});
  chassis.moveToPoint(-50, 8, 2000, {.maxSpeed = 60});
  intake.jam_override = true;

  pisstake.extend();
  chassis.waitUntilDone();
  pisstake.retract();
  pros::delay(800);

  chassis.moveToPoint(-50, 40, 1000, {.forwards = false, .maxSpeed = 60});

  chassis.turnToPoint(-27.5, 7.5, 1000, {.maxSpeed = 100});
  chassis.moveToPoint(-27.5, 7.5, 1000, {.maxSpeed = 100});
  intake.jam_override = false;
  chassis.waitUntil(12);
  lift.setTarget(150);
}

inline void blueRingSide() {
  chassis.setPose(60, 6, 90);

  chassis.swingToPoint(67.5, -0.6, lemlib::DriveSide::RIGHT, 1000);
  pros::delay(150);
  lift.setTarget(210);
  chassis.waitUntilDone();

  pros::delay(300);
  chassis.moveToPoint(23.5, 19.5, 2000, {.forwards = false, .maxSpeed = 70});

  chassis.waitUntil(28);
  lift.setTarget(75);
  clamp.extend();
  pros::delay(500);

  chassis.moveToPoint(17.5, 27, 1000, {.maxSpeed = 80});

  chassis.turnToPoint(17.5, 45, 500, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(17.5, 45, 1000, {.maxSpeed = 90});

  pros::delay(300);

  chassis.swingToHeading(-25, lemlib::DriveSide::RIGHT, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(20, 24, 500, {.forwards = false, .maxSpeed = 90});

  chassis.turnToPoint(35, 45, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(35, 45, 1000, {.maxSpeed = 90});
  chassis.turnToPoint(49.75, 6.75, 500, {.maxSpeed = 90});
  chassis.moveToPoint(49.75, 6.75, 2000, {.maxSpeed = 60});
  intake.jam_override = true;

  pisstake.extend();
  chassis.waitUntilDone();
  pisstake.retract();
  pros::delay(800);

  chassis.moveToPoint(50, 40, 1000, {.forwards = false, .maxSpeed = 60});

  chassis.turnToPoint(27.5, 7.5, 1000, {.maxSpeed = 100});
  chassis.moveToPoint(27.5, 7.5, 1000, {.maxSpeed = 100});
  intake.jam_override = false;
  chassis.waitUntil(12);
  lift.setTarget(150);
}

inline void redMogoRush() {
  chassis.setPose(-57.25, -48, 90);
  chassis.moveToPoint(-57, -48, 100);

  chassis.moveToPoint(-15.5, -48, 2000);
  lift.setTarget(150);
  intake.setState(lib::IntakeState::In);
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    while (!((color.get_hue() < 30 || color.get_hue() > 300) && color.get_proximity() > 200)) {
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

  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  clamp.extend();

  pros::delay(500);

  chassis.moveToPoint(-22, -30, 1000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::In);
  pros::delay(1500);

  chassis.turnToPoint(-57, -57, 1000);
  chassis.moveToPoint(-57, -57, 2000, {.maxSpeed = 100});

  chassis.waitUntilDone();
  pros::delay(750);
  intake.setState(lib::IntakeState::Out);

  chassis.moveToPoint(-72, -70, 1000, {.maxSpeed = 90});

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setState(lib::IntakeState::In);
  pros::delay(400);
  intake.jam_override = true;
  pros::delay(400);

  chassis.moveToPoint(-45, -45, 2000, {.forwards = false, .maxSpeed = 40});

  chassis.turnToPoint(-14, -14, 1000, {.maxSpeed = 60});
  intake.jam_override = false;
  chassis.moveToPoint(-14, -14, 4000, {.maxSpeed = 60});
  lift.setTarget(135);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::Idle);
}

inline void blueMogoRush() {
  chassis.setPose(57.25, -48, -90);
  chassis.moveToPoint(57, -48, 100);

  chassis.moveToPoint(15.75, -48, 2000);
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

  pros::delay(500);

  chassis.moveToPoint(22, -30, 1000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::In);
  pros::delay(1500);

  chassis.turnToPoint(57, -57, 1000);
  chassis.moveToPoint(57, -57, 2000, {.maxSpeed = 100});

  chassis.waitUntilDone();
  pros::delay(750);
  intake.setState(lib::IntakeState::Out);

  chassis.moveToPoint(73, -71, 1000, {.maxSpeed = 90});

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setState(lib::IntakeState::In);
  pros::delay(400);
  intake.jam_override = true;
  pros::delay(400);

  chassis.moveToPoint(45, -45, 2000, {.forwards = false, .maxSpeed = 40});

  chassis.turnToPoint(14.5, -14.5, 1000, {.maxSpeed = 60});
  intake.jam_override = false;
  chassis.moveToPoint(14.5, -14.5, 4000, {.maxSpeed = 60});
  lift.setTarget(135);
  chassis.waitUntilDone();
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

  lift.setTarget(230);
  pros::delay(700);
  chassis.moveToPoint(-47, 0, 500, {.forwards = false});

  // Grab first mogo
  chassis.turnToPoint(-47, 24, 1000, {.forwards = false});
  chassis.waitUntilDone();
  lift.setTarget(0);
  chassis.moveToPoint(-47, 24, 3000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(20);
  clamp.extend();
  pros::delay(200);

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

  chassis.turnToPoint(2, 48, 1000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::Idle);

  lift.setTarget(75);
  intake.jam_override = false;

  chassis.moveToPoint(2, 48, 1000, {.maxSpeed = 80});
  chassis.waitUntil(6);
  intake.setState(lib::IntakeState::In);

  chassis.turnToHeading(0, 1000);
  chassis.moveToPoint(2, 65, 1000);
  chassis.waitUntil(0.5);
  lift.setTarget(175);
  pros::delay(500);

  // back up and go to fill up mogo in left corner
  chassis.moveToPoint(0, 40, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToPoint(-24, 40, 1000, {.maxSpeed = 70});
  lift.setTarget(2);

  // long intake
  chassis.moveToPoint(-51, 40, 3000, {.maxSpeed = 64});

  // last guy before mogo drop
  chassis.turnToPoint(-48, 50, 1000, {.maxSpeed = 60});
  chassis.moveToPoint(-48, 50, 1000, {.maxSpeed = 75});

  // drop the mogo
  chassis.turnToPoint(-64, 64, 1000, {.forwards = false, .maxSpeed = 75});
  chassis.moveToPoint(-64, 64, 1000, {.forwards = false});
  clamp.retract();

  // cross to blue corner
  chassis.turnToPoint(30, 34, 1000);
  chassis.moveToPoint(30, 34, 5000, {.maxSpeed = 110});
  chassis.turnToPoint(44, 18, 1000);
  chassis.moveToPoint(44, 18, 5000, {.maxSpeed = 110});

  // shove goal into corner
  chassis.swingToPoint(65, 60, lemlib::DriveSide::LEFT, 1500, {.maxSpeed = 80});
  chassis.moveToPoint(65, 60, 2000);

  // back up and wall reset
  chassis.moveToPoint(60, 40, 1500, {.forwards = false, .maxSpeed = 100});
  intake.setState(lib::IntakeState::Out);
  chassis.turnToPoint(90, 40, 1000, {.forwards = false});
  chassis.moveToPoint(90, 40, 500, {.forwards = false, .maxSpeed = 65});
  intake.setState(lib::IntakeState::Idle);
  chassis.waitUntilDone();

  // reset position
  pros::delay(200);
  chassis.setPose(63.25, chassis.getPose().y, -90);
  pros::delay(100);

  chassis.moveToPoint(48, chassis.getPose().y, 1000, {.maxSpeed = 80});
  chassis.turnToPoint(48,5, 1200, {.forwards = false});
  chassis.moveToPoint(48, 5, 1200, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  clamp.extend();
  pros::delay(200);

  chassis.moveToPoint(48, 11, 1000, {.maxSpeed = 100});
  chassis.turnToPoint(24, 33, 1000, {.maxSpeed = 100});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(24, 33, 1100, {.maxSpeed = 100});
  chassis.waitUntilDone();
  pros::delay(750);
  intake.setState(lib::IntakeState::Idle);

  chassis.turnToPoint(-28, -22, 1000);
  chassis.moveToPoint(-28, -22, 3000, {.maxSpeed = 90});
  chassis.waitUntil(45);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-45, -36, 2000, {.maxSpeed = 65});

  // turn to face the driver box and intake the ring
  chassis.turnToHeading(-90, 1000);
  chassis.moveToPoint(-59, -36, 1000, {.maxSpeed = 80});

  // grab last of the angle rings
  chassis.turnToPoint(-52, -48, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(-52, -48, 1000, {.maxSpeed = 80});

  // drop off mogo
  chassis.turnToPoint(-68, -60, 1000, {.forwards = false});
  chassis.moveToPoint(-68, -60, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.retract();

  // intake last ring of the L for da wall stake
  chassis.turnToPoint(-28, -48, 1000);
  chassis.moveToPoint(-28, -48, 1000, {.maxSpeed = 80});
  lift.setTarget(30);

  // move to new mogo to clamp
  chassis.turnToPoint(-58, -24, 1500, {.forwards = false});
  intake.jam_override = true;
  chassis.moveToPoint(-58, -24, 2000, {.forwards = false, .maxSpeed = 60});
  pros::delay(300);
  chassis.waitUntilDone();
  clamp.extend();

  chassis.turnToPoint(-12, -55, 1000);
  chassis.moveToPoint(-12, -55, 1500, {.maxSpeed = 100});
  chassis.waitUntil(24);
  lift.setTarget(75);
  intake.setState(lib::IntakeState::Idle);

  // turn to da wall
  chassis.turnToHeading(180, 1000);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(chassis.getPose().x, -70, 1000, {.maxSpeed = 100});
  chassis.waitUntil(3);
  lift.setTarget(175);
  intake.jam_override = false;
  pros::delay(500);

  chassis.moveToPoint(chassis.getPose().x, -50, 1000, {.forwards = false, .maxSpeed = 100});
  chassis.turnToPoint(44, -55, 1000);
  lift.setTarget(2);
  chassis.moveToPoint(44, -55, 2000, {.maxSpeed = 90, .earlyExitRange = 1});
  doinker.extend();

  chassis.turnToPoint(60, -70, 1000);
  chassis.moveToPoint(60, -70, 500, {.maxSpeed = 100});
  chassis.swingToHeading(-150, lemlib::DriveSide::RIGHT, 1000);

  chassis.turnToHeading(-45, 1000, {.earlyExitRange = 2});
  doinker.retract();
  chassis.moveToPoint(56, -74, 1000, {.forwards = false, .maxSpeed = 100});
  pros::delay(200);
  clamp.retract();
  pros::delay(300);
  chassis.moveToPoint(34, -46, 1000, {.maxSpeed = 100});
};
