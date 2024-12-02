#pragma once
#include "lemlib/api.hpp"
#include "lemlib/asset.hpp"
#include "main.h"
#include "lib/intake.hpp"
#include "lib/lights.hpp"
#include "lib/lift.hpp"
#include "pros/adi.hpp"

inline bool armLoading = false;
enum class team {red, blue, none};
inline team teamColor = team::none;

// controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
inline pros::MotorGroup leftMotors({-2, -19, 18},
                            pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
inline pros::MotorGroup rightMotors({3, -1, 9}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

// Inertial Sensor on port 10
inline pros::Imu imu(4);

// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
inline pros::Rotation verticalEnc(8);
inline EmaFilter filter(.875);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
inline lemlib::TrackingWheel vertical(&verticalEnc, &filter, lemlib::Omniwheel::NEW_2, 0);

// drivetrain settings
inline lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              12, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              8 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
inline lemlib::ControllerSettings linearController(8, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            7, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            250, // small error range timeout, in milliseconds
                                            2, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
inline lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
inline lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
inline lemlib::ExpoDriveCurve throttleCurve(0, // joystick deadband out of 127
                                     0, // minimum output where drivetrain will move out of 127
                                     1.0005 // expo curve gain
);

// input curve for steer input during driver control
inline lemlib::ExpoDriveCurve steerCurve(0, // joystick deadband out of 127
                                  0, // minimum output where drivetrain will move out of 127
                                  1.0005 // expo curve gain
);

// create the chassis
inline lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);


inline pros::Optical color(13);
inline pros::MotorGroup intakeMotor({15});
inline pros::adi::Pneumatics sorter('F', false);
inline lib::Intake intake(&intakeMotor, &color, &sorter);

inline pros::MotorGroup armMotors({11, -17});
inline lib::Lift lift(&armMotors, 12.0 / 36, {2.5, 0, 1.75});

inline pros::adi::Pneumatics doinker('H', false);
inline pros::adi::Pneumatics clamp('D', false);
inline pros::adi::Pneumatics rushClamp('C', false);

inline lib::Lights lights = lib::Lights();

ASSET(example_txt)