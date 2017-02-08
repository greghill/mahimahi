/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <vector>
#include <string>
#include <iostream>

#include <getopt.h>

#include "state_space_queue.hh"
#include "util.hh"
#include "ezio.hh"
#include "packetshell.cc"

using namespace std;

void usage_error( const string & program_name )
{
    throw runtime_error( "Usage: " + program_name );
}

int main( int argc, char *argv[] )
{
    try {
        /* clear environment while running as root */
        char ** const user_environment = environ;
        environ = nullptr;

        check_requirements( argc, argv );

        vector< string > command;

        if ( optind == argc ) {
            command.push_back( shell_path() );
        } else {
            for ( int i = optind; i < argc; i++ ) {
                command.push_back( argv[ i ] );
            }
        }

        PacketShell<StateSpaceQueue> state_space_app( "statespace", user_environment );

        state_space_app.start_uplink( "[state-space] ", command, 7 );
        state_space_app.start_downlink( 8 );
        return state_space_app.wait_for_exit();

    } catch ( const exception & e ) {
        print_exception( e );
        return EXIT_FAILURE;
    }
}
