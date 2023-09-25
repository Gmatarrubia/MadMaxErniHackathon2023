
#include <iostream>

class PIDController {
public:
    PIDController() = default;
    ~PIDController() = default;
    double compute(double error);

private:
    double kp_ = 0.1;
    double ki_ = 0.01;
    double kd_ = 0.02;
    double prevError_;
    double integral_;
};
