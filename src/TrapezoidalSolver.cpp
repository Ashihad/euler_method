#include "Solvers.hpp"
#include <cmath>
#include <iostream>

using namespace std;

TrapezoidalSolver::TrapezoidalSolver(struct sim_params init_struct):
    Solver(init_struct) {}

void TrapezoidalSolver::run() {
    auto F1 = [&] (double x, double x_prev, double v, double v_prev) {
        return x - x_prev - dt/2*v - dt/2*v_prev;
    };
    auto F2 = [&] (double x, double x_prev, double v, double v_prev) {
        return v - v_prev - dt/2*(-1/m*dpot_dx(x) - alpha*v) - dt/2*(-1/m*dpot_dx(x_prev) - alpha*v_prev);
    };

    // lhs_matrix * lhs_vector = rhs_vector
    cout << "in run" << "\n";
    Matrix2f lhs_matrix;
    lhs_matrix(0, 0) = 1;
    lhs_matrix(0, 1) = -dt/2;
    lhs_matrix(1, 1) = 1 + dt/2*alpha;
    Vector2f lhs_vector;                // fill with arbitrary value greater than eps
    lhs_vector(0) = eps+1;
    lhs_vector(1) = eps+1;
    Vector2f rhs_vector;
    rhs_vector(0) = -F1(x_tab(0), x_tab(0), v_tab(0), v_tab(0));
    rhs_vector(1) = -F2(x_tab(0), x_tab(0), v_tab(0), v_tab(0));

    double x_mu;
    double v_mu;
    size_t mu_counter;

    // main simulation loop
    for (size_t iter = 1; iter < max_iter; ++iter) {
        // start mu-iteration from values of last simulation iteration
        x_mu = x_tab(iter-1);
        v_mu = v_tab(iter-1);
        mu_counter = 0;
        cout << "in main loop, iter=" << iter << "\n";
        // while ((abs(lhs_vector(0)) > eps && abs(lhs_vector(1)) > eps) && mu_counter >= 10) {
        while (mu_counter <= 5) {
            cout << "mu= " << mu_counter << "\n";
            lhs_matrix(1, 0) = dt/(2*m)*d2pot_dx2(x_mu);
            rhs_vector(0) = -F1(x_mu, x_tab(iter-1), v_mu, v_tab(iter-1));
            rhs_vector(1) = -F2(x_mu, x_tab(iter-1), v_mu, v_tab(iter-1));
            lhs_vector = lhs_matrix.colPivHouseholderQr().solve(rhs_vector);
            x_mu += lhs_vector(0);
            v_mu += lhs_vector(1);
            ++mu_counter;
        }
        x_tab(iter) = x_mu;
        v_tab(iter) = v_mu;
        kin_e_tab(iter) = get_kin_e(v_tab(iter));
        pot_e_tab(iter) = get_pot_e(x_tab(iter));
        total_e_tab(iter) = get_total_e(x_tab(iter), v_tab(iter));
    }
}

