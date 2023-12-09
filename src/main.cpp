#include <iostream>

#include "Solvers.hpp"
#include "InitParams.hpp"

using namespace std;

int main() {
    sim_params init_params = gen_basic_init_params();

    ExplicitEulerSolver esolver(init_params);
    esolver.run();
    esolver.saveResults("results_euler.txt");

    TrapezoidalSolver tsolver(init_params);
    tsolver.run();
    tsolver.saveResults("results_trapezoidal.txt");

    return 0;
}