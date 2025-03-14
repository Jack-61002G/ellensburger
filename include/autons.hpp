#include "lib/intake.hpp"
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
  chassis.moveToPoint(-59, 9.5, 450);
  lift.setTarget(220);
  chassis.waitUntilDone();
  
  // clamp goal
  pros::delay(500);
  chassis.moveToPoint(-48, 24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 11});
  chassis.moveToPoint(-22, 24, 1000, {.forwards = false, .maxSpeed = 80, .minSpeed = 20, .earlyExitRange = 5});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();
  
  // first ring
  pros::delay(250);
  chassis.turnToPoint(-24, 48, 750, {.minSpeed = 50, .earlyExitRange = 3.5});
  chassis.moveToPoint(-24, 48, 1000, {.maxSpeed = 100});
  intake.setDirection(lib::Dir::In);

  // quad stack
  chassis.waitUntilDone();
  pros::delay(250);
  chassis.turnToPoint(-6.2, 52, 750, {.minSpeed = 50, .earlyExitRange = 6});
  chassis.moveToPoint(-6.2, 52, 1000, {.maxSpeed = 90});

  // back out
  chassis.waitUntilDone();
  pros::delay(300);
  chassis.moveToPoint(-24, 50, 1000, {.forwards = false, .maxSpeed = 100, .minSpeed = 30, .earlyExitRange = 2});

  chassis.turnToPoint(-47, 4, 750);
  chassis.moveToPoint(-47, 4, 1200, {.maxSpeed = 100, .minSpeed = 30, .earlyExitRange = 3});
  pisstake.extend();

  chassis.waitUntilDone();
  pisstake.retract();
  clamp.retract();
  intake.setJamMode(lib::Jam::None);

  chassis.moveToPoint(-48, -6, 1000, {.maxSpeed = 75});

  int start = pros::millis();
  while (!color.seesRed() && pros::millis() - start < 1300) { pros::delay(50); }

  intake.setState(lib::Dir::Idle, lib::Jam::Reverse, true);
  chassis.turnToPoint(-24, -24, 1000, {.forwards = false});
  chassis.moveToPoint(-23.5, -24.5, 1000, {.forwards = false, .maxSpeed = 85});
  chassis.waitUntil(23);
  clamp.extend();

  chassis.waitUntilDone();
  intake.setDirection(lib::Dir::In);
  pros::delay(250);
  chassis.turnToPoint(-24, -52, 1000, {.minSpeed = 40, .earlyExitRange = 4});
  chassis.moveToPoint(-24, -52, 1000, {.maxSpeed = 75});

  chassis.waitUntilDone();
  pros::delay(250);

  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 40, .earlyExitRange = 6});
  pros::delay(250);
  lift.setTarget(45);
  chassis.moveToPoint(-6, -6, 500);
  intake.setDirection(lib::Dir::Idle);
}



inline void blueSoloAWP() {
  chassis.setPose(56, 12.5, 135);

  // score on alliance stake
  chassis.moveToPoint(59, 9.5, 450);
  lift.setTarget(220);
  chassis.waitUntilDone();
  
  // clamp goal
  pros::delay(500);
  chassis.moveToPoint(48, 24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 11});
  chassis.moveToPoint(22, 24, 1000, {.forwards = false, .maxSpeed = 80, .minSpeed = 20, .earlyExitRange = 5});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();
  
  // first ring
  pros::delay(250);
  chassis.turnToPoint(24, 48, 750, {.minSpeed = 50, .earlyExitRange = 3.5});
  chassis.moveToPoint(24, 48, 1000, {.maxSpeed = 100});
  intake.setDirection(lib::Dir::In);

  // quad stack
  chassis.waitUntilDone();
  pros::delay(250);
  chassis.turnToPoint(6.2, 52, 750, {.minSpeed = 50, .earlyExitRange = 6});
  chassis.moveToPoint(6.2, 52, 1000, {.maxSpeed = 90});

  // back out
  chassis.waitUntilDone();
  pros::delay(300);
  chassis.moveToPoint(24, 50, 1000, {.forwards = false, .maxSpeed = 100, .minSpeed = 30, .earlyExitRange = 2});

  chassis.turnToPoint(47, 4, 750);
  chassis.moveToPoint(47, 4, 1200, {.maxSpeed = 100, .minSpeed = 30, .earlyExitRange = 3});
  pisstake.extend();

  chassis.waitUntilDone();
  pisstake.retract();
  clamp.retract();
  intake.setJamMode(lib::Jam::None);

  chassis.moveToPoint(48, -6, 1000, {.maxSpeed = 75});

  int start = pros::millis();
  while (!color.seesBlue() && pros::millis() - start < 1300) { pros::delay(50); }

  intake.setState(lib::Dir::Idle, lib::Jam::Reverse, true);
  chassis.turnToPoint(24, -24, 1000, {.forwards = false});
  chassis.moveToPoint(23.5, -24.5, 1000, {.forwards = false, .maxSpeed = 85});
  chassis.waitUntil(23);
  clamp.extend();

  chassis.waitUntilDone();
  intake.setDirection(lib::Dir::In);
  pros::delay(250);
  chassis.turnToPoint(24, -52, 1000, {.minSpeed = 40, .earlyExitRange = 4});
  chassis.moveToPoint(24, -52, 1000, {.maxSpeed = 75});

  chassis.waitUntilDone();
  pros::delay(250);

  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 40, .earlyExitRange = 6});
  pros::delay(250);
  lift.setTarget(45);
  chassis.moveToPoint(6, -6, 500);
  intake.setDirection(lib::Dir::Idle);
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
  intake.setDirection(lib::Dir::In);

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
  intake.setState(lib::Dir::Out, lib::Jam::None, true);

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setDirection(lib::Dir::In);
  pros::delay(200);

  chassis.moveToPoint(-50, 50, 1000, {.forwards = false});
  chassis.moveToPoint(-68, 67, 1000);

  chassis.moveToPoint(-48, 48, 2000, {.forwards = false, .maxSpeed = 90});

  chassis.turnToPoint(-46.5, 6, 500);
  chassis.moveToPoint(-46.5, 6, 3000, {.maxSpeed = 90, .minSpeed = 30, .earlyExitRange = 2});

  intake.setJamMode(lib::Jam::Reverse);

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
  intake.setDirection(lib::Dir::In);

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
  intake.setState(lib::Dir::Out, lib::Jam::None, true);

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setDirection(lib::Dir::In);
  pros::delay(200);

  chassis.moveToPoint(50, 50, 1000, {.forwards = false});
  chassis.moveToPoint(68, 67, 1000);

  chassis.moveToPoint(48, 48, 2000, {.forwards = false, .maxSpeed = 90});

  chassis.turnToPoint(46.5, 5.5, 500);
  chassis.moveToPoint(46.5, 5.5, 3000, {.maxSpeed = 90, .minSpeed = 30, .earlyExitRange = 2});

  intake.setJamMode(lib::Jam::Reverse);

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

  // clamp goal
  chassis.moveToPoint(-26, -24, 1000, {.forwards = false, .maxSpeed = 75, .minSpeed = 20, .earlyExitRange = 2.5});
  chassis.waitUntilDone();
  clamp.extend();

  // grab center ring
  chassis.turnToPoint(-12, -12, 750, {.minSpeed = 30, .earlyExitRange = 6});
  chassis.moveToPoint(-12, -12, 1000, {.minSpeed = 30, .earlyExitRange = 3});
  chassis.waitUntilDone();
  doinker.extend();

  pros::delay(500);
  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 3});
  chassis.waitUntilDone();
  doinker.retract();

  // gobble up ring
  intake.setDirection(lib::Dir::In);
  chassis.moveToPoint(-10, -16, 1000);

  chassis.moveToPoint(-24, -24, 1000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 2});

  // go to ring stack
  chassis.turnToPoint(-24, -48, 1000, {.minSpeed = 30, .earlyExitRange = 6});
  chassis.moveToPoint(-24, -48, 1000);
  chassis.waitUntilDone();
  pros::delay(750);

  // go to corner
  chassis.turnToPoint(-68, -66, 1000, {.minSpeed = 20, .earlyExitRange = 6});
  chassis.moveToPoint(-68, -66, 1800, {.maxSpeed = 80});

  pros::delay(800);
  intake.setState(lib::Dir::Out, lib::Jam::None, true);

  chassis.waitUntilDone();
  intake.setDirection(lib::Dir::In);
  pros::delay(350);

  chassis.moveToPoint(-50, -50, 1000, {.forwards = false});
  chassis.moveToPoint(-68, -67, 1000);

  pisstake.extend();
  chassis.waitUntilDone();
  pisstake.retract();

  pros::delay(500);
  chassis.moveToPoint(-48, -48, 2000, {.forwards = false, .maxSpeed = 90});
  intake.setJamMode(lib::Jam::Reverse);

  chassis.moveToPoint(-12, -12, 2500, {.maxSpeed = 90});
  lift.setTarget(70);
}



inline void blueGoalSide() {
  chassis.setPose(54, -24, 90);

  // clamp goal
  chassis.moveToPoint(26, -24, 1000, {.forwards = false, .maxSpeed = 75, .minSpeed = 20, .earlyExitRange = 2.5});
  chassis.waitUntilDone();
  clamp.extend();

  // grab center ring
  chassis.turnToPoint(15, -7, 750, {.minSpeed = 30, .earlyExitRange = 6});
  chassis.moveToPoint(7, -15, 1000, {.minSpeed = 30, .earlyExitRange = 3});
  chassis.waitUntilDone();
  doinker.extend();

  pros::delay(500);
  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 3});
  chassis.waitUntilDone();
  doinker.retract();

  // gobble up ring
  intake.setDirection(lib::Dir::In);
  chassis.moveToPoint(16, -10, 1000);

  chassis.moveToPoint(24, -24, 1000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 2});

  // go to ring stack
  chassis.turnToPoint(24, -48, 1000, {.minSpeed = 30, .earlyExitRange = 6});
  chassis.moveToPoint(24, -48, 1000);
  chassis.waitUntilDone();
  pros::delay(750);

  // go to corner
  chassis.turnToPoint(68, -66, 1000, {.minSpeed = 20, .earlyExitRange = 6});
  chassis.moveToPoint(68, -66, 1800, {.maxSpeed = 80});

  pros::delay(800);
  intake.setState(lib::Dir::Out, lib::Jam::None, true);

  chassis.waitUntilDone();
  intake.setDirection(lib::Dir::In);
  pros::delay(350);

  chassis.moveToPoint(50, -50, 1000, {.forwards = false});
  chassis.moveToPoint(68, -67, 1000);

  pisstake.extend();
  chassis.waitUntilDone();
  pisstake.retract();

  pros::delay(600);
  chassis.moveToPoint(48, -48, 2000, {.forwards = false, .maxSpeed = 90});
  intake.setJamMode(lib::Jam::Reverse);

  chassis.turnToPoint(10, -10, 1000);
  chassis.moveToPoint(10, -10, 2500, {.maxSpeed = 90});
  lift.setTarget(70);
}



inline void redMogoRush() {
  chassis.setPose(-55.5, -48, 90);

  chassis.moveToPoint(-15.5, -48, 2000);
  lift.setTarget(150);
  intake.setDirection(lib::Dir::In);
  pisstake.retract();
  intake.setSortMode(false);

  pros::Task ring = pros::Task{[=] {
    while (!color.seesRed()) {
      pros::delay(15);
    }
    intake.setDirection(lib::Dir::Idle);
  }};

  chassis.waitUntil(38);
  lift.setTarget(230);
  intake.setSortMode(true);

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
  intake.setDirection(lib::Dir::In);
  pros::delay(1300);

  chassis.turnToPoint(-57, -57, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-57, -57, 2000, {.maxSpeed = 100});

  chassis.waitUntilDone();
  pros::delay(250);
  intake.setDirection(lib::Dir::Idle);

  chassis.moveToPoint(-72, -70, 1000, {.maxSpeed = 90});

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setDirection(lib::Dir::In);
  pros::delay(400);
  intake.setJamMode(lib::Jam::None);
  pros::delay(400);

  chassis.moveToPoint(-45, -45, 2000, {.forwards = false, .maxSpeed = 40});

  chassis.turnToPoint(-14, -14, 1000, {.maxSpeed = 60});
  intake.setJamMode(lib::Jam::Reverse);
  chassis.moveToPoint(-14, -14, 2500, {.maxSpeed = 60});
  lift.setTarget(135);
  chassis.waitUntilDone();
  intake.setDirection(lib::Dir::Idle);
}



inline void blueMogoRush() {
  chassis.setPose(55.5, -48, -90);

  chassis.moveToPoint(15.5, -48, 2000);
  lift.setTarget(150);
  intake.setDirection(lib::Dir::In);
  pisstake.retract();
  intake.setSortMode(false);

  pros::Task ring = pros::Task{[=] {
    while (!color.seesBlue()) {
      pros::delay(15);
    }
    intake.setDirection(lib::Dir::Idle);
  }};

  chassis.waitUntil(38);
  lift.setTarget(230);
  intake.setSortMode(true);

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
  intake.setDirection(lib::Dir::In);
  pros::delay(1300);

  chassis.turnToPoint(57, -57, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(57, -57, 2000, {.maxSpeed = 100});

  chassis.waitUntilDone();
  pros::delay(250);
  intake.setDirection(lib::Dir::Idle);

  chassis.moveToPoint(72, -70, 1000, {.maxSpeed = 90});

  chassis.waitUntilDone();
  pros::delay(200);
  intake.setDirection(lib::Dir::In);
  pros::delay(400);
  intake.setJamMode(lib::Jam::None);
  pros::delay(400);

  chassis.moveToPoint(45, -45, 2000, {.forwards = false, .maxSpeed = 40});

  chassis.turnToPoint(14, -14, 1000, {.maxSpeed = 60});
  intake.setJamMode(lib::Jam::Reverse);
  chassis.moveToPoint(14, -14, 2500, {.maxSpeed = 60});
  lift.setTarget(135);
  chassis.waitUntilDone();
  intake.setDirection(lib::Dir::Idle);
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
  chassis.waitUntil(18);
  clamp.extend();
  pros::delay(200);

  // ring 1
  chassis.turnToPoint(-25, 24, 1000, {.minSpeed = 80});
  intake.setDirection(lib::Dir::In);
  chassis.moveToPoint(-25, 24, 1000);

  // second ring
  chassis.turnToPoint(24.5, 50, 1000, {.minSpeed = 80});
  chassis.moveToPoint(24.5, 50, 1500);
  chassis.waitUntil(20);
  lift.setTarget(19.5);
  intake.setJamMode(lib::Jam::Tap);

  // move to wall stake
  pros::delay(600);
  chassis.moveToPoint(-1, 41, 1000, {.forwards = false, .maxSpeed = 100});

  pros::delay(800);
  intake.setDirection(lib::Dir::Idle);
  lift.setTarget(75);

  pros::delay(300);
  intake.setDirection(lib::Dir::In);

  // score on wall
  chassis.turnToPoint(-1, 64, 1000);
  chassis.moveToPoint(-1, 64, 1000);
  chassis.waitUntil(12.75);
  lift.setTarget(175);
  intake.setJamMode(lib::Jam::Reverse);
  pros::delay(600);

  // back up and go to fill up mogo in left corner
  chassis.moveToPoint(-3, 46, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToPoint(-24, 48, 1000, {.minSpeed = 80});
  lift.setTarget(75);

  // long intake
  chassis.moveToPoint(-60, 47.5, 3000, {.maxSpeed = 70});
  intake.setDirection(lib::Dir::In);

  // last guy before mogo drop
  chassis.waitUntilDone();
  pros::delay(50);
  chassis.turnToPoint(-48, 60, 1000, {.maxSpeed = 59});
  chassis.moveToPoint(-48, 60, 1000, {.maxSpeed = 80});

  // back into corner
  chassis.turnToPoint(-61, 63, 1000, {.forwards = false, .maxSpeed = 65});
  chassis.moveToPoint(-61, 63, 800, {.forwards = false});

  // cross to blue corner
  chassis.turnToPoint(41, 46, 1000, {.minSpeed = 80, .earlyExitRange = 4});
  pros::delay(150);
  clamp.retract();
  chassis.moveToPoint(41, 46, 5000, {.maxSpeed = 110});

  // get ready to hold ring from blue corner 
  lift.setTarget(19.5);
  intake.setJamMode(lib::Jam::Tap);
  pros::delay(1000);
  doinker.extend();

  chassis.waitUntilDone();
  pros::delay(50);
  chassis.turnToHeading(0, 1500);
  chassis.waitUntilDone();
  pros::delay(200);
  lib::wallReset(lib::dir::Y_PLUS);
  pros::delay(25);

  // grab blue goal
  chassis.turnToPoint(56.5, 21, 1000, {.forwards = false, .minSpeed = 80});

  chassis.moveToPoint(56.5, 21, 2200, {.forwards = false, .maxSpeed = 80});

  intake.setDirection(lib::Dir::Idle);
  lift.setTarget(75);
  pros::delay(350);
  intake.setDirection(lib::Dir::Out);
  doinker.retract();

  chassis.waitUntilDone();
  clamp.extend();
  
  // shove goal into corner
  chassis.turnToPoint(66, 64, 1000, {.minSpeed = 90});
  pros::delay(250);
  doinker.extend();
  chassis.moveToPoint(66, 64, 1200, {.maxSpeed = 90});

  chassis.turnToPoint(0, 0, 1500, {.minSpeed = 90});
  pros::delay(300);
  doinker.retract();
  chassis.moveToPoint(75, 75, 700, {.forwards = false});
  clamp.retract();
  doinker.retract();
  pros::delay(250);

  // back up and clamp empty goal
  chassis.moveToPoint(48, 48, 500);
  chassis.turnToPoint(48, -3.75, 1000 ,{.forwards = false, .minSpeed = 50, .earlyExitRange = 5});
  chassis.moveToPoint(48, -3.75, 2000, {.forwards = false, .maxSpeed = 75});
  chassis.waitUntil(42);
  clamp.extend();

  // wall reset
  chassis.turnToHeading(90, 1500);
  chassis.waitUntilDone();
  pros::delay(150);
  lib::wallReset(lib::dir::X_PLUS);
  intake.setDirection(lib::Dir::Idle);

  // turn to the alliance stake and score on it
  chassis.moveToPoint(73, chassis.getPose().y, 1000, {.maxSpeed = 80});
  chassis.waitUntilDone();
  pros::delay(150);

  chassis.tank(-65, -65);
  lift.setTarget(220);
  pros::delay(170);
  chassis.tank(0, 0);
  pros::delay(350);

  intake.setJamMode(lib::Jam::Reverse);
  chassis.moveToPoint(48, 0, 750, {.forwards = false, .minSpeed = 80});

  chassis.turnToPoint(26, 23, 1000, {.minSpeed = 50, .earlyExitRange = 5});
  lift.setTarget(0);
  intake.setDirection(lib::Dir::In);
  chassis.moveToPoint(26, 23.75, 1100, {.maxSpeed = 100});
  chassis.waitUntilDone();
  pros::delay(700);

  // cross under ladder
  chassis.turnToPoint(-23, -24, 1000, {.maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 5});
  chassis.moveToPoint(-23, -24, 3000, {.minSpeed = 40, .earlyExitRange = 6});
  intake.setDirection(lib::Dir::Idle);
  chassis.waitUntil(45.5);
  intake.setDirection(lib::Dir::In);
  chassis.moveToPoint(-42, -46, 2000, {.maxSpeed = 80});

  chassis.waitUntilDone();
  pros::delay(100);
  chassis.turnToHeading(-90, 1500, {.maxSpeed = 90});
  chassis.waitUntilDone();

  pros::delay(150);
  lib::wallReset(lib::dir::X_MINUS);


  // turn to face the driver box and intake the ring
  chassis.moveToPoint(-60, -48, 1000, {.maxSpeed = 90});

  chassis.turnToHeading(180, 1750, {.maxSpeed = 60});
  chassis.waitUntilDone();

  pros::delay(150);
  lib::wallReset(lib::dir::Y_MINUS);

  // grab last of the angle rings
  chassis.turnToPoint(-47.75, -60, 1000, {.maxSpeed = 60});
  chassis.moveToPoint(-47.75, -60, 1000, {.maxSpeed = 80});

  // drop off mogo
  chassis.turnToPoint(-61, -61, 1000, {.forwards = false, .maxSpeed = 65, .minSpeed = 80});
  chassis.moveToPoint(-61, -61, 900, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.retract();

  // intake last ring of the L for da wall stake
  chassis.turnToPoint(-24.5, -42.25, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(-24.5, -42.25, 1000, {.maxSpeed = 80});
  lift.setTarget(20);

  pros::Task task = pros::Task{[=] {
    int start = pros::millis();
    while (!color.seesRed() && pros::millis() - start < 1500) { pros::delay(10); }
    intake.setJamMode(lib::Jam::Tap);
  }};

  // move to new mogo to clamp
  chassis.turnToPoint(-46.75, -21.5, 1500, {.forwards = false, .minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(-46.75, -21.5, 2000, {.forwards = false, .maxSpeed = 60});
  pros::delay(300);
  chassis.waitUntilDone();
  clamp.extend();

  // move to wall stake
  chassis.turnToPoint(0, -40, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(0, -40, 1500, {.maxSpeed = 100});
  

  // turn to da wall
  chassis.turnToHeading(180, 1000);
  chassis.waitUntilDone();
  lift.setTarget(75);
  intake.setDirection(lib::Dir::Idle);
  pros::delay(150);
  lib::wallReset(lib::dir::Y_MINUS);
  intake.setDirection(lib::Dir::In);
  
  chassis.moveToPoint(0, -63.5, 1000, {.maxSpeed = 100});
  chassis.waitUntil(10.5);
  lift.setTarget(175);
  intake.setJamMode(lib::Jam::Reverse);
  pros::delay(500);

  // back out
  chassis.moveToPoint(chassis.getPose().x, -44, 1200, {.forwards = false, .maxSpeed = 100});

  // turn to corner
  chassis.turnToPoint(24, -45, 1000, { .maxSpeed = 70, .minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(24, -45, 2900, {.minSpeed = 40, .earlyExitRange = 1});
  lift.setTarget(75);
  
  // get corner rings
  chassis.turnToPoint(23, -25, 750, {.maxSpeed = 60});
  chassis.moveToPoint(23, -25, 1000, {.maxSpeed = 100});
  chassis.turnToPoint(45, -45, 750, {.maxSpeed = 60});
  chassis.moveToPoint(45, -45, 1000, {.maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 5});
  chassis.moveToPoint(62, -45, 500, {.maxSpeed = 100});

  // back out
  chassis.moveToPoint(28.25, -56, 1000, {.forwards = false});

  // sweep out corner
  chassis.moveToPoint(65, -64, 1000);
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
  intake.setDirection(lib::Dir::Idle);
  chassis.moveToPoint(2, 0, 2000, {.forwards = false, .maxSpeed = 75});
  pros::delay(800);
  wheelsUpPiston.extend();
};
