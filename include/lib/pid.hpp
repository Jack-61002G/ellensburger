
class PID {

private:

    float kp;
    float ki;
    float kd;
    float prev_error = 0;
    float integral = 0;

public:

    PID(float p, float i, float d) : kp(p), ki(i), kd(d) {}

    float compute(float error) {
        integral += error;
        float derivative = error - prev_error;
        prev_error = error;
        return error * kp + integral * ki + derivative * kd;
    }

};