#pragma once
#include "lib/TaskWrapper.hpp"
#include "color.hpp"
#include "pros/motor_group.hpp"



namespace lib {



enum class Dir { In, Out, Idle };
enum class Jam { Reverse, Tap, None };



class Intake : public ryan::TaskWrapper {

private:
  std::shared_ptr<pros::MotorGroup> motors;
  std::shared_ptr<lib::Color> color;

  uint jamStartTime = 0;
  bool ringSeated = false;
  bool sortPrimed = false;
  
  
public:
  int8_t target_v = 0;
  Jam jamMode = Jam::Reverse;
  bool sortEnabled = false;


  Intake(pros::MotorGroup *motors, lib::Color *color) : motors(motors), color(color) {}


  void loop() override;
        
  
  void setDirection(Dir dir) {
    int8_t volts = (dir == Dir::In) ? 127 : (dir == Dir::Out) ? -127 : 0;
    if (target_v != volts) {
      jamStartTime = 0; ringSeated = false; sortPrimed = false;
      target_v = volts;
    }
  }
  void setJamMode(Jam jam) {
    if (jamMode != jam) {
      jamStartTime = 0; ringSeated = false;
      jamMode = jam;
    }
  }
  void setSortMode(bool sort) {
    if (sortEnabled != sort) {
      jamStartTime = 0; ringSeated = false; sortPrimed = false;
      sortEnabled = sort;
    }
  }
  void setState(Dir dir, Jam jam, bool sort) {
    int8_t volts = (dir == Dir::In) ? 127 : (dir == Dir::Out) ? -127 : 0;
    if (target_v != volts || sortEnabled != sort || jamMode != jam) {
      jamStartTime = 0; ringSeated = false; sortPrimed = false;
      target_v = volts; sortEnabled = sort; jamMode = jam;;
    }
  }
};
}