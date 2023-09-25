#include "PidController.hpp"
#include <iostream>


double PIDController::compute(double error) {
    double pTerm = kp_ * error;
    integral_ += error;
    double iTerm = ki_ * integral_;
    double dTerm = kd_ * (error - prevError_);
    prevError_ = error;

    double output = pTerm + iTerm + dTerm;
    return output;
}

