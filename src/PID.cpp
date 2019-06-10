#include "PID.h"
#include <math.h>
#include <algorithm>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID(double Kp_, double Kd_, double Ki_)
    : error(0),
      Kp(Kp_), Ki(Ki_), Kd(Kd_),
      cte_last(0), cte_int(0)
{
}

PID::~PID() {}

double PID::get_steering_angle(double cte) {

    // calculate time derivatives or integratives of cte
    double dt = 1; // assuming equi-distant spacing between sensor measurements
    double cte_diff = (cte - cte_last) / dt;
    cte_last = cte;
    cte_int += cte;
    error += cte*cte;

    // calculate steering angle
    double steer_angle = -Kp * cte - Kd * cte_diff - Ki * cte_int;
    steer_angle = clip(steer_angle, -1., +1.);
    return steer_angle;
}



double PID::clip(double x, double x_min, double x_max) {
    x = std::max(x, x_min);
    x = std::min(x, x_max);
    return x;
}

void PID::reset_with_new_params(double Kp_, double Kd_, double Ki_)
{
    Kp = Kp_;
    Kd = Kd_;
    Ki = Ki_;
    cte_int = 0;
    error = 0;
}
