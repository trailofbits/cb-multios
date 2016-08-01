/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>
#include <stdlib.h>
#include <mymath.h>

#include "simulation.h"
#include "render.h"

#define BANNER_STR "2D Particle Simulator\nEnter the number of particles to simulate (1-10):\n"
#define PARTICLE_PROMPT_POSITION "Enter Position (x,y):\n"
#define PARTICLE_PROMPT_VELOCITY "Enter Velocity (x,y):\n"
#define PARTICLE_PROMPT_MASS     "Enter Mass:\n"
#define PARTICLE_PROMPT_RADIUS   "Enter Radius:\n"
#define SIMULATION_TIME_PROMPT   "Enter Simulation Runtime (in seconds):\n"
#define SIMULATION_RUNNING_PROMPT   "Simulation running...\n"

#define BAD_POSITION_ERROR      "Invalid position. Try again.\n"
#define BAD_VELOCITY_ERROR      "Invalid velocity. Try again.\n"
#define BAD_MASS_ERROR          "Invalid mass. Try again.\n"
#define BAD_RADIUS_ERROR        "Invalid radius. Try again.\n"
#define BAD_DATA_ERROR          "Invalid simulation data. Try again.\n"

int g_lasterror = 0;

int readLine( int fd, char *buffer, size_t maxlen )
{
    size_t pos;
    char temp_buffer[2];
    int retvalue;
    size_t rx_count;

    for ( pos = 1; pos < maxlen; pos++ )
    {
        if ( (retvalue = receive( fd, (void *)temp_buffer, 1, &rx_count)) != 0 )
        {
            g_lasterror = retvalue;
            return (-1);
        }
        else
        {
            if ( temp_buffer[0] == '\n' )
                break;

            buffer[0] = temp_buffer[0];
            buffer++;
        }
    }

    buffer[0] = '\0';
    return pos;
}

int parse_float_pair( const char *buf, double* pair1, double* pair2 )
{
    int pos;
    int buf_pos;
    char pair1_buf[1024];
    char pair2_buf[1024];

    // Split at comma
    for ( pos = 0; pos < 1024; pos++ )
    {
        if ( buf[pos] == '\0' )
            return -1;

        if ( buf[pos] == ',' )
            break;

        pair1_buf[pos] = buf[pos];
    }

    if ( pos == 1024 )
        return -1;

    pair1_buf[pos] = '\0';

    pos++;
    buf_pos = 0;
    for ( ; pos < 1024; pos++ )
    {
        if ( buf[pos] == '\0' )
            break;

        pair2_buf[buf_pos++] = buf[pos];
    }

    if ( pos == 1024 )
        return -1;

    pair2_buf[buf_pos] = '\0';

    *pair1 = atof( pair1_buf );
    *pair2 = atof( pair2_buf );

    return 0;
}

int main(void)
{
    char buf[1024];
    int ret;
    int i;

    // Print banner
    printf( BANNER_STR );

    ret = readLine( STDIN, buf, sizeof(buf) );
    if ( ret == -1 )
        _terminate(2);

    int32_t particle_count = atoi( buf );

    if ( particle_count == 0 )
    {
        printf( "Goodbye\n" );
        _terminate(0);
    }


    if ( particle_count > MAX_PARTICLE_COUNT )
    {
        printf( "Goodbye\n" );
        _terminate(3);
    }

    for ( i = 0; i < particle_count; )
    {
        double pos_x, pos_y;
        double vel_x, vel_y;
        double mass;
        double radius;
        int32_t particle_num;

        // Get position
        printf( PARTICLE_PROMPT_POSITION );

        ret = readLine( STDIN, buf, sizeof(buf) );
        if ( ret == -1 )
            _terminate(2);

        if ( parse_float_pair( buf, &pos_x, &pos_y ) != 0 )
        {
            printf( BAD_POSITION_ERROR );
            continue;
        }

        // Get velocity
        printf( PARTICLE_PROMPT_VELOCITY );

        ret = readLine( STDIN, buf, sizeof(buf) );
        if ( ret == -1 )
            _terminate(2);

        if ( parse_float_pair( buf, &vel_x, &vel_y ) != 0 )
        {
            printf( BAD_VELOCITY_ERROR );

            continue;
        }

        // Get mass
        printf( PARTICLE_PROMPT_MASS );

        ret = readLine( STDIN, buf, sizeof(buf) );
        if ( ret == -1 )
            _terminate(2);

        if ( (mass = atof( buf )) == 0.0 )
        {
            printf( BAD_MASS_ERROR );
            continue;
        }

        // Get radius
        printf( PARTICLE_PROMPT_RADIUS );

        ret = readLine( STDIN, buf, sizeof(buf) );
        if ( ret == -1 )
            _terminate(2);

        if ( (radius = atof( buf )) == 0.0 )
        {
            printf( BAD_RADIUS_ERROR );
            continue;
        }

        // Now attempt to add to the simulation (this will validate the data sets)
        if ( (particle_num = simulation_add_particle( pos_x, pos_y, vel_x, vel_y, mass, radius )) >= 0 )
        {
            // Particle added
            i++;
        }
        else
        {
            printf( BAD_DATA_ERROR );
            continue;
        }

        printf( "Particle #@d added at (@f,@f) velocity(@f,@f) mass(@f) radius(@f).\n", particle_num, pos_x, pos_y, vel_x, vel_y, mass, radius );
    }

    printf( "Running simulation with...\n" );
    // Initialize render grid
    init_render_grid();

    // Display start information
    display_simulation_data( );

    // Run the simulation for the desired amount of time
    simulation_run( 10 );

    // Print out simple statistics
    printf( "Simulation complete, @d collisions simulated over @d seconds in @d frames.\n", get_collision_count(), get_simulation_time(), get_simulation_frames() );

    // Output end information
    display_simulation_data( );

    // Exit
    printf( "Goodbye\n" );

    // Exit
    _terminate( 0 );
}
