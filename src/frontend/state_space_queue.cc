/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <limits>
#include <iostream>
#include <algorithm>

#include "state_space_queue.hh"
#include "timestamp.hh"

using namespace std;

void StateSpaceQueue::read_packet( const string & contents )
{
    uint64_t cur_time = timestamp();
    //cerr << contents.size() << "@ " << cur_time << endl;
    if (cur_time > (bin_start_ms_ + bin_size_)) {
        double bin_megabits = double(cur_bin_bytes_sent_ * 8) / (1024. * 1024.);
        double bin_mbps = (bin_megabits * 1000.) / double(bin_size_);

        past_bins_.emplace_back(std::pair<double, double>(bin_mbps, cur_bin_delay_));
        past_bins_.pop_front(); // drop oldest value

        /*
        cerr << "[";
        for( const auto & x : past_bins_ ) {
            cerr << "( " << x.first << ", " << x.second << "), ";
        }
        cerr << "]" << endl;
        */

        std::pair<double, uint64_t> tput_delay_pair = model_.query( past_bins_ );
        cur_bin_delay_ = tput_delay_pair.second;
        cur_bin_bytes_sent_ = 0;
    }

    // if not dropping packet
    cur_bin_bytes_sent_ += contents.size();

    packet_queue_.emplace( cur_time + cur_bin_delay_, contents );
}

void StateSpaceQueue::write_packets( FileDescriptor & fd )
{
    // WILL NOT RE-ORDER packets
    while ( (!packet_queue_.empty())
            && (packet_queue_.front().first <= timestamp()) ) {
        fd.write( packet_queue_.front().second );
        packet_queue_.pop();
    }
}

unsigned int StateSpaceQueue::wait_time( void ) const
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
