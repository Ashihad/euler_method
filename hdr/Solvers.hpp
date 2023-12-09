#pragma once
#include <functional>
#include <vector>
#include <string>

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
        std::function<double(double)> pot;
        double dpot_dx(double);
        double d2pot_dx2(double);
        double get_kin_e(double) const;
        double get_pot_e(double) const;
        double get_total_e(double, double) const;
};

class ExplicitEulerSolver: public Solver {
    public:
        ExplicitEulerSolver(struct sim_params&);
        virtual ~ExplicitEulerSolver() = default;
        virtual void run();
};

class TrapezoidalSolver: public Solver {
    public:
        TrapezoidalSolver(struct sim_params&);
        virtual ~TrapezoidalSolver() = default;
        virtual void run();
    private:
        const double eps {1e-8};
        inline double F1(double, double, double, double);
        inline double F2(double, double, double, double);
};
