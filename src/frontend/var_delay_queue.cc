/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <limits>
#include <iostream>

#include "var_delay_queue.hh"
#include "timestamp.hh"

using namespace std;

void VarDelayQueue::read_packet( const string & contents )
{
    bool move_up = dist_( prng_ ) == 1;
    if ( move_up )
    {
        cur_delay_ms_ += step_;
    } else {
        cur_delay_ms_ -= step_;
    }

    cur_delay_ms_ = min(cur_delay_ms_, (double) max_delay_ms_);
    cur_delay_ms_ = max(cur_delay_ms_, (double) min_delay_ms_);

    uint64_t var_delay_ms = cur_delay_ms_;
    packet_queue_.emplace( timestamp() + var_delay_ms, contents );
}

void VarDelayQueue::write_packets( FileDescriptor & fd )
{
    while ( (!packet_queue_.empty())
            && (packet_queue_.front().first <= timestamp()) ) {
        fd.write( packet_queue_.front().second );
        packet_queue_.pop();
    }
}

unsigned int VarDelayQueue::wait_time( void ) const
{
    if ( packet_queue_.empty() ) {
        return numeric_limits<uint16_t>::max();
    }

    const auto now = timestamp();

    if ( packet_queue_.front().first <= now ) {
        return 0;
    } else {
        return packet_queue_.front().first - now;
    }
}
