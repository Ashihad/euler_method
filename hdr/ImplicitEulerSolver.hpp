#include "Solver.hpp"
#include "InitParams.hpp"

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