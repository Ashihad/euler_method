#pragma once
#include <vector>
#include <string>
#include <numeric>

#include "InitParams.hpp"

class Solver {
    public:
        Solver(struct sim_params&);
        virtual ~Solver() = default;
        virtual void run() = 0;
        virtual void printResults() const;
        virtual void saveResults(std::string filename="results.txt") const;
    protected:
        const double m;
        const double v0;
        const double x0;
        const double dt;
        const double dx;
        const double t_min;
        const double t_max;
        const double alpha;
        void verify_parameters();
        size_t max_iter;
        std::vector<double> time_tab;
        std::vector<double> x_tab;
        std::vector<double> v_tab;
        std::vector<double> kin_e_tab;
        std::vector<double> pot_e_tab;
        std::vector<double> total_e_tab;
        inline double pot(double) const;
        inline double dpot_dx(double) const;
        inline double d2pot_dx2(double) const;
        inline double get_kin_e(double) const;
        inline double get_pot_e(double) const;
        inline double get_total_e(double, double) const;
};

inline double Solver::pot(double x) const {
    /* potential function */
    return -std::exp(-std::pow(x, 2)) - 1.2*std::exp(-std::pow((x-2), 2));
}

inline double Solver::dpot_dx(double x) const {
    /* five point 1st order derivative */
    return (pot(x-2*dx) - 8*pot(x-dx) + 8*pot(x+dx) - pot(x+2*dx))/(12*dx);
}

inline double Solver::d2pot_dx2(double x) const {
    /* five point 2nd order derivative */
    return (-pot(x-2*dx) + 16*pot(x-dx) - 30*pot(x) + 16*pot(x+dx) - pot(x+2*dx))/(12*dx);
}

inline double Solver::get_kin_e(double v) const {
    return m*std::pow(v, 2)/2;
}

inline double Solver::get_pot_e(double x) const {
    return pot(x);
}

inline double Solver::get_total_e(double x, double v) const {
    return get_kin_e(v) - get_pot_e(x);
}
