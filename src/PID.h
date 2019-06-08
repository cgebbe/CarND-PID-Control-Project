#ifndef PID_H
#define PID_H

class PID {
 public:
  PID(double Kp_, double Kd_, double Ki_);
  virtual ~PID();
  double get_steering_angle(double cte);
  void reset_with_new_params(double Kp, double Kd, double Ki);
  double error;

 private:
  double Kp;
  double Ki;
  double Kd;
  double cte_last;
  double cte_int;
  double clip(double x, double x_min, double x_max);
};

#endif  // PID_H
