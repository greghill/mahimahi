/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef STATE_SPACE_QUEUE_HH
#define STATE_SPACE_QUEUE_HH

#include <queue>
#include <deque>
#include <tuple>
#include <cstdint>
#include <string>

#include "file_descriptor.hh"
#include "state_space_model.hh"

class StateSpaceQueue
{
private:
    uint64_t bin_start_ms_ = 0;
    uint64_t bin_size_ = 50;
    double cur_bin_delay_ = 0;
    uint64_t cur_bin_bytes_sent_ = 0;
    std::deque< std::pair<double, double> > past_bins_;

    StateSpaceModel model_;
    std::queue< std::pair<uint64_t, std::string> > packet_queue_;
    /* release timestamp, contents */

public:
    StateSpaceQueue( int ) : model_(), packet_queue_() {
        const std::pair<double, double> default_fill(5., 5.);
        for (auto i = 0; i < 15; i++) {
            past_bins_.emplace_back(default_fill);
        }
    }

    void read_packet( const std::string & contents );

    void write_packets( FileDescriptor & fd );

    unsigned int wait_time( void ) const;

    bool pending_output( void ) const { return wait_time() <= 0; }

    static bool finished( void ) { return false; }
};

#endif /* STATE_SPACE_QUEUE_HH */
