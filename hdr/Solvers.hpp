#pragma once
#include <functional>
#include <vector>
#include <string>
#include <cmath>

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

class ExplicitEulerSolver: public Solver {
    public:
        ExplicitEulerSolver(struct sim_params&);
        virtual ~ExplicitEulerSolver() = default;
        virtual void run();
};

class ImplicitEulerSolver: public Solver {
    public:
        ImplicitEulerSolver(struct sim_params&);
        virtual ~ImplicitEulerSolver() = default;
        virtual void run();
    private:
        const double eps {1e-8};
        inline double F1(double, double, double) const;
        inline double F2 (double, double, double) const;
};

inline double ImplicitEulerSolver::F1(double x, double x_prev, double v) const {
    return x - x_prev - dt*v;
}

inline double ImplicitEulerSolver::F2(double x, double v, double v_prev) const {
    return v - v_prev - dt*(-1/m*dpot_dx(x) - alpha*v);
}

class TrapezoidalSolver: public Solver {
    public:
        TrapezoidalSolver(struct sim_params&);
        virtual ~TrapezoidalSolver() = default;
        virtual void run();
    private:
        const double eps {1e-8};
        inline double F1(double, double, double, double) const;
        inline double F2(double, double, double, double) const;
};

inline double TrapezoidalSolver::F1(double x, double x_prev, double v, double v_prev) const {
    return x - x_prev - dt/2*v - dt/2*v_prev;
}

inline double TrapezoidalSolver::F2(double x, double x_prev, double v, double v_prev) const {
    return v - v_prev - dt/2*(-1/m*dpot_dx(x) - alpha*v) - dt/2*(-1/m*dpot_dx(x_prev) - alpha*v_prev);
}
