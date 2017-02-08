/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef STATE_SPACE_QUEUE_HH
#define STATE_SPACE_QUEUE_HH

#include <queue>
#include <cstdint>
#include <string>

#include "file_descriptor.hh"
#include "state_space_model.hh"

class StateSpaceQueue
{
private:
    StateSpaceModel model_;
    std::queue< std::pair<uint64_t, std::string> > packet_queue_;
    /* release timestamp, contents */

public:
    StateSpaceQueue( int ) : model_(), packet_queue_() {}

    void read_packet( const std::string & contents );

    void write_packets( FileDescriptor & fd );

    unsigned int wait_time( void ) const;

    bool pending_output( void ) const { return wait_time() <= 0; }

    static bool finished( void ) { return false; }
};

#endif /* STATE_SPACE_QUEUE_HH */
