/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef VAR_DELAY_QUEUE_HH
#define VAR_DELAY_QUEUE_HH

#include <queue>
#include <cstdint>
#include <string>
#include <random>

#include "file_descriptor.hh"

class VarDelayQueue
{
private:
    const uint64_t min_delay_ms_;
    const uint64_t max_delay_ms_;
    const double step_ = .1;
    double cur_delay_ms_;

    std::default_random_engine prng_;
    std::uniform_int_distribution<> dist_;

    std::queue< std::pair<uint64_t, std::string> > packet_queue_;
    /* release timestamp, contents */

public:
    VarDelayQueue( const uint64_t & min_delay_ms, const uint64_t & max_delay_ms ) : min_delay_ms_( min_delay_ms ), max_delay_ms_( max_delay_ms ), cur_delay_ms_( (min_delay_ms+max_delay_ms)/2 ), prng_( std::random_device()() ), dist_( 0, 1 ), packet_queue_() {}

    void read_packet( const std::string & contents );

    void write_packets( FileDescriptor & fd );

    unsigned int wait_time( void ) const;

    bool pending_output( void ) const { return wait_time() <= 0; }

    static bool finished( void ) { return false; }
};

#endif /* VAR_DELAY_QUEUE_HH */
