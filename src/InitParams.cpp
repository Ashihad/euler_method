#include "InitParams.hpp"

struct sim_params gen_basic_init_params() {
    sim_params init_params {
        .m=1,
        .v0=0,
        .x0=2.8,
        .dt=0.01,
        .dx=0.01,
        .t_min=0,
        .t_max=50,
        .alpha=0
    };
    return init_params;
}