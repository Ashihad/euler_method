#include "logic.hpp"

#include <iostream>
#include <fstream>

using namespace std;

double EulerSolver::pot(double x) {
    return -exp(-pow(x, 2)) - 1.2*exp(-pow((x-2), 2));
}

double EulerSolver::dpot_dx(double x) {
    return 2*x*exp(-pow(x, 2)) + 2.4*(x-2)*exp(-pow((x-2), 2));
}

double EulerSolver::get_kin_e(size_t iter) {
    return params.m*pow(v_tab(iter), 2)/2;
}

double EulerSolver::get_pot_e(size_t iter) {
    return pot(x_tab(iter));
}

double EulerSolver::get_total_e(size_t iter) {
    return get_kin_e(iter) + get_pot_e(iter);
}

EulerSolver::EulerSolver(struct sim_params init_struct): 
    params {init_struct} {
    max_iter = std::round((params.t_max-params.t_min)/params.dt);

    cout << time_tab.size() << endl;

    time_tab.resize(max_iter);
    x_tab.resize(max_iter);
    v_tab.resize(max_iter);
    kin_e_tab.resize(max_iter);
    pot_e_tab.resize(max_iter);
    total_e_tab.resize(max_iter);

    // init time table
    for (size_t i = 0; i < max_iter; ++i) {
        time_tab(i) = i*params.dt;
    }

    x_tab(0) = params.x0;
    v_tab(0) = params.v0;
    kin_e_tab(0) = get_kin_e(0);
    pot_e_tab(0) = get_pot_e(0);
    total_e_tab(0) = get_total_e(0);
}

void EulerSolver::run() {
    // main simulation loop
    for (size_t iter = 1; iter < max_iter; ++iter) {
        x_tab(iter) = x_tab(iter-1) + v_tab(iter-1)*params.dt;                          // definition of speed
        v_tab(iter) = v_tab(iter-1) - 1/params.m*dpot_dx(x_tab(iter-1))*params.dt;      // 2nd law of dynamics
        kin_e_tab(iter) = get_kin_e(iter);
        pot_e_tab(iter) = get_pot_e(iter);
        total_e_tab(iter) = get_total_e(iter);
    }
}

void EulerSolver::printResults() {
    cout << "x: " << x_tab << endl;
    cout << "v: " << v_tab << endl;
    cout << "Ek: " << kin_e_tab << endl;
    cout << "Ep: " << pot_e_tab << endl;
    cout << "E: " << total_e_tab << endl;
}

void EulerSolver::saveResults(string filename) {
    ofstream file;
    file.open(filename);
    file << "iter x v Ek Ep E" << endl;
    for (size_t iter = 0; iter < max_iter; ++iter) {
        file << iter << " " << x_tab(iter) << " " << v_tab(iter) << " " << kin_e_tab(iter) << " " << pot_e_tab(iter) << " " << total_e_tab(iter) << endl;
    }
    file.close();
}
