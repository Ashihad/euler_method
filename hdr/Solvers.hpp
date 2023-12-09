#include <Eigen/Dense>
#include <functional>

using namespace Eigen;

struct sim_params {
    double m;       // object mass [kg]
    double v0;      // initial velocity [m/s]
    double x0;      // initial position [m]
    double dt;      // time step [s]
    double t_min;   // start time [s]
    double t_max;   // end time [s]
    double alpha;   // damping parameter, (alpha > 0) [1/s]
};

class Solver {
    public:
        Solver(struct sim_params);
        virtual ~Solver() = default;
        virtual void run() = 0;
        virtual void printResults() const;
        virtual void saveResults(std::string filename="results.txt") const;
    protected:
        const double m;
        const double v0;
        const double x0;
        const double dt;
        const double t_min;
        const double t_max;
        const double alpha;
        size_t max_iter;
        Matrix<double, 1, Dynamic> time_tab;
        Matrix<double, 1, Dynamic> x_tab;
        Matrix<double, 1, Dynamic> v_tab;
        Matrix<double, 1, Dynamic> kin_e_tab;
        Matrix<double, 1, Dynamic> pot_e_tab;
        Matrix<double, 1, Dynamic> total_e_tab;
        std::function<double(double)> pot;
        std::function<double(double)> dpot_dx;
        std::function<double(double)> d2pot_dx2;
        double get_kin_e(double) const;
        double get_pot_e(double) const;
        double get_total_e(double, double) const;
};

class ExplicitEulerSolver: public Solver {
    public:
        ExplicitEulerSolver(struct sim_params);
        virtual ~ExplicitEulerSolver() = default;
        virtual void run();
};

class TrapezoidalSolver: public Solver {
    public:
        TrapezoidalSolver(struct sim_params);
        virtual ~TrapezoidalSolver() = default;
        virtual void run();
    protected:
        const double eps {1e-6};
};
