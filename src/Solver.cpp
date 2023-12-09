#include "Solvers.hpp"
#include "InitParams.hpp"

#include <iostream>
#include <fstream>

using namespace std;

Solver::Solver(struct sim_params init_struct):
    m {init_struct.m}, 
    v0 {init_struct.v0}, 
    x0 {init_struct.x0}, 
    dt {init_struct.dt}, 
    t_min {init_struct.t_min}, 
    t_max {init_struct.t_max}, 
    alpha {init_struct.alpha} {
    
    max_iter = std::round((t_max-t_min)/dt);

    // set potential function and its derivatives
    pot = [](double x) {return -exp(-pow(x, 2)) - 1.2*exp(-pow((x-2), 2));};
    dpot_dx = [] (double x) {return 2*x*exp(-pow(x, 2)) + 2.4*(x-2)*exp(-pow((x-2), 2));};
    d2pot_dx2 = [] (double x) { return  -4*pow(x, 2)*exp(-pow(x, 2)) \
                                        + 2*exp(-pow(x, 2)) \
                                        - 24/5.*pow((x-2), 2)*exp(-pow(x-2, 2)) \
                                        + 12/5.*exp(-pow(x-2, 2));};

    // init result tables
    time_tab.resize(max_iter);
    x_tab.resize(max_iter);
    v_tab.resize(max_iter);
    kin_e_tab.resize(max_iter);
    pot_e_tab.resize(max_iter);
    total_e_tab.resize(max_iter);

    // init time table
    for (size_t i = 0; i < max_iter; ++i) {
        time_tab(i) = i*dt;
    }

    // init initial parameters
    x_tab(0) = x0;
    v_tab(0) = v0;
    kin_e_tab(0) = get_kin_e(v0);
    pot_e_tab(0) = get_pot_e(x0);
    total_e_tab(0) = get_total_e(x0, v0);
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
    ofstream file {filename, ios_base::out | ios_base::trunc};
    if (!file.good()) {
        cerr << "Can't open file " << filename << endl;
        throw std::runtime_error("Could not open file");
    }
    string header {"iter t x v Ek Ep E"};
    file << header << "\n";
    for (size_t iter = 0; iter < max_iter; ++iter) {
        file << iter << " " \
        << time_tab(iter) << " " \
        << x_tab(iter) << " " \
        << v_tab(iter) << " " \
        << kin_e_tab(iter) << " " \
        << pot_e_tab(iter) << " " \
        << total_e_tab(iter) << "\n";
    }
    file.close();
}

double Solver::get_kin_e(double v) const {
    return m*pow(v, 2)/2;
}

double Solver::get_pot_e(double x) const {
    return pot(x);
}

double Solver::get_total_e(double x, double v) const {
    return get_kin_e(v) - get_pot_e(x);
}