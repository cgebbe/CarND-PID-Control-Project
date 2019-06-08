#include "twiddle.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cassert>

Twiddle::Twiddle(int num_steps, std::vector<double>& params_init)
    : cnt(0),
      num_steps(num_steps),
      params(params_init),
      idx_current_experiment(0),
      idx_current_param(0)
{
    // create params_step vector with same size as params
    for (auto param : params) {
        params_step.push_back(param * 0.2);
        params_step_tol.push_back(param * 0.02);
    }
}

Twiddle::~Twiddle() {}

std::vector<double> Twiddle::get_new_params(double result) {
    // reset counter for next optimization and check need for further optimization
    cnt = 0;
    if (has_optim_terminated()) {
        std::cout << "=== Optimization has terminated!" << std::endl;
        return params;
    }

    // fill in result for latest experiment
    if (experiments.size()>0 ) {
        experiments[idx_current_experiment].result = result;
        std::cout << " --> result=" << result << std::endl;
    }

    // else, perform the actual optimization
    if (have_experiments_completed()) {
        evaluate_experiments();
        setup_new_experiments();
    }
    else {
        // if there are still experiments open, perform next one!
        idx_current_experiment+=1;
    }
    std::vector<double> new_params = experiments[idx_current_experiment].params;

    // DEBUG OUTPUT
    std::cout << "Driving with params=";
    for (auto p : new_params) {std::cout << p << ", ";}
    std::cout << " ### current params_step=";
    for (auto p : params_step) {std::cout << p << ", ";}
    std::cout << "idx_current_params=" << idx_current_param;

    return new_params;
}


bool Twiddle::has_optim_terminated() {
    for (int i=0; i<params_step.size(); i++) {
        if (params_step[i] > params_step_tol[i]) {
            return false;
        }
    }
    return true;
}

bool Twiddle::have_experiments_completed() {
    if (idx_current_experiment+1 >= experiments.size()) {
        return true;
    }
    else {
        return false;
    }
}

void Twiddle::evaluate_experiments() {
    if (experiments.size()>0) {
        // check that all experiments have a result
        for (auto exp : experiments) {
            assert(exp.result != -1);
        }

        // identify experiment with lowest result (=lowest error)
        Experiment experiment_lowest_result = *std::min_element(
                    std::begin(experiments),std::end(experiments),
                    [] (const Experiment& a, const Experiment&b) {return a.result < b.result;}
        );
        if (experiment_lowest_result.is_org) {
            params_step[idx_current_param] *= 0.9;
            std::cout << "=== Evaluated: original params scored lowest result=";
        }
        else {
            params_step[idx_current_param] *= 1.1;
            std::cout << "=== Evaluated: new params scored lowest result=";
        }
        std::cout << experiment_lowest_result.result << std::endl;
        params = experiment_lowest_result.params;
    }
}

void Twiddle::setup_new_experiments() {
    experiments.clear();
    idx_current_param = (idx_current_param+1) % params.size();
    idx_current_experiment = 0; // this means that three experiments are started for each parameter!

    // add current parameter setup as first experiment
    Experiment exp_org;
    exp_org.is_org = true;
    exp_org.params = params;
    experiments.push_back(exp_org);

    // setup two new experiments, where step in one direction
    for (int step_direction=-1; step_direction!=3; step_direction+=2) {
        double step_value = params_step[idx_current_param] * step_direction;
        Experiment exp_new;
        exp_new.is_org = false;
        exp_new.params = params;
        exp_new.params[idx_current_param] += step_value;
        experiments.push_back(exp_new);
    }
    std::cout << "=== Set up new experiments!" << std::endl;
}
