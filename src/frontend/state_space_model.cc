#include "state_space_model.hh"
#include <Eigen/Dense>

// (throughput, delay) pairs
std::pair<double, double> StateSpaceModel::query( std::queue<std::pair<double, double>> &/*previous_state*/ )
{
    return { 0, 20 };
}
