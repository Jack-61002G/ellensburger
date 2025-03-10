#pragma once
#include "lib/TaskWrapper.hpp"
#include "lib/StateMachine.hpp"
#include "color.hpp"
#include "pros/motor_group.hpp"



namespace lib {



enum class Jam { Reverse, Tap, None };



class Intake : public ryan::TaskWrapper {

private:
  std::shared_ptr<pros::MotorGroup> motors;
  std::shared_ptr<lib::Color> color;
  
  
public:
  int8_t direction = 0;
  bool sortEnabled = true;
  Jam jamMode = Jam::Reverse;

  uint jamStartTime = 0;
  bool ringSeated = false;
  bool sortPrimed = false;


  Intake(pros::MotorGroup *motors, lib::Color *color) : motors(motors), color(color) {}

  void loop() override;
        
  void setDirection(int8_t dir) {
    if (direction != dir) {
      jamStartTime = 0; ringSeated = false; sortPrimed = false;
      direction = dir;
    }
  }
  void setJamMode(Jam jam) {
    if (jamMode != jam) {
      jamStartTime = 0; ringSeated = false;
      jamMode = jam;
    }
  }
  void setSortEnabled(bool sort) {
    if (sortEnabled != sort) {
      jamStartTime = 0; ringSeated = false; sortPrimed = false;
      sortEnabled = sort;
    }
  }
  void setState(int8_t dir, bool sort, Jam jam) {
    if (direction != dir || sortEnabled != sort || jamMode != jam) {
      jamStartTime = 0; ringSeated = false; sortPrimed = false;
      direction = dir; sortEnabled = sort; jamMode = jam;;
    }
  }
};
}