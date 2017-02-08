/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef STATE_SPACE_MODEL
#define STATE_SPACE_MODEL

#include <utility>
#include <queue>

class StateSpaceModel
{
public:
    std::pair<double, double> query( std::queue<std::pair<double, double>> &previous_state );
};

#endif /* STATE_SPACE_MODEL */ 
