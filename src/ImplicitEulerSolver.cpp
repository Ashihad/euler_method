#include <cmath>
#include <iostream>
#include <Eigen/Dense>

#include "Solvers.hpp"
#include "InitParams.hpp"

using namespace std;
using namespace Eigen;

ImplicitEulerSolver::ImplicitEulerSolver(struct sim_params& init_struct):
    Solver(init_struct) {}

void ImplicitEulerSolver::run() {
    // lhs_matrix * lhs_vector = rhs_vector
    Matrix2f lhs_matrix;
    lhs_matrix(0, 0) = 1;
    lhs_matrix(0, 1) = -dt;
    lhs_matrix(1, 1) = 1 + dt*alpha;
    Vector2f lhs_vector;                // empty, will be filled during solving
    Vector2f rhs_vector;
    rhs_vector(0) = -F1(x_tab[0], x_tab[0], v_tab[0]);
    rhs_vector(1) = -F2(x_tab[0], v_tab[0], v_tab[0]);

    double x_mu; double x_mu_old;
    double v_mu; double v_mu_old;
    size_t mu_counter;

    // main simulation loop
    for (size_t iter = 1; iter < max_iter; ++iter) {
        // start mu-iteration from values of last simulation iteration
        x_mu = x_tab[iter-1];
        v_mu = v_tab[iter-1];
        mu_counter = 0;
        do {
            lhs_matrix(1, 0) = dt/m*d2pot_dx2(x_mu);
            rhs_vector(0) = -F1(x_mu, x_tab[iter-1], v_mu);
            rhs_vector(1) = -F2(x_mu, v_mu, v_tab[iter-1]);
            lhs_vector = lhs_matrix.colPivHouseholderQr().solve(rhs_vector);
            x_mu_old = x_mu;
            v_mu_old = v_mu;
            x_mu += lhs_vector(0);
            v_mu += lhs_vector(1);
            ++mu_counter;
        }
        while ((abs(x_mu - x_mu_old) > eps && abs(v_mu - v_mu_old) > eps) && mu_counter <= 10);
        
        x_tab[iter] = x_mu;
        v_tab[iter] = v_mu;
        kin_e_tab[iter] = get_kin_e(v_tab[iter]);
        pot_e_tab[iter] = get_pot_e(x_tab[iter]);
        total_e_tab[iter] = get_total_e(x_tab[iter], v_tab[iter]);
    }
}

