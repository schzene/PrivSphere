#include "linear-ot.h"
#include <cmath>
#include <omp.h>

#define MAX_NUM_OT (1 << 24)

#define USE_EIGEN
#ifdef USE_EIGEN
#include <Eigen/Dense>
#endif