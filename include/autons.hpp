#include "lemlib/chassis/chassis.hpp"
#include "lib/intake.hpp"
#include "pros/rtos.hpp"
#include "robodash/views/console.hpp"
#include "robotconfig.h"
#include "lib/reset.hpp"
#include "lib/color.hpp"

ASSET(mogo1_txt)
ASSET(wall1_txt)
ASSET(mogo3_txt)
ASSET(mogo2_txt)
ASSET(mogo3rings_txt)
ASSET(mogo3ring_txt)
ASSET(mogo4rush_txt)
ASSET(nyoooom_txt)



inline void redSoloAWP() {
  chassis.setPose(-56, 12.5, -135);

  // score on alliance stake
  chassis.moveToPoint(-59, 9.5, 470);
  lift.setTarget(220);
  chassis.waitUntilDone();
  
  // clamp goal
  pros::delay(500);
  chassis.moveToPoint(-48, 24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 11});
  chassis.moveToPoint(-23, 24, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 4});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  // first ring
  pros::delay(250);
  chassis.turnToPoint(-24, 48, 750, {.minSpeed = 50, .earlyExitRange = 3.5});
  chassis.moveToPoint(-24, 48, 1000, {.maxSpeed = 100});
  intake.setState(lib::IntakeState::In);

  // quad stack
  chassis.waitUntilDone();
  pros::delay(250);
  chassis.turnToPoint(-6, 52, 750, {.minSpeed = 50, .earlyExitRange = 6});
  chassis.moveToPoint(-6, 52, 1000, {.maxSpeed = 90});

  // back out
  chassis.waitUntilDone();
  pros::delay(200);
  chassis.moveToPoint(-24, 50, 1000, {.forwards = false, .maxSpeed = 100, .minSpeed = 30, .earlyExitRange = 2});

  chassis.turnToPoint(-47, 4, 750);
  chassis.moveToPoint(-47, 4, 1200, {.maxSpeed = 100, .minSpeed = 30, .earlyExitRange = 3});
  pisstake.extend();

  chassis.waitUntilDone();
  pisstake.retract();
  clamp.retract();

  chassis.moveToPoint(-48, -6, 1000, {.maxSpeed = 75});

  int start = pros::millis();
  while (!color.seesRed() && pros::millis() - start < 1300) { pros::delay(50); }

  intake.setState(lib::IntakeState::Idle);
  chassis.turnToPoint(-24, -24, 1000, {.forwards = false});
  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .maxSpeed = 90});
  chassis.waitUntil(24);
  clamp.extend();

  chassis.waitUntilDone();
  pros::delay(250);
  chassis.turnToPoint(-24, -51, 1000, {.minSpeed = 40, .earlyExitRange = 4});
  chassis.moveToPoint(-24, -51, 1000, {.maxSpeed = 75});
  intake.setState(lib::IntakeState::In);

  chassis.waitUntilDone();
  pros::delay(250);

  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 40, .earlyExitRange = 6});
  pros::delay(250);
  lift.setTarget(45);
  chassis.moveToPoint(-6, -6, 500);
  intake.setState(lib::IntakeState::Idle);
}



inline void blueSoloAWP() {
  chassis.setPose(56, 12.5, 135);

  // score on alliance stake
  chassis.moveToPoint(59, 9.5, 470);
  lift.setTarget(220);
  chassis.waitUntilDone();
  
  // clamp goal
  pros::delay(500);
  chassis.moveToPoint(48, 24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 11});
  chassis.moveToPoint(23, 24, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 4});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  // first ring
  pros::delay(250);
  chassis.turnToPoint(24, 48, 750, {.minSpeed = 50, .earlyExitRange = 3.5});
  chassis.moveToPoint(24, 48, 1000, {.maxSpeed = 100});
  intake.setState(lib::IntakeState::In);

  // quad stack
  chassis.waitUntilDone();
  pros::delay(250);
  chassis.turnToPoint(6, 52, 750, {.minSpeed = 50, .earlyExitRange = 6});
  chassis.moveToPoint(6, 52, 1000, {.maxSpeed = 90});

  // back out
  chassis.waitUntilDone();
  pros::delay(200);
  chassis.moveToPoint(24, 50, 1000, {.forwards = false, .maxSpeed = 100, .minSpeed = 30, .earlyExitRange = 2});

  chassis.turnToPoint(47, 4, 750);
  chassis.moveToPoint(47, 4, 1200, {.maxSpeed = 100, .minSpeed = 30, .earlyExitRange = 3});
  pisstake.extend();

  chassis.waitUntilDone();
  pisstake.retract();
  clamp.retract();

  chassis.moveToPoint(48, -6, 1000, {.maxSpeed = 75});

  int start = pros::millis();
  while (!color.seesBlue() && pros::millis() - start < 1300) { pros::delay(50); }

  intake.setState(lib::IntakeState::Idle);
  chassis.turnToPoint(24, -24, 1000, {.forwards = false});
  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .maxSpeed = 90});
  chassis.waitUntil(24);
  clamp.extend();

  chassis.waitUntilDone();
  pros::delay(250);
  chassis.turnToPoint(24, -51, 1000, {.minSpeed = 40, .earlyExitRange = 4});
  chassis.moveToPoint(24, -51, 1000, {.maxSpeed = 75});
  intake.setState(lib::IntakeState::In);

  chassis.waitUntilDone();
  pros::delay(250);

  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 40, .earlyExitRange = 6});
  pros::delay(250);
  lift.setTarget(45);
  chassis.moveToPoint(6, -6, 500);
  intake.setState(lib::IntakeState::Idle);
}



inline void redRingSide() {
  chassis.setPose(-56, 12.5, -135);

  // score on alliance stake
  chassis.moveToPoint(-59, 9.5, 480);
  lift.setTarget(215);
  chassis.waitUntilDone();
  
  // clamp goal
  pros::delay(500);
  chassis.moveToPoint(-48, 24, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 6});
  chassis.moveToPoint(-23, 24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 6});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  // intake quad stack
  pros::delay(250);
  chassis.moveToPoint(-8, 42, 1200, {.maxSpeed = 80});
  intake.setState(lib::IntakeState::In);

  chassis.turnToPoint(-8.5, 55, 1000, {.maxSpeed = 100});
  chassis.moveToPoint(-8.5, 55, 1500, {.maxSpeed = 100});

  chassis.waitUntilDone();

  // back out
  chassis.moveToPoint(-10.5, 40, 500, {.forwards = false, .maxSpeed = 90});
  
  chassis.turnToPoint(-70.5, 69.5, 1000);
  chassis.moveToPoint(-70.5, 69.5, 2000, {.maxSpeed = 68});

  int start = pros::millis();
  while (!color.seesBlue() && pros::millis() - start < 1750) {pros::delay(50);}

  pros::delay(150);
  intake.setState(lib::IntakeState::Out);
  intake.jam_override = true;

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setState(lib::IntakeState::In);
  pros::delay(200);

  chassis.moveToPoint(-50, 50, 1000, {.forwards = false});
  chassis.moveToPoint(-68, 67, 1000);

  chassis.moveToPoint(-48, 48, 2000, {.forwards = false, .maxSpeed = 90});

  chassis.turnToPoint(-46.5, 6, 500);
  chassis.moveToPoint(-46.5, 6, 3000, {.maxSpeed = 90, .minSpeed = 30, .earlyExitRange = 2});

  intake.jam_override = false;

  pisstake.extend();
  chassis.waitUntilDone();
  pisstake.retract();

  /*       positive corner rush
  chassis.moveToPoint(-46, 10, 400, {.forwards = false});
  chassis.moveToPoint(-67, -75, 1500);
  return;
  */

  chassis.turnToPoint(-24, 0, 750, {.minSpeed = 50, .earlyExitRange = 5});
  lift.setTarget(200);
  chassis.moveToPoint(-24, 0, 1000, {.maxSpeed = 50});
}



inline void blueRingSide() {
  chassis.setPose(56, 12.5, 135);

  // score on alliance stake
  chassis.moveToPoint(59, 9.5, 480);
  lift.setTarget(215);
  chassis.waitUntilDone();
  
  // clamp goal
  pros::delay(500);
  chassis.moveToPoint(48, 24, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 6});
  chassis.moveToPoint(23, 24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 6});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  // intake quad stack
  pros::delay(250);
  chassis.moveToPoint(8.5, 42, 1200, {.maxSpeed = 80});
  intake.setState(lib::IntakeState::In);

  chassis.turnToPoint(9.25, 55, 1000, {.maxSpeed = 100});
  chassis.moveToPoint(9.25, 55, 1500, {.maxSpeed = 100});

  chassis.waitUntilDone();

  // back out
  chassis.moveToPoint(10.5, 40, 500, {.forwards = false, .maxSpeed = 90});
  
  chassis.turnToPoint(71, 69, 1000);
  chassis.moveToPoint(71, 69, 2000, {.maxSpeed = 68});

  int start = pros::millis();
  while (!color.seesRed() && pros::millis() - start < 1750) {pros::delay(50);}

  pros::delay(150);
  intake.setState(lib::IntakeState::Out);
  intake.jam_override = true;

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setState(lib::IntakeState::In);
  pros::delay(200);

  chassis.moveToPoint(50, 50, 1000, {.forwards = false});
  chassis.moveToPoint(68, 67, 1000);

  chassis.moveToPoint(48, 48, 2000, {.forwards = false, .maxSpeed = 90});

  chassis.turnToPoint(46.5, 5.5, 500);
  chassis.moveToPoint(46.5, 5.5, 3000, {.maxSpeed = 90, .minSpeed = 30, .earlyExitRange = 2});

  intake.jam_override = false;

  pisstake.extend();
  chassis.waitUntilDone();
  pisstake.retract();

  /*       positive corner rush
  chassis.moveToPoint(46, 10, 400, {.forwards = false});
  chassis.moveToPoint(67, -75, 1500);
  return;
  */

  chassis.turnToPoint(24, 0, 750, {.minSpeed = 50, .earlyExitRange = 5});
  lift.setTarget(200);
  chassis.moveToPoint(24, 0, 1000, {.maxSpeed = 50});
}



inline void redGoalSide() {
  chassis.setPose(-54, -24, -90);

  chassis.moveToPoint(-26, -24, 1000, {.forwards = false, .maxSpeed = 70});
  chassis.waitUntilDone();
  clamp.extend();

  chassis.turnToPoint(-10, -10, 750);
  chassis.moveToPoint(-10, -10, 1000, {.maxSpeed = 100});
  chassis.waitUntilDone();
  doinker.extend();

  pros::delay(1000);
  chassis.moveToPoint(-24, -24, 1000, {.forwards = false});
  doinker.retract();

  pros::delay(250);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-16, -16, 1000);

  chassis.moveToPoint(-24, -24, 1000, {.forwards = false});

  chassis.turnToPoint(-24, -48, 1000);
  chassis.moveToPoint(-24, -48, 1000);

  chassis.turnToPoint(-70, -70, 1000);
  chassis.moveToPoint(-70, -70, 2000, {.maxSpeed = 68});

  pros::delay(800);
  intake.setState(lib::IntakeState::Out);
  intake.jam_override = true;

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setState(lib::IntakeState::In);
  pros::delay(200);

  chassis.moveToPoint(-50, -50, 1000, {.forwards = false});
  chassis.moveToPoint(-68, -67, 1000);
  chassis.moveToPoint(-48, -48, 2000, {.forwards = false, .maxSpeed = 90});
  intake.jam_override = false;
}



inline void redMogoRush() {
  chassis.setPose(-55.5, -48, 90);

  chassis.moveToPoint(-15.5, -48, 2000);
  lift.setTarget(150);
  intake.setState(lib::IntakeState::In);
  pisstake.retract();
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    while (!color.seesRed()) {
      pros::delay(15);
    }
    intake.setState(lib::IntakeState::Idle);
  }};

  chassis.waitUntil(38);
  lift.setTarget(230);
  intake.sort_override = false;

  chassis.waitUntilDone();
  pros::delay(200);
  chassis.moveToPose(-28, -46, 180, 1500, {.forwards = false});
  pros::delay(250);
  lift.setTarget(90);

  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  clamp.extend();

  pros::delay(400);

  chassis.moveToPoint(-22, -30, 1000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::In);
  pros::delay(1300);

  chassis.turnToPoint(-57, -57, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-57, -57, 2000, {.maxSpeed = 100});

  chassis.waitUntilDone();
  pros::delay(250);
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
  chassis.moveToPoint(-14, -14, 2500, {.maxSpeed = 60});
  lift.setTarget(135);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::Idle);
}



inline void blueMogoRush() {
  chassis.setPose(55.5, -48, -90);

  chassis.moveToPoint(15.5, -48, 2000);
  lift.setTarget(150);
  intake.setState(lib::IntakeState::In);
  pisstake.retract();
  intake.sort_override = true;

  pros::Task ring = pros::Task{[=] {
    while (!color.seesBlue()) {
      pros::delay(15);
    }
    intake.setState(lib::IntakeState::Idle);
  }};

  chassis.waitUntil(38);
  lift.setTarget(230);
  intake.sort_override = false;

  chassis.waitUntilDone();
  pros::delay(200);
  chassis.moveToPose(28, -46, 180, 1500, {.forwards = false});
  pros::delay(250);
  lift.setTarget(90);

  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  clamp.extend();

  pros::delay(400);

  chassis.moveToPoint(22, -30, 1000);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::In);
  pros::delay(1300);

  chassis.turnToPoint(57, -57, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(57, -57, 2000, {.maxSpeed = 100});

  chassis.waitUntilDone();
  pros::delay(250);
  intake.setState(lib::IntakeState::Out);

  chassis.moveToPoint(72, -70, 1000, {.maxSpeed = 90});

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setState(lib::IntakeState::In);
  pros::delay(400);
  intake.jam_override = true;
  pros::delay(400);

  chassis.moveToPoint(45, -45, 2000, {.forwards = false, .maxSpeed = 40});

  chassis.turnToPoint(14, -14, 1000, {.maxSpeed = 60});
  intake.jam_override = false;
  chassis.moveToPoint(14, -14, 2500, {.maxSpeed = 60});
  lift.setTarget(135);
  chassis.waitUntilDone();
  intake.setState(lib::IntakeState::Idle);
}



inline void skills() {
  rd::Console console;
  chassis.setPose(-54, 0, -90);
  chassis.moveToPoint(-54, 0, 100);

  // Score alliance stake
  lift.setTarget(230);
  pros::delay(700);
  chassis.moveToPoint(-47, 0, 500, {.forwards = false});

  // Grab first mogo
  chassis.turnToPoint(-47.75, 24, 1000, {.forwards = false, .minSpeed = 80});
  chassis.waitUntilDone();
  lift.setTarget(0);
  chassis.moveToPoint(-47.75, 24.1, 3000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(18.2);
  clamp.extend();
  pros::delay(200);

  // ring 1
  chassis.turnToPoint(-25, 24, 1000, {.minSpeed = 80});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-25, 24, 1000);

  // second ring
  chassis.turnToPoint(24.5, 50, 1000, {.minSpeed = 80});
  chassis.moveToPoint(24.5, 50, 1500);
  chassis.waitUntil(24);
  lift.setTarget(20);
  intake.arm_loading = true;

  // move to wall stake
  pros::delay(600);
  chassis.moveToPoint(-1, 41, 1000, {.forwards = false, .maxSpeed = 100});

  pros::delay(800);
  intake.setState(lib::IntakeState::Idle);
  lift.setTarget(75);

  pros::delay(300);
  intake.setState(lib::IntakeState::In);

  // score on wall
  chassis.turnToPoint(-1, 63.5, 1000);
  chassis.moveToPoint(-1, 63.5, 1000);
  chassis.waitUntil(12.25);
  lift.setTarget(175);
  intake.arm_loading = false;
  intake.jam_override = false;
  pros::delay(500);

  // back up and go to fill up mogo in left corner
  chassis.moveToPoint(-3, 47, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToPoint(-24, 48, 1000, {.minSpeed = 80});
  lift.setTarget(75);

  // long intake
  chassis.moveToPoint(-60, 48, 3000, {.maxSpeed = 70});
  intake.setState(lib::IntakeState::In);

  // last guy before mogo drop
  chassis.waitUntilDone();
  pros::delay(75);
  chassis.turnToPoint(-48, 60, 1000, {.minSpeed = 50});
  chassis.moveToPoint(-48, 60, 1000, {.maxSpeed = 80});

  // back into corner
  chassis.turnToPoint(-61, 63, 1000, {.forwards = false, .maxSpeed = 70});
  chassis.moveToPoint(-61, 63, 1000, {.forwards = false});

  // cross to blue corner
  chassis.turnToPoint(41, 46, 1000, {.minSpeed = 80});
  pros::delay(300);
  clamp.retract();
  chassis.moveToPoint(41, 46, 5000, {.maxSpeed = 110});

  // get ready to hold ring from blue corner 
  lift.setTarget(20);
  intake.arm_loading = true;
  pros::delay(1000);
  doinker.extend();

  chassis.waitUntilDone();
  pros::delay(50);
  chassis.turnToHeading(0, 1500);
  chassis.waitUntilDone();
  pros::delay(250);
  lib::wallReset(lib::dir::Y_PLUS);
  pros::delay(50);

  // grab blue goal
  chassis.turnToPoint(56, 24, 1000, {.forwards = false, .minSpeed = 80});

  intake.setState(lib::IntakeState::Idle);
  lift.setTarget(75);
  pros::delay(350);
  intake.setState(lib::IntakeState::Out);

  chassis.moveToPoint(56, 24, 2000, {.forwards = false, .maxSpeed = 85});
  doinker.retract();
  chassis.waitUntilDone();
  clamp.extend();
  
  // shove goal into corner
  chassis.turnToPoint(66, 66, 1000, {.minSpeed = 90});
  pros::delay(250);
  doinker.extend();
  chassis.moveToPoint(66, 66, 1500, {.maxSpeed = 90});

  chassis.turnToPoint(0, 0, 2000, {.minSpeed = 90});
  pros::delay(300);
  doinker.retract();
  chassis.moveToPoint(80, 80, 550, {.forwards = false});
  clamp.retract();
  doinker.retract();
  pros::delay(250);


  // back up and clamp empty goal
  chassis.moveToPoint(48, 48, 500);
  chassis.turnToPoint(48, -3, 1000 ,{.forwards = false, .minSpeed = 50, .earlyExitRange = 5});
  chassis.moveToPoint(48, -3, 2000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(47);
  clamp.extend();

  // wall reset
  chassis.turnToHeading(90, 1500);
  chassis.waitUntilDone();
  pros::delay(250);
  lib::wallReset(lib::dir::X_PLUS);
  pros::delay(50);
  intake.setState(lib::IntakeState::Idle);

  // turn to the alliance stake and score on it
  chassis.moveToPoint(55, -1.5, 750, {.maxSpeed = 100});
  chassis.waitUntilDone();
  lift.setTarget(250);
  intake.arm_loading = false;
  intake.jam_override = false;
  pros::delay(500);

  chassis.moveToPoint(48, 0, 750, {.forwards = false, .minSpeed = 80});

  chassis.turnToPoint(26, 24, 1000, {.minSpeed = 50, .earlyExitRange = 5});
  lift.setTarget(2);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(26, 24, 1100, {.maxSpeed = 100});
  chassis.waitUntilDone();
  pros::delay(750);
  intake.setState(lib::IntakeState::Idle);

  // cross under ladder
  chassis.turnToPoint(-23, -24, 1000, {.minSpeed = 50, .earlyExitRange = 5});
  chassis.moveToPoint(-23, -24, 3000, {.minSpeed = 40, .earlyExitRange = 6});
  chassis.waitUntil(45.5);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-42, -46, 2000, {.maxSpeed = 80});

  chassis.turnToHeading(-90, 1500);
  chassis.waitUntilDone();

  pros::delay(250);
  lib::wallReset(lib::dir::X_MINUS);
  pros::delay(50);

  // turn to face the driver box and intake the ring
  chassis.moveToPoint(-60, -48, 1000, {.maxSpeed = 90});

  chassis.turnToHeading(180, 1500);
  chassis.waitUntilDone();

  pros::delay(250);
  lib::wallReset(lib::dir::Y_MINUS);
  pros::delay(50);

  // grab last of the angle rings
  chassis.turnToPoint(-47.75, -61, 1000, {.minSpeed = 80});
  chassis.moveToPoint(-47.75, -61, 1000, {.maxSpeed = 80});

  // drop off mogo
  chassis.turnToPoint(-61, -62, 1000, {.forwards = false , .minSpeed = 80});
  chassis.moveToPoint(-61, -62, 1100, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.retract();

  // intake last ring of the L for da wall stake
  chassis.turnToPoint(-23, -47, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(-23, -47, 1000, {.maxSpeed = 80});
  lift.setTarget(20);

  pros::Task task = pros::Task{[=] {
    int start = pros::millis();
    while (!color.seesRed() && pros::millis() - start < 1500) { pros::delay(10); }
    intake.arm_loading = true;
  }};

  // move to new mogo to clamp
  chassis.turnToPoint(-47, -22.5, 1500, {.forwards = false, .minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(-47, -22.5, 2000, {.forwards = false, .maxSpeed = 60});
  pros::delay(300);
  chassis.waitUntilDone();
  clamp.extend();

  // move to wall stake
  chassis.turnToPoint(-1, -44, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(-1, -44, 1500, {.maxSpeed = 100});
  chassis.waitUntil(12);
  lift.setTarget(75);
  intake.setState(lib::IntakeState::Idle);

  chassis.waitUntil(25);
  intake.setState(lib::IntakeState::In);

  // turn to da wall
  chassis.turnToHeading(180, 1000);
  chassis.waitUntilDone();
  pros::delay(250);
  lib::wallReset(lib::dir::Y_MINUS);
  pros::delay(50);
  
  chassis.moveToPoint(-1, -63.5, 1000, {.maxSpeed = 100});
  chassis.waitUntil(10.5);
  lift.setTarget(175);
  intake.arm_loading = false;
  intake.jam_override = false;
  pros::delay(500);

  // back out
  chassis.moveToPoint(chassis.getPose().x, -48, 1200, {.forwards = false, .maxSpeed = 100});

  // turn to corner
  chassis.turnToPoint(24, -45, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  lift.setTarget(75);
  chassis.moveToPoint(24, -45, 2900, {.minSpeed = 40, .earlyExitRange = 1});
  
  // get corner rings
  chassis.turnToPoint(23, -25, 750, {.maxSpeed = 100});
  chassis.moveToPoint(23, -25, 1000, {.maxSpeed = 100});
  chassis.turnToPoint(45, -45, 750, {.maxSpeed = 100});
  chassis.moveToPoint(45, -45, 1000, {.maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 5});
  chassis.moveToPoint(62, -45, 500, {.maxSpeed = 100});

  // back out
  chassis.moveToPoint(29.5, -56, 1000, {.forwards = false});

  // sweep out corner
  chassis.moveToPoint(65, -65, 1000);
  doinker.extend();

  chassis.turnToPoint(0, 0, 1500);
  chassis.moveToPoint(80, -80, 1000, {.forwards = false});

  chassis.waitUntilDone();

  // drop mogo
  clamp.retract();
  doinker.retract();
  pros::delay(300);

  // hang
  chassis.moveToPoint(30, -30, 1000);
  intake.setState(lib::IntakeState::Idle);
  chassis.moveToPoint(2, -2, 2400, {.forwards = false, .maxSpeed = 75});
  pros::delay(750);
  wheelsUpPiston.extend();
};
