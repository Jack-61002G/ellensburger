#include "TaskWrapper.hpp"
#include "color.hpp"
#include "pros/motor_group.hpp"
#include "pros/rtos.hpp"
#include <memory>



namespace lib {



enum class Dir { In, Out, Idle };
enum class Jam { Reverse, Tap, None };
enum class Sort { Red, Blue, None };



class NewIntake : public ryan::TaskWrapper {

private:
    std::shared_ptr<pros::MotorGroup> motors;
    std::shared_ptr<lib::Color> color;

    Dir direction = Dir::Idle;
    Jam jamMode = Jam::Reverse;
    Sort sortMode = Sort::Red;

    uint jamStartTime = 0;
    bool ringSeated = false;
    bool sortPrimed = false;


public:
    NewIntake(pros::MotorGroup *motors, lib::Color *color) : motors(motors), color(color) {}


    void loop() override {
        while (true) { switch (direction) {
            
            case Dir::Idle:
                motors->move(0);
                break;

            case Dir::In:
                motors->move(127);

                if ((sortMode == Sort::Red && color->seesRed()) || (sortMode == Sort::Blue && color->seesBlue())) { sortPrimed = true; }
                else if (sortPrimed) {
                    sortPrimed = false;
                    motors->move(-127);
                    pros::delay(250);
                }

                if (motors->get_actual_velocity() < 5) { switch (jamMode) {

                    case Jam::None:
                        break;
                    
                    case Jam::Reverse:
                        if (jamStartTime == 0) { jamStartTime = pros::millis(); }
                        else if (pros::millis() - jamStartTime > 75) {
                            motors->move(-127);
                            pros::delay(250);
                        }
                        break;
                    
                    case Jam::Tap:
                        if (jamStartTime == 0 && !ringSeated) { jamStartTime = pros::millis(); }
                        else if (pros::millis() - jamStartTime > 25) {
                            ringSeated = true;
                            motors->move(0);
                            pros::delay(150);
                            motors->move(127);
                            pros::delay(150);
                        }
                        break;
                } }
                else { jamStartTime = 0; }
                break;
            
            case Dir::Out:
                motors->move(-127);
                break;

        } pros::delay(20); }
    }


    void setState(Dir direction) {
        jamStartTime = 0; ringSeated = false; sortPrimed = false;
        this->direction = direction;
    }
    void setState(Dir direction, Jam jamMode) {
        jamStartTime = 0; ringSeated = false; sortPrimed = false;
        this->direction = direction; this->jamMode = jamMode;
    }
    void setState(Dir direction, Sort sortMode) {
        jamStartTime = 0; ringSeated = false; sortPrimed = false;
        this->direction = direction; this->sortMode = sortMode;
    }
    void setState(Dir direction, Jam jamMode, Sort sortMode) {
        jamStartTime = 0; ringSeated = false;sortPrimed = false;
        this->direction = direction; this->jamMode = jamMode; this->sortMode = sortMode;
    }

}; // class Intake

} // namespace lib