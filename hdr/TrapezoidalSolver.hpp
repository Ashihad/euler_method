#include "Solver.hpp"
#include "InitParams.hpp"

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
