/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <vector>
#include <string>

#include "var_delay_queue.hh"
#include "util.hh"
#include "ezio.hh"
#include "packetshell.cc"

using namespace std;

int main( int argc, char *argv[] )
{
    try {
        /* clear environment while running as root */
        char ** const user_environment = environ;
        environ = nullptr;

        check_requirements( argc, argv );

        if ( argc < 3 ) {
            throw runtime_error( "Usage: " + string( argv[ 0 ] ) + " min-delay-milliseconds max-delay-milliseconds [command...]" );
        }

        const uint64_t min_delay_ms = myatoi( argv[ 1 ] );
        const uint64_t max_delay_ms = myatoi( argv[ 2 ] );

        vector< string > command;

        if ( argc == 3 ) {
            command.push_back( shell_path() );
        } else {
            for ( int i = 3; i < argc; i++ ) {
                command.push_back( argv[ i ] );
            }
        }

        PacketShell<VarDelayQueue> var_delay_shell_app( "var-delay", user_environment );

        var_delay_shell_app.start_uplink( "[var-delay " + to_string( min_delay_ms )+ "-" + to_string( max_delay_ms ) + " ms] ",
                                      command,
                                      min_delay_ms, max_delay_ms );
        var_delay_shell_app.start_downlink( min_delay_ms, max_delay_ms );
        return var_delay_shell_app.wait_for_exit();
    } catch ( const exception & e ) {
        print_exception( e );
        return EXIT_FAILURE;
    }
}
