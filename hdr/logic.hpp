#include <Eigen/Dense>

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

class EulerSolver {
    public:
        EulerSolver(struct sim_params);
        void run();
        void printResults();
        void saveResults(string filename="results.txt");
    private:
        struct sim_params params;
        size_t max_iter;
        Matrix<double, 1, Dynamic> time_tab;
        Matrix<double, 1, Dynamic> x_tab;
        Matrix<double, 1, Dynamic> v_tab;
        Matrix<double, 1, Dynamic> kin_e_tab;
        Matrix<double, 1, Dynamic> pot_e_tab;
        Matrix<double, 1, Dynamic> total_e_tab;
        double pot(double);
        double dpot_dx(double);
        double get_kin_e(size_t);
        double get_pot_e(size_t);
        double get_total_e(size_t);
};
