#include <iostream>
#include <Eigen/Dense>

#include "Solvers.hpp"

using namespace std;
using namespace Eigen;

int main() {
    sim_params basic_init_params {};
    basic_init_params.m = 1;
    basic_init_params.v0 = 0;
    basic_init_params.x0 = 2.8; 
    basic_init_params.dt = 0.01;
    basic_init_params.t_min = 0;
    basic_init_params.t_max = 100;
    basic_init_params.alpha = 0;

    ExplicitEulerSolver solver(basic_init_params);
    solver.run();
    solver.saveResults();

    TrapezoidalSolver solver2(basic_init_params);
    solver2.run();
    solver2.saveResults();

    return 0;
}