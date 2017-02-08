/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef STATE_SPACE_MODEL
#define STATE_SPACE_MODEL

#include "stdint.h"
#include <utility>
#include <deque>

class StateSpaceModel
{
public:
    std::pair<double, uint64_t> query( std::deque<std::pair<double, uint64_t>> &previous_state );
};

#endif /* STATE_SPACE_MODEL */ 
