#include "logic.hpp"

#include <iostream>
#include <fstream>

Solver::Solver(struct sim_params init_struct): 
    params {init_struct} {
    max_iter = std::round((params.t_max-params.t_min)/params.dt);

    // set potential function and its derivative
    pot = [](double x) {return -exp(-pow(x, 2)) - 1.2*exp(-pow((x-2), 2));};
    dpot_dx = [] (double x) {return 2*x*exp(-pow(x, 2)) + 2.4*(x-2)*exp(-pow((x-2), 2));};

    // init result tables
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

    // init initial parameters
    x_tab(0) = params.x0;
    v_tab(0) = params.v0;
    kin_e_tab(0) = get_kin_e(0);
    pot_e_tab(0) = get_pot_e(0);
    total_e_tab(0) = get_total_e(0);
}

void Solver::printResults() const {
    cout << "t: " << time_tab << endl;
    cout << "x: " << x_tab << endl;
    cout << "v: " << v_tab << endl;
    cout << "Ek: " << kin_e_tab << endl;
    cout << "Ep: " << pot_e_tab << endl;
    cout << "E: " << total_e_tab << endl;
}

void Solver::saveResults(string filename) const {
    ofstream file;
    file.open(filename);
    file << "iter t x v Ek Ep E" << endl;
    for (size_t iter = 0; iter < max_iter; ++iter) {
        file << iter << " " << time_tab(iter) << " " \
        << x_tab(iter) << " " << v_tab(iter) << " " \
        << kin_e_tab(iter) << " " << pot_e_tab(iter) << " " \
        << total_e_tab(iter) << endl;
    }
    file.close();
}

double Solver::get_kin_e(size_t iter) const {
    return params.m*pow(v_tab(iter), 2)/2;
}

double Solver::get_pot_e(size_t iter) const {
    return pot(x_tab(iter));
}

double Solver::get_total_e(size_t iter) const {
    return get_kin_e(iter) - get_pot_e(iter);
}