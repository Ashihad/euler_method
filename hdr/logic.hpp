#include <Eigen/Dense>
#include <functional>

using namespace std;
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
        virtual void run() = 0;
        virtual void printResults() const;
        virtual void saveResults(string filename="results.txt") const;
    protected:
        struct sim_params params;
        size_t max_iter;
        Matrix<double, 1, Dynamic> time_tab;
        Matrix<double, 1, Dynamic> x_tab;
        Matrix<double, 1, Dynamic> v_tab;
        Matrix<double, 1, Dynamic> kin_e_tab;
        Matrix<double, 1, Dynamic> pot_e_tab;
        Matrix<double, 1, Dynamic> total_e_tab;
        function<double(double)> pot;
        function<double(double)> dpot_dx;
        double get_kin_e(size_t) const;
        double get_pot_e(size_t) const;
        double get_total_e(size_t) const;
};

class ExplicitEulerSolver: public Solver {
    public:
        ExplicitEulerSolver(struct sim_params);
        virtual void run();
};
 