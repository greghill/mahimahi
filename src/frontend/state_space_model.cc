#include "state_space_model.hh"

void StateSpaceModel::update( double throughput, double delay )
{
    throughput += 1;
    delay += 1;
    return;
}

std::pair<double, double> StateSpaceModel::query( )
{
    return {0,0};
}
