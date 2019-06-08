#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>
#include "PID.h"


struct Experiment
{
    bool is_org = false ;
    std::vector<double> params;
    double result = -1;
};

class Twiddle
{
public:
    Twiddle(int num_steps, std::vector<double>& params_init);
    ~Twiddle();
    std::vector<double> get_new_params(double result);
    int cnt;
    int num_steps;
private:
    std::vector<double> params;
    std::vector<double> params_step;
    std::vector<double> params_step_tol;
    std::vector<Experiment> experiments;
    int idx_current_experiment;
    int idx_current_param;
    bool has_optim_terminated();
    void evaluate_experiments();
    void setup_new_experiments();
    bool have_experiments_completed();
};

#endif  // TWIDDLE_H
