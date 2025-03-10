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
        
  void setDirection(int8_t direction) {
    jamStartTime = 0; ringSeated = false; sortPrimed = false;
    this->direction = direction;
  }
  void setJamMode(Jam jamMode) {
    jamStartTime = 0; ringSeated = false;
    this->jamMode = jamMode;
  }
  void setSortEnabled(bool sortEnabled) {
    jamStartTime = 0; ringSeated = false; sortPrimed = false;
    this->sortEnabled = sortEnabled;
  }
  void setState(int8_t direction, bool sortEnabled, Jam jamMode) {
    jamStartTime = 0; ringSeated = false; sortPrimed = false;
    this->direction = direction; this->sortEnabled = sortEnabled; this->jamMode = jamMode;;
  }
};
}