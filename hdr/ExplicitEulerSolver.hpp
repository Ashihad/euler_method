#include "Solver.hpp"
#include "InitParams.hpp"

class ExplicitEulerSolver: public Solver {
    public:
        ExplicitEulerSolver(struct sim_params&);
        virtual ~ExplicitEulerSolver() = default;
        virtual void run();
};