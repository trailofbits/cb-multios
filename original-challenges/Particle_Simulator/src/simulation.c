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

int32_t g_particleCount = 0;
uint32_t g_collisionTotal = 0;
uint32_t g_simulationTime = 0;
uint32_t g_simulationFrames = 0;

tParticleData g_particles[MAX_PARTICLE_COUNT];

#define fp_add( l, r )      (l+r)
#define fp_sub( l, r )      (l-r)
#define fp_mul( l, r )      (l*r)
#define fp_div( l, r )      (l/r)
#define fp_sqrt( l )        (sqrt(l))
#define fp_fconst( l )      ((double)l)
#define fp_iconst( l )      ((double)l)
#define fp_toint( l )       ((uint32_t)l)
#define fp_todouble( l )    ((double)l)

int32_t simulation_add_particle( double x_pos, double y_pos, double x_vel, double y_vel, double mass, double radius )
{
    uint32_t i;

    x_pos = ((double)((int32_t)(x_pos * 100))) / 100;
    y_pos = ((double)((int32_t)(y_pos * 100))) / 100;
    x_vel = ((double)((int32_t)(x_vel * 100))) / 100;
    y_vel = ((double)((int32_t)(y_vel * 100))) / 100;
    mass = ((double)((int32_t)(mass * 100))) / 100;
    radius = ((double)((int32_t)(radius * 100))) / 100;

    // Limit the number of particles in the simulation
    if ( g_particleCount >= MAX_PARTICLE_COUNT )
        return (-1);

    // Particle must be completely within the grid
    if ( !(x_pos < SIMULATION_GRID_MAX_X && x_pos > SIMULATION_GRID_MIN_X) )
        return -1;

    if ( !(y_pos < SIMULATION_GRID_MAX_Y && y_pos > SIMULATION_GRID_MIN_Y) )
        return -1;

    if ( !(x_vel <= PARTICLE_VELOCITY_MAX && x_vel >= PARTICLE_VELOCITY_MIN) )
        return -1;

    if ( !(y_vel <= PARTICLE_VELOCITY_MAX && y_vel >= PARTICLE_VELOCITY_MIN) )
        return -1;

    if ( !(mass <= PARTICLE_MASS_MAX && mass >= PARTICLE_MASS_MIN) )
        return -1;

    if ( !(radius <= PARTICLE_RADIUS_MAX && radius >= PARTICLE_RADIUS_MIN) )
        return -1;

    // Check to make sure the particle is not overlapping the simulation grid walls
    if ( (x_pos + radius) <= SIMULATION_GRID_MAX_X &&
         (x_pos - radius) >= SIMULATION_GRID_MIN_X &&
         (y_pos + radius) <= SIMULATION_GRID_MAX_Y &&
         (y_pos - radius) >= SIMULATION_GRID_MIN_Y )
        ; // Good
    else
        return -1;


    // Add this particle data to the simulation...
    g_particles[g_particleCount].x_pos = fp_fconst( x_pos );
    g_particles[g_particleCount].y_pos = fp_fconst( y_pos );
    g_particles[g_particleCount].x_vel = fp_fconst( x_vel );
    g_particles[g_particleCount].y_vel = fp_fconst( y_vel );
    g_particles[g_particleCount].mass = fp_fconst( mass );
    g_particles[g_particleCount].radius = fp_fconst( radius );

    // Check particle data to make sure it isn't colliding with another particle
    for ( i = 0; i < g_particleCount; i++ )
    {
        if ( is_colliding( &g_particles[i], &g_particles[g_particleCount]) )
                return -1;
    }

    // Finally add the particle
    g_particleCount++;

    return (g_particleCount);
}

void simulation_reset( void )
{
    g_particleCount = 0;
}

int32_t is_colliding( tParticleData *p1, tParticleData *p2 )
{
    // Perform collision detection between the two particles
    double x_delta = fp_sub( p1->x_pos, p2->x_pos );
    double y_delta = fp_sub( p1->y_pos, p2->y_pos );

    double radius_sum = fp_add( p1->radius, p2->radius );

    double dist_square = fp_add( fp_mul( x_delta, x_delta ), fp_mul(y_delta, y_delta) );

    double radius_sum_square = fp_mul(radius_sum, radius_sum);

    // Naive collision detection
    if ( dist_square < radius_sum_square )
        return 1;
    else
        return 0;
}

void do_collision( tParticleData *p1, tParticleData *p2 )
{
    // Collide the two particles in an elastic collision (vector math)
    double delta_x = fp_sub( p1->x_pos, p2->x_pos );
    double delta_y = fp_sub( p1->y_pos, p2->y_pos );

    double total_distance = fp_add( fp_mul( delta_x, delta_x ), fp_mul( delta_y, delta_y ) );

    double delta_length = fp_sqrt( total_distance );

    double radius_total = fp_add( p1->radius, p2->radius );

    double radius_scale = fp_div( radius_total, delta_length );
    radius_scale = fp_sub( radius_scale, fp_iconst(1) );

    double mtd_x = fp_mul( delta_x, radius_scale );
    double mtd_y = fp_mul( delta_y, radius_scale );

    double mass1 = p1->mass;
    double mass2 = p2->mass;

    double total_mass = fp_add( mass1, mass2 );

    double temp_mtdx_double = fp_mul( fp_iconst(2), mtd_x );
    double temp_mtdy_double = fp_mul( fp_iconst(2), mtd_y );

    double mass1_ratio = fp_div( mass2, total_mass );
    double mass2_ratio = fp_div( mass1, total_mass );

    double x_position_change1 = fp_mul( temp_mtdx_double, mass1_ratio );
    double y_position_change1 = fp_mul( temp_mtdy_double, mass1_ratio );

    double new_pos_1_x = fp_add( p1->x_pos, x_position_change1 );
    double new_pos_1_y = fp_add( p1->y_pos, y_position_change1 );

    double x_position_change2 = fp_mul( temp_mtdx_double, mass2_ratio );
    double y_position_change2 = fp_mul( temp_mtdy_double, mass2_ratio );

    double new_pos_2_x = fp_sub( p2->x_pos, x_position_change2 );
    double new_pos_2_y = fp_sub( p2->y_pos, y_position_change2 );

    // Apply new positions
    p1->x_pos = new_pos_1_x;
    p1->y_pos = new_pos_1_y;

    p2->x_pos = new_pos_2_x;
    p2->y_pos = new_pos_2_y;

    // Calculate velocity impulse from collision and apply
    double delta_velocity_x = fp_sub(p1->x_vel, p2->x_vel);
    double delta_velocity_y = fp_sub(p1->y_vel, p2->y_vel);

    double mtd_total_distance = fp_add( fp_mul( mtd_x, mtd_x ), fp_mul( mtd_y, mtd_y ) );

    if ( mtd_total_distance == 0 )
        mtd_total_distance = 1;

    double mtd_length = fp_sqrt( mtd_total_distance );

    double normal_mtd_x = fp_div( mtd_x, mtd_length );
    double normal_mtd_y = fp_div( mtd_y, mtd_length );

    // Find the dot product of the velocity vector and the normalized minimum translation distance vector (to apply to the velocity)
    double velocity_normal = fp_add( fp_mul(delta_velocity_x, normal_mtd_x), fp_mul(delta_velocity_y, normal_mtd_y));

    if ( velocity_normal >= fp_iconst(0) )
        return;     // Exit if the particles are moving away from each other already

    // Find the velocity impulse from the collision
    double impulse = fp_mul( fp_iconst(-2), velocity_normal );

    double impulse_x = fp_mul( normal_mtd_x, impulse );
    double impulse_y = fp_mul( normal_mtd_y, impulse );

    // Calculate new velocity's
    double new_vel_1_x = fp_add( p1->x_vel, fp_mul( impulse_x, mass1_ratio ) );
    double new_vel_1_y = fp_add( p1->y_vel, fp_mul( impulse_y, mass1_ratio ) );

    double new_vel_2_x = fp_sub( p2->x_vel, fp_mul( impulse_x, mass2_ratio ) );
    double new_vel_2_y = fp_sub( p2->y_vel, fp_mul( impulse_y, mass2_ratio ) );

    // Apply velocities
    //
    p1->x_vel = new_vel_1_x;
    p1->y_vel = new_vel_1_y;

    p2->x_vel = new_vel_2_x;
    p2->y_vel = new_vel_2_y;
}

void do_wall_collision( tParticleData *p1 )
{

    double x_position_high = fp_add( p1->x_pos, p1->radius );
    double x_position_low = fp_sub( p1->x_pos, p1->radius );
    double y_position_high = fp_add( p1->y_pos, p1->radius );
    double y_position_low = fp_sub( p1->y_pos, p1->radius );

    // CHECK MAX X COLLISION
    if ( x_position_high > fp_iconst(SIMULATION_GRID_MAX_X) )
    {
        // MAX X COLLISION
        double mtd_x = fp_sub( x_position_high, fp_iconst(SIMULATION_GRID_MAX_X) );

        double new_x_pos = fp_sub( p1->x_pos, fp_mul( fp_iconst(2), mtd_x ) );

        p1->x_pos = new_x_pos;

        // VELOCITY (apply velocity translation only if it isn't already moving away)
        if ( p1->x_vel > 0 )
            p1->x_vel = -p1->x_vel;
    }

    // CHECK MIN X COLLISION
    if ( x_position_low < fp_iconst(SIMULATION_GRID_MIN_X) )
    {
        // MIN X COLLISION
        double mtd_x = fp_sub( fp_iconst(SIMULATION_GRID_MIN_X), x_position_low );

        double new_x_pos = fp_add( p1->x_pos, fp_mul( fp_iconst(2), mtd_x ) );

        p1->x_pos = new_x_pos;

        // VELOCITY (apply velocity translation only if it isn't already moving away)
        if ( p1->x_vel < 0 )
            p1->x_vel = -p1->x_vel;
    }

    // CHECK MAX Y COLLISION
    if ( y_position_high > fp_iconst(SIMULATION_GRID_MAX_Y) )
    {
        // MAX Y COLLISION
        double mtd_y = fp_sub( y_position_high, fp_iconst(SIMULATION_GRID_MAX_Y) );

        double new_y_pos = fp_sub( p1->y_pos, fp_mul( fp_iconst(2), mtd_y ) );

        p1->y_pos = new_y_pos;

        // VELOCITY (apply velocity translation only if it isn't already moving away)
        if ( p1->y_vel > 0 )
            p1->y_vel = -p1->y_vel;
    }

    if ( y_position_low < fp_iconst(SIMULATION_GRID_MIN_Y) )
    {
        // MIN Y COLLISION
        double mtd_y = fp_sub( fp_iconst(SIMULATION_GRID_MIN_Y), y_position_low );

        double new_y_pos = fp_add( p1->y_pos, fp_mul( fp_iconst(2), mtd_y) );

        p1->y_pos = new_y_pos;

        // VELOCITY (apply velocity translation only if it isn't already moving away)
        if ( p1->y_vel < 0 )
            p1->y_vel = -p1->y_vel;
    }
}


void simulation_run( uint32_t second_count )
{
    uint32_t i,j;
    uint32_t last_frames_per_second;
    uint32_t frames_remaining;
    uint32_t cur_frame;
    uint32_t collision_count;

    frames_remaining = (1 * second_count);
    last_frames_per_second = 1;

    // Reset the collision counter
    g_collisionTotal = 0;

    g_simulationTime = second_count;
    g_simulationFrames = 0;

    // Start at 1 frame per second
    last_frames_per_second = 1;

    for ( cur_frame = 0; cur_frame < frames_remaining; cur_frame++ )
    {

    uint32_t max_frames_per_second = 1;
    uint32_t frames_per_second = 1;
    for ( i = 0; i < g_particleCount; i++ )
    {
        if ( fabs( g_particles[i].x_vel ) > g_particles[i].radius )
            frames_per_second = ((uint32_t)fp_toint( fp_div( fabs(g_particles[i].x_vel), g_particles[i].radius ))) + 1;

        if ( frames_per_second > max_frames_per_second )
            max_frames_per_second = frames_per_second;

        if ( fabs( g_particles[i].y_vel ) > g_particles[i].radius )
            frames_per_second = ((uint32_t)fp_toint( fp_div( fabs(g_particles[i].y_vel), g_particles[i].radius))) + 1;

        if ( frames_per_second > max_frames_per_second )
            max_frames_per_second = frames_per_second;
    }

    // Run the simulation for the specified number of seconds
    // Break the simulation into frames/second based on the velocity of the particles relative
    // to there radius (this way a particle cannot translate beyond half its radius in a frame)
    while ( max_frames_per_second > last_frames_per_second )
    {
        // Increase the number of frames per second for the simulation to
        // prevent objects from translating fast than their radius
        last_frames_per_second *= 2;

        frames_remaining *= 2;
    }


    // Translate (move) particles based on the frames per second
    for ( i = 0; i < g_particleCount; i++ )
    {
        double fp_frames_per_second = fp_iconst( last_frames_per_second );

        double temp_x_vel = fp_div(g_particles[i].x_vel, fp_frames_per_second);
        double temp_y_vel = fp_div(g_particles[i].y_vel, fp_frames_per_second);

        g_particles[i].x_pos = fp_add( g_particles[i].x_pos, temp_x_vel );
        g_particles[i].y_pos = fp_add( g_particles[i].y_pos, temp_y_vel );
    }

    // COLLISION DETECTION
    collision_count = 0;
    for ( i = 0; i < g_particleCount; i++ )
    {
        for ( j = 0; j < g_particleCount; j++ )
        {
            if ( i == j )
                continue;

            if ( is_colliding( &g_particles[i], &g_particles[j] ) )
            {
                do_collision( &g_particles[i], &g_particles[j] );

                collision_count++;
            }
        }

        do_wall_collision( &g_particles[i] );
    }
    g_collisionTotal += collision_count;

    }

    // Remember the number of frames simulated for statistics
    g_simulationFrames = cur_frame;
}

uint32_t get_collision_count( void )
{
    return (g_collisionTotal);
}

uint32_t get_simulation_time( void )
{
    return (g_simulationTime);
}

uint32_t get_simulation_frames( void )
{
    return (g_simulationFrames);
}

void display_simulation_data( void )
{
    uint32_t i;

    // Reset render grid
    clear_render_grid();

    printf( "@d total particles:\n", g_particleCount );

    for ( i = 0; i < g_particleCount; i++ )
    {
        double x_pos = fp_todouble( g_particles[i].x_pos );
        double y_pos = fp_todouble( g_particles[i].y_pos );
        double x_vel = fp_todouble( g_particles[i].x_vel );
        double y_vel = fp_todouble( g_particles[i].y_vel );
        double mass = fp_todouble( g_particles[i].mass );
        double radius = fp_todouble( g_particles[i].radius );

        printf( "@d: Position (@f,@f) Velocity (@f,@f) mass (@f) radius (@f).\n", i, x_pos, y_pos, x_vel, y_vel, mass, radius );

        // Add particle into render grid
        add_render_grid( &g_particles[i] );
    }

    display_render_grid();
}
