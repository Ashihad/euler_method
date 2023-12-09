#include <iostream>
#include <fstream>
#include <cmath>

#include "Solver.hpp"
#include "InitParams.hpp"

using namespace std;

Solver::Solver(struct sim_params& init_struct) :
    m {init_struct.m}, 
    v0 {init_struct.v0}, 
    x0 {init_struct.x0}, 
    dt {init_struct.dt },
    dx {init_struct.dx}, 
    t_min {init_struct.t_min}, 
    t_max {init_struct.t_max}, 
    alpha {init_struct.alpha},
    max_iter {static_cast<size_t>(std::round((t_max-t_min)/dt))} {

    verify_parameters();

    // init result tables
    time_tab.reserve(max_iter);
    x_tab.reserve(max_iter);
    v_tab.reserve(max_iter);
    kin_e_tab.reserve(max_iter);
    pot_e_tab.reserve(max_iter);
    total_e_tab.reserve(max_iter);

    // init time table
    for (size_t i = 0; i < max_iter; ++i) {
        time_tab[i] = i*dt;
    }

    // init initial parameters
    x_tab[0] = x0;
    v_tab[0] = v0;
    kin_e_tab[0] = get_kin_e(v0);
    pot_e_tab[0] = get_pot_e(x0);
    total_e_tab[0] = get_total_e(x0, v0);
}

void Solver::printResults() const {
    /* for debugging purposes */
    cout << "t: " << "\n";
    for (const double& elem: time_tab) {
        cout << elem << "\n";
    }
    cout << "x: " << "\n";
    for (const double& elem: x_tab) {
        cout << elem << "\n";
    }
    cout << "v: " << "\n";
    for (const double& elem: v_tab) {
        cout << elem << "\n";
    }
    cout << "Ek: " << "\n";
    for (const double& elem: kin_e_tab) {
        cout << elem << "\n";
    }
    cout << "Ep: " << "\n";
    for (const double& elem: pot_e_tab) {
        cout << elem << "\n";
    }
    cout << "E: " << "\n";
    for (const double& elem: total_e_tab) {
        cout << elem << "\n";
    }
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
        << time_tab[iter] << " " \
        << x_tab[iter] << " " \
        << v_tab[iter] << " " \
        << kin_e_tab[iter] << " " \
        << pot_e_tab[iter] << " " \
        << total_e_tab[iter] << "\n";
    }
    file.close();
}

void Solver::verify_parameters() {
    if (m < 0) throw invalid_argument {"Mass cannot be <=0"};
    if (dt < 0) throw invalid_argument {"Time stape cannot be <=0"};
    if (dx < 0) throw invalid_argument {"Distance step cannot be <=0"};
    if (t_min < 0) throw invalid_argument {"Start time cannot be negative"};
    if (t_max <= 0) throw invalid_argument {"End time cannot be negative or zero"};
    if (alpha < 0) throw invalid_argument {"Damping parameter cannot be negative"};
    if (t_max - t_min <= 0) throw invalid_argument {"Time span cannot be negative, nor zero"};
    if (max_iter < 1) throw invalid_argument {"Time span is too short for simulation to run"};
}
