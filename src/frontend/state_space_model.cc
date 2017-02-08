#include "state_space_model.hh"
#include <Eigen/Dense>

// (throughput, delay) pairs
std::pair<double, uint64_t> StateSpaceModel::query( std::deque<std::pair<double, uint64_t>> &/*previous_state*/ )
{
    return { 5, 20 };
}
