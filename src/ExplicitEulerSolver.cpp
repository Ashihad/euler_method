#include "logic.hpp"

using namespace std;

ExplicitEulerSolver::ExplicitEulerSolver(struct sim_params init_struct):
    Solver(init_struct) {}

void ExplicitEulerSolver::run() {
    // main simulation loop
    for (size_t iter = 1; iter < max_iter; ++iter) {
        x_tab(iter) = x_tab(iter-1) + v_tab(iter-1)*params.dt;                          // definition of speed
        v_tab(iter) = v_tab(iter-1) - 1/params.m*dpot_dx(x_tab(iter-1))*params.dt;      // 2nd law of dynamics
        kin_e_tab(iter) = get_kin_e(iter);
        pot_e_tab(iter) = get_pot_e(iter);
        total_e_tab(iter) = get_total_e(iter);
    }
}

