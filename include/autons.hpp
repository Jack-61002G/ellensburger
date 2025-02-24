#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "lib/intake.hpp"
#include "pros/distance.hpp"
#include "robodash/views/console.hpp"
#include "robotconfig.h"
#include "lib/reset.hpp"
#include <functional>
#include <string>

ASSET(mogo1_txt)
ASSET(wall1_txt)
ASSET(mogo3_txt)
ASSET(mogo2_txt)
ASSET(mogo3rings_txt)
ASSET(mogo3ring_txt)
ASSET(mogo4rush_txt)
ASSET(nyoooom_txt)



inline void redRingSide() {
  chassis.setPose(-56, 12.5, -135);

  // score on alliance stake
  chassis.moveToPoint(-59, 9.5, 470);
  lift.setTarget(220);
  chassis.waitUntilDone();
  
  // clamp goal
  pros::delay(500);
  chassis.moveToPoint(-48, 24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 11});
  chassis.moveToPoint(-23, 24, 1000, {.forwards = false, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 4});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  pros::delay(250);
  chassis.moveToPoint(-6.2, 32.5, 1200, {.maxSpeed = 80});

  // intake quad stack
  chassis.turnToPoint(-6, 60, 1000, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-6, 60, 1500, {.maxSpeed = 90});

  chassis.waitUntilDone();
  pros::delay(200);

  chassis.swingToHeading(18, lemlib::DriveSide::LEFT, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(-15.5, 26, 500, {.forwards = false, .maxSpeed = 90});
  
  chassis.turnToPoint(-28, 50, 1000);
  chassis.moveToPoint(-28, 50, 1000, {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 2});

  // intake corner stack
  chassis.waitUntilDone();
  pros::delay(200);
  chassis.moveToPoint(-70, 70, 1500, {.maxSpeed = 100});

  pros::delay(950);
  intake.setState(lib::IntakeState::Out);
  chassis.waitUntilDone();
  pros::delay(100);
  intake.setState(lib::IntakeState::In);
  intake.jam_override = true;
  pros::delay(50);

  chassis.moveToPoint(-48, 48, 2000, {.forwards = false, .maxSpeed = 60});

  chassis.turnToPoint(-46.5, 7.1, 500, {.maxSpeed = 70});
  chassis.moveToPoint(-46.5, 7.1, 3000, {.maxSpeed = 70});

  pisstake.extend();
  chassis.waitUntilDone();
  pisstake.retract();
  pros::delay(500);

  chassis.moveToPoint(-46, 10, 400, {.forwards = false});
  chassis.moveToPoint(-67, -75, 1500);
}



inline void blueRingSide() {
  chassis.setPose(56, 12.5, 135);

  // score on alliance stake
  chassis.moveToPoint(59, 9.5, 480);
  lift.setTarget(220);
  chassis.waitUntilDone();
  
  // clamp goal
  pros::delay(500);
  chassis.moveToPoint(48, 24, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 11});
  chassis.moveToPoint(23, 24, 1000, {.forwards = false, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 4});
  lift.setTarget(75);

  chassis.waitUntilDone();
  clamp.extend();

  pros::delay(250);
  chassis.moveToPoint(7.2, 35, 1200, {.maxSpeed = 80});

  // intake quad stack
  chassis.turnToPoint(7, 60, 1000, {.maxSpeed = 90});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(7, 60, 1600, {.maxSpeed = 90});

  chassis.waitUntilDone();
  pros::delay(200);

  chassis.swingToHeading(-18, lemlib::DriveSide::RIGHT, 1000, {.maxSpeed = 90});
  chassis.moveToPoint(15.5, 26, 500, {.forwards = false, .maxSpeed = 90});
  
  chassis.turnToPoint(28.2, 52, 1000);
  chassis.moveToPoint(28.2, 52, 1000, {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 6});

  // intake corner stack
  chassis.waitUntilDone();
  pros::delay(200);
  chassis.moveToPoint(70, 68, 1500, {.maxSpeed = 100});

  pros::delay(950);
  intake.setState(lib::IntakeState::Out);
  chassis.waitUntilDone();
  pros::delay(100);
  intake.setState(lib::IntakeState::In);
  intake.jam_override = true;
  pros::delay(50);

  chassis.moveToPoint(48, 48, 2000, {.forwards = false, .maxSpeed = 60});

  chassis.turnToPoint(45, 6.5, 500, {.maxSpeed = 70});
  chassis.moveToPoint(45, 6.5, 3000, {.maxSpeed = 70});

  pisstake.extend();
  chassis.waitUntilDone();
  pisstake.retract();
  pros::delay(500);

  lift.setTarget(205);
  chassis.turnToPoint(27, 2, 500);
  chassis.moveToPoint(27, 2, 1000, {.maxSpeed = 80});
}



inline void redMogoRush() {
  chassis.setPose(-55.5, -48, 90);

  chassis.moveToPoint(-15.5, -48, 2000);
  lift.setTarget(150);
  intake.setState(lib::IntakeState::In);
  pisstake.retract();
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
    while (!((color.get_hue() > 180 && color.get_hue() < 330) && color.get_proximity() > 200)) {
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
  chassis.moveToPoint(-47.75, 24, 3000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntil(18);
  clamp.extend();
  pros::delay(200);

  // ring 1
  chassis.turnToPoint(-25, 24, 1000, {.minSpeed = 80});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-25, 24, 1000);

  // second ring
  chassis.turnToPoint(25, 49, 1000, {.minSpeed = 80});
  chassis.moveToPoint(25, 49, 1500);
  chassis.waitUntil(24);
  lift.setTarget(25);
  intake.jam_override = true;

  // move to wall stake
  pros::delay(600);
  chassis.moveToPoint(-1, 42, 1000, {.forwards = false, .maxSpeed = 100});

  pros::delay(500);
  intake.setState(lib::IntakeState::Idle);
  lift.setTarget(75);
  intake.jam_override = false;

  pros::delay(300);
  intake.setState(lib::IntakeState::In);

  // score on wall
  chassis.turnToPoint(-1, 65, 1000);
  chassis.moveToPoint(-1, 65, 1000);
  chassis.waitUntil(12.25);
  lift.setTarget(175);
  pros::delay(500);

  // back up and go to fill up mogo in left corner
  chassis.moveToPoint(-3, 47, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToPoint(-24, 48, 1000, {.minSpeed = 80});
  lift.setTarget(75);

  // long intake
  chassis.moveToPoint(-60, 48, 3000, {.maxSpeed = 64});
  intake.setState(lib::IntakeState::In);

  // last guy before mogo drop
  chassis.waitUntilDone();
  pros::delay(75);
  chassis.turnToPoint(-48, 60, 1000, {.minSpeed = 65});
  chassis.moveToPoint(-48, 60, 1000, {.maxSpeed = 80});

  // drop the mogo
  chassis.turnToPoint(-61, 63, 1000, {.forwards = false, .maxSpeed = 70});
  chassis.moveToPoint(-61, 63, 1000, {.forwards = false});
  clamp.retract();

  // cross to blue corner
  chassis.turnToPoint(41, 46, 1000, {.minSpeed = 80});
  chassis.moveToPoint(41, 46, 5000, {.maxSpeed = 110});

  // get ready to hold ring from blue corner 
  lift.setTarget(25);
  intake.jam_override = true;

  chassis.waitUntilDone();
  pros::delay(50);
  chassis.turnToHeading(0, 1500);
  chassis.waitUntilDone();
  pros::delay(250);
  lib::wallReset(lib::dir::Y_PLUS);
  pros::delay(50);

  // grab blue goal
  chassis.turnToPoint(56, 24, 1000, {.forwards = false, .minSpeed = 80});
  chassis.moveToPoint(56, 24, 2000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.extend();

  intake.setState(lib::IntakeState::Idle);
  lift.setTarget(75);
  pros::delay(200);
  
  // shove goal into corner
  chassis.turnToPoint(66, 66, 1000, {.minSpeed = 80});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(66, 66, 1900, {.maxSpeed = 80});
  pros::delay(200);

  chassis.turnToPoint(0, 0, 2000, {.minSpeed = 80});
  chassis.moveToPoint(80, 80, 550, {.forwards = false});
  clamp.retract();
  intake.setState(lib::IntakeState::Out);
  pros::delay(500);


  // back up and clamp empty goal
  chassis.moveToPoint(48, 48, 500);
  chassis.turnToPoint(48, -2, 1000 ,{.forwards = false, .minSpeed = 80});
  chassis.moveToPoint(48, -2, 2000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.extend();
  pros::delay(200);

  // wall reset
  chassis.turnToHeading(90, 1500);
  chassis.waitUntilDone();
  pros::delay(250);
  lib::wallReset(lib::dir::X_PLUS);
  pros::delay(50);
  intake.setState(lib::IntakeState::Idle);

  // turn to the alliance stake and score on it
  chassis.moveToPoint(56.05, -1.75, 750, {.maxSpeed = 100});
  chassis.waitUntilDone();
  lift.setTarget(250);
  pros::delay(500);

  chassis.moveToPoint(46.5, 0, 1000, {.forwards = false, .minSpeed = 80});

  chassis.turnToPoint(26, 24, 1000, {.minSpeed = 80});
  lift.setTarget(2);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(26, 24, 1100, {.maxSpeed = 100});
  chassis.waitUntilDone();
  pros::delay(750);
  intake.setState(lib::IntakeState::Idle);

  chassis.turnToPoint(-23, -24, 1000, {.minSpeed = 80});
  chassis.moveToPoint(-23, -24, 3000, {.maxSpeed = 90, .earlyExitRange = 6});
  chassis.waitUntil(45);
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(-44, -44, 2000, {.maxSpeed = 65});

  chassis.turnToHeading(-90, 1500);
  chassis.waitUntilDone();

  pros::delay(250);
  lib::wallReset(lib::dir::X_MINUS);
  pros::delay(50);

  // turn to face the driver box and intake the ring
  chassis.moveToPoint(-60, -47, 1000, {.maxSpeed = 80});

  chassis.turnToHeading(180, 1500);
  chassis.waitUntilDone();

  pros::delay(250);
  lib::wallReset(lib::dir::Y_MINUS);
  pros::delay(50);


  // grab last of the angle rings
  chassis.turnToPoint(-47.75, -61, 1000, {.minSpeed = 80});
  chassis.moveToPoint(-47.75, -61, 1000, {.maxSpeed = 80});

  // drop off mogo
  chassis.turnToPoint(-61, -67, 1000, {.forwards = false , .minSpeed = 80});
  chassis.moveToPoint(-61, -67, 1100, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.retract();

  // intake last ring of the L for da wall stake
  chassis.turnToPoint(-24, -48, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(-24, -48, 1000, {.maxSpeed = 80});
  lift.setTarget(30);
  intake.jam_override = false;
  intake.arm_loading = true;

  // move to new mogo to clamp
  chassis.turnToPoint(-48, -24, 1500, {.forwards = false, .minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(-48, -24, 2000, {.forwards = false, .maxSpeed = 60});
  pros::delay(300);
  chassis.waitUntilDone();
  clamp.extend();

  // move to wall stake
  chassis.turnToPoint(-0.5, -47, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(-0.5, -47, 1500, {.maxSpeed = 100});
  chassis.waitUntil(12);
  lift.setTarget(75);
  intake.setState(lib::IntakeState::Idle);

  chassis.waitUntil(25);
  intake.setState(lib::IntakeState::In);

  // turn to da wall
  chassis.turnToPoint(-1.5, -65, 1000, {.maxSpeed = 100});
  chassis.moveToPoint(-1.5, -65, 1000, {.maxSpeed = 100});
  chassis.waitUntil(10.5);
  lift.setTarget(175);
  intake.jam_override = false;
  intake.arm_loading = false;
  pros::delay(500);

  chassis.moveToPoint(0, -48, 1200, {.forwards = false, .maxSpeed = 100});
  chassis.turnToPoint(58, -48, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  lift.setTarget(75);
  chassis.moveToPoint(55, -48, 2900, {.maxSpeed = 90, .earlyExitRange = 1});
  doinker.extend();

  chassis.turnToPoint(70, -70, 1000, {.minSpeed = 80, .earlyExitRange = 10});
  chassis.moveToPoint(70, -70, 600, {.maxSpeed = 100});
  chassis.swingToHeading(-150, lemlib::DriveSide::RIGHT, 1000);

  chassis.turnToHeading(-45, 1000, {.earlyExitRange = 2});
  chassis.moveToPoint(70, -72, 1000, {.forwards = false, .maxSpeed = 100});
  doinker.retract();
  pros::delay(200);
  clamp.retract();
  pros::delay(300);
  chassis.moveToPoint(40, -40, 1000, {.maxSpeed = 100});
  pros::delay(200);
  intake.setState(lib::IntakeState::Idle);
  chassis.moveToPoint(-2, -2, 2400, {.forwards = false, .maxSpeed = 75});
  pros::delay(750);
  wheelsUpPiston.extend();
};

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
  chassis.waitUntil(18.5);
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

  chassis.moveToPoint(2, 49, 1000, {.maxSpeed = 80});
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
  chassis.turnToPoint(48, 5, 1200, {.forwards = false});
  chassis.moveToPoint(48, 5, 1200, {.forwards = false, .maxSpeed = 58});
  chassis.waitUntilDone();
  clamp.extend();
  pros::delay(200);

  chassis.moveToPoint(48, 11, 1000, {.maxSpeed = 100});
  chassis.turnToPoint(26, 31, 1000, {.maxSpeed = 100});
  intake.setState(lib::IntakeState::In);
  chassis.moveToPoint(26, 31, 1100, {.maxSpeed = 100});
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
  chassis.moveToPoint(-58, -36, 1000, {.maxSpeed = 80});

  // grab last of the angle rings
  chassis.turnToPoint(-52, -48, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(-52, -48, 1000, {.maxSpeed = 80});

  // drop off mogo
  chassis.turnToPoint(-68, -58, 1000, {.forwards = false});
  chassis.moveToPoint(-68, -58, 1000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  clamp.retract();

  // intake last ring of the L for da wall stake
  chassis.turnToPoint(-28, -45, 1000);
  chassis.moveToPoint(-28, -45, 1000, {.maxSpeed = 80});
  lift.setTarget(30);

  // move to new mogo to clamp
  chassis.turnToPoint(-58.7, -24.7, 1500, {.forwards = false});
  intake.jam_override = true;
  chassis.moveToPoint(-58.7, -24.7, 2000, {.forwards = false, .maxSpeed = 60});
  pros::delay(300);
  chassis.waitUntilDone();
  clamp.extend();

  chassis.turnToPoint(-11, -53, 1000);
  chassis.moveToPoint(-11, -53, 1500, {.maxSpeed = 100});
  chassis.waitUntil(12);
  lift.setTarget(75);
  intake.setState(lib::IntakeState::Idle);

  chassis.waitUntil(25);
  intake.setState(lib::IntakeState::In);

  // turn to da wall
  chassis.turnToHeading(180, 1000);
  chassis.moveToPoint(chassis.getPose().x, -70, 1000, {.maxSpeed = 100});
  chassis.waitUntil(3);
  lift.setTarget(175);
  intake.jam_override = false;
  pros::delay(500);

  chassis.moveToPoint(chassis.getPose().x, -54, 1000,
                      {.forwards = false, .maxSpeed = 100});
  chassis.turnToPoint(44, -53, 1000);
  lift.setTarget(75);
  chassis.moveToPoint(44, -53, 2000, {.maxSpeed = 90, .earlyExitRange = 1});
  doinker.extend();

  chassis.turnToPoint(60, -70, 1000);
  chassis.moveToPoint(60, -70, 500, {.maxSpeed = 100});
  chassis.swingToHeading(-150, lemlib::DriveSide::RIGHT, 1000);

  chassis.turnToHeading(-45, 1000, {.earlyExitRange = 2});
  chassis.moveToPoint(58, -74, 1000, {.forwards = false, .maxSpeed = 100});
  doinker.retract();
  pros::delay(200);
  clamp.retract();
  pros::delay(300);
  chassis.moveToPoint(36, -48, 1000, {.maxSpeed = 100});
  pros::delay(200);
  intake.setState(lib::IntakeState::Idle);
  chassis.moveToPoint(-2, -4, 2500, {.forwards = false, .maxSpeed = 75});
  pros::delay(750);
  wheelsUpPiston.extend();
};
