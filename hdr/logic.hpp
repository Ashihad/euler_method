#include <Eigen/Dense>
#include <functional>

using namespace std;
using namespace Eigen;

struct sim_params {
    double m;
    double v0;
    double x0;
    double dt;
    double t_min;
    double t_max;
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

class EulerSolver: public Solver {
    public:
        EulerSolver(struct sim_params);
        virtual void run();
};
        
 