#include <iostream>
#include <Eigen/Dense>

#include "logic.hpp"

using namespace std;
using namespace Eigen;

int main() {
    sim_params init_params {};
    init_params.m = 1;      // kg
    init_params.v0 = 0;     // m/s
    init_params.x0 = 2.8;   // m
    init_params.dt = 0.01;  // s
    init_params.t_min = 0;  // s
    init_params.t_max = 20; // s

    EulerSolver solver(init_params);
    solver.run();
    solver.printResults();
    solver.saveResults();

    return 0;
}