/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef STATE_SPACE_MODEL
#define STATE_SPACE_MODEL

#include <utility>

class StateSpaceModel
{
public:
    void update( double throughput, double delay );

    std::pair<double, double> query( );
};

#endif /* STATE_SPACE_MODEL */ 
