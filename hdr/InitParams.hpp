#pragma once
struct sim_params {
    double m;       // object mass [kg]
    double v0;      // initial velocity [m/s]
    double x0;      // initial position [m]
    double dt;      // time step [s]
    double dx;      // step in space (for derivatives) [m]
    double t_min;   // start time [s]
    double t_max;   // end time [s]
    double alpha;   // damping parameter, (alpha > 0) [1/s]
};

struct sim_params gen_basic_init_params();
