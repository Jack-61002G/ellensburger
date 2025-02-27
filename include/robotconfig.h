#pragma once
#include "lemlib/api.hpp"
#include "lemlib/asset.hpp"
#include "main.h"
#include "lib/color.hpp"
#include "lib/intake.hpp"
#include "lib/lights.hpp"
#include "lib/lift.hpp"
#include "pros/abstract_motor.hpp"
#include "robodash/api.h"
#include "pros/adi.hpp"
#include "pros/optical.h"
#include "pros/rotation.hpp"
#include "robodash/views/selector.hpp"

enum class team {red, blue, none};
inline team teamColor = team::none;
inline std::optional<rd::Selector::routine_t> current_auto;
inline bool liftButtonHeld = false;

// controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
inline pros::MotorGroup leftMotors({-11, -13, -15}, pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
inline pros::MotorGroup rightMotors({18, 19, 20}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

// Inertial Sensor on port 10
inline pros::Imu imu(17);

inline pros::Distance dist = pros::Distance(3);

// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
inline pros::Rotation horizontal(-7);
inline EmaFilter filter(.9);

inline pros::Rotation vertical(-14);
inline EmaFilter filter2(.9);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
inline lemlib::TrackingWheel verticalwheel(&vertical, &filter2, 2.015, 0);
inline lemlib::TrackingWheel horizontalwheel(&horizontal, &filter, 2.028, 0.138);

// drivetrain settings
inline lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              12, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
inline lemlib::ControllerSettings linearController(6.125, // proportional gain (kP)
                                            0.01, // integral gain (kI)
                                            1, // derivative gain (kD)
                                            3, // anti windup
                                            .5, // small error range, in inches
                                            35, // small error range timeout, in milliseconds
                                            1.5, // large error range, in inches
                                            160, // large error range timeout, in milliseconds
                                            7 // maximum acceleration (slew)
);

// angular motion controller
inline lemlib::ControllerSettings angularController(4.7, // proportional gain (kP)
                                             0.01, // integral gain (kI)
                                             48, // derivative gain (kD)
                                             3, // anti windup
                                             2, // small error range, in degrees
                                             35, // small error range timeout, in milliseconds
                                             5, // large error range, in degrees
                                             100, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
inline lemlib::OdomSensors sensors(&verticalwheel, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontalwheel, // horizontal tracking wheel
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


inline lib::Color color = lib::Color();

inline pros::MotorGroup intakeMotor({-8});
inline pros::adi::Pneumatics pisstake('G', false);
inline lib::Intake intake(&intakeMotor, &color);

inline pros::MotorGroup armMotors({2, 21}, pros::v5::MotorGears::red);
inline pros::Rotation armrot(6);

inline lib::Lift lift = lib::Lift();

inline pros::adi::Pneumatics doinker('C', false);
inline pros::adi::Pneumatics clamp('B', false);
inline pros::adi::Pneumatics wheelsUpPiston('A', false);

inline lib::Lights lights = lib::Lights();