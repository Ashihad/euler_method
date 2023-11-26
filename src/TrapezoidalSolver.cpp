#include "Solvers.hpp"

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

    // lhs_matrix * lhs_vector = rhs
    Matrix2f lhs_matrix;
    lhs_matrix(0, 0) = 1;
    lhs_matrix(0, 1) = -dt/2;
    lhs_matrix(1, 1) = 1 + dt/2*alpha;
    Vector2f lhs_vector;                // fill with arbitrary value greater than eps
    lhs_vector(0) = eps+1;
    lhs_vector(1) = eps+1;
    Vector2f rhs;
    rhs(0) = -F1(x_tab(0), x_tab(0), v_tab(0), v_tab(0));
    rhs(1) = -F2(x_tab(0), x_tab(0), v_tab(0), v_tab(0));

    double x_mu; double x_mu_prev;
    double v_mu; double v_mu_prev;
    size_t mu;

    // main simulation loop
    for (size_t iter = 1; iter < max_iter; ++iter) {
        x_mu = x_tab(iter-1); x_mu_prev = x_tab(iter-1);
        v_mu = v_tab(iter-1); v_mu_prev = v_tab(iter-1);
        mu = 0;
        while (rhs(0) > eps && rhs(1) > eps) {
            lhs_matrix(1, 0) = dt/(2*m)*d2pot_dx2(x_mu);
            rhs(0) = -F1(x_mu, x_tab(iter-1), v_mu, v_tab(iter-1));
            rhs(1) = -F2(x_mu, x_tab(iter-1), v_mu, v_tab(iter-1));
            lhs_vector += lhs_matrix.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(rhs);
            x_mu_prev = x_mu; v_mu_prev = v_prev;
            ++mu;
        }
        x_tab(iter) = x_tab(iter-1) + v_tab(iter-1)*dt;  // definition of speed
        v_tab(iter) = v_tab(iter-1) - 1/m*dpot_dx(x_tab(iter-1))*dt \
         - alpha*v_tab(iter-1)*dt;                // 2nd law of dynamics
        kin_e_tab(iter) = get_kin_e(iter);
        pot_e_tab(iter) = get_pot_e(iter);
        total_e_tab(iter) = get_total_e(iter);
    }
}

