#include "ExplicitEulerSolver.hpp"
#include "InitParams.hpp"

using namespace std;

ExplicitEulerSolver::ExplicitEulerSolver(struct sim_params& init_struct):
    Solver(init_struct) {}

void ExplicitEulerSolver::run() {
    // main simulation loop
    for (size_t iter = 1; iter < max_iter; ++iter) {
        x_tab[iter] = x_tab[iter-1] + v_tab[iter-1]*dt;  // definition of speed
        v_tab[iter] = v_tab[iter-1] - 1/m*dpot_dx(x_tab[iter-1])*dt \
         - alpha*v_tab[iter-1]*dt;                // 2nd law of dynamics
        kin_e_tab[iter] = get_kin_e(v_tab[iter]);
        pot_e_tab[iter] = get_pot_e(x_tab[iter]);
        total_e_tab[iter] = get_total_e(x_tab[iter], v_tab[iter]);
    }
}
