#include <iostream>

#include "ExplicitEulerSolver.hpp"
#include "ImplicitEulerSolver.hpp"
#include "TrapezoidalSolver.hpp"
#include "InitParams.hpp"

using namespace std;

int main() {
    sim_params init_params = gen_basic_init_params();

    ExplicitEulerSolver eesolver(init_params);
    eesolver.run();
    eesolver.saveResults("results_expl_euler.txt");

    ImplicitEulerSolver iesolver(init_params);
    iesolver.run();
    iesolver.saveResults("results_impl_euler.txt");

    TrapezoidalSolver tsolver(init_params);
    tsolver.run();
    tsolver.saveResults("results_trapezoidal.txt");

    return 0;
}