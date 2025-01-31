#include "lemlib/pose.hpp"
#include "robotconfig.h"
// ACTUAL WALL POSITIONS (MODIFY THESE)
const double WALL_Y_PLUS = 144.0;   // North wall position
const double WALL_X_PLUS = 144.0;   // East wall position
const double WALL_Y_MINUS = 0.0;    // South wall position
const double WALL_X_MINUS = 0.0;    // West wall position

// SENSOR OFFSETS (MEASURE THESE)
const double SENSOR_FORWARD_OFFSET = 5.0;  // Distance from robot center to sensor in facing direction
const double SENSOR_LATERAL_OFFSET = 3.0;  // Distance from robot center to sensor in side direction

lemlib::Pose quickReset() {
    lemlib::Pose current = chassis.getPose();
    
    // Normalize theta to 0-360 degrees
    double theta = fmod(current.theta, 360.0);
    if (theta < 0) theta += 360.0;

    // Determine wall orientation and calculate effective offset
    double wall_position = 0.0;
    double effective_offset = 0.0;
    bool update_x = false;

    if (theta >= 315 || theta < 45) {       // Facing Y+ wall
        wall_position = WALL_Y_PLUS;
        effective_offset = SENSOR_FORWARD_OFFSET;
    } else if (theta >= 45 && theta < 135) { // Facing X+ wall
        wall_position = WALL_X_PLUS;
        effective_offset = SENSOR_FORWARD_OFFSET;
        update_x = true;
    } else if (theta >= 135 && theta < 225) {// Facing Y- wall
        wall_position = WALL_Y_MINUS;
        effective_offset = -SENSOR_FORWARD_OFFSET;
    } else {                                // Facing X- wall
        wall_position = WALL_X_MINUS;
        effective_offset = -SENSOR_FORWARD_OFFSET;
        update_x = true;
    }

    // Calculate lateral compensation based on heading
    double lateral_compensation = SENSOR_LATERAL_OFFSET * cos(theta * M_PI/180);

    // Sensor data collection
    const short samples = 10;
    double valid_readings = 0;
    double sum = 0.0;

    for (short i = 0; i < samples; i++) {
        double sensor_dist = distSens.get() * 0.0393701; // mm to inches
        
        if (sensor_dist < 1 || sensor_dist > 100) { // Basic error checking
            i--; // Retry invalid sample
            continue;
        }

        // Calculate distance to wall including offsets
        double total_distance = sensor_dist + effective_offset;
        
        // Apply lateral compensation to non-updated axis
        if (update_x) {
            current.y += lateral_compensation;
        } else {
            current.x += lateral_compensation;
        }

        sum += wall_position - total_distance;
        valid_readings++;
        
        pros::delay(20);
    }

    if (valid_readings == 0) return chassis.getPose();

    // Update robot's position
    if (update_x) {
        current.x = sum / valid_readings;
    } else {
        current.y = sum / valid_readings;
    }

    chassis.setPose(current.x, current.y, theta);
    return lemlib::Pose(current.x, current.y, theta);
}