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
#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <stdint.h>

typedef struct PARTICLE_DATA_STRUCT
{
    double x_pos, y_pos;
    double x_vel, y_vel;
    double mass;
    double radius;
} tParticleData;

#define SIMULATION_GRID_MAX_X       (200)
#define SIMULATION_GRID_MIN_X       (100)
#define SIMULATION_GRID_MAX_Y       (200)
#define SIMULATION_GRID_MIN_Y       (100)

#define PARTICLE_MASS_MAX           (10)
#define PARTICLE_MASS_MIN           (1)

// Minimum and maximum velocities for any component (x or y)
#define PARTICLE_VELOCITY_MAX       (10)
#define PARTICLE_VELOCITY_MIN       (-10)

// Maximum number of particles in the simulation
#define MAX_PARTICLE_COUNT          (10)

// Particle radius maximum and minimum
#define PARTICLE_RADIUS_MIN         (1)
#define PARTICLE_RADIUS_MAX         (10)

int32_t simulation_add_particle( double x_pos, double y_pos, double x_vel, double y_vel, double mass, double radius );
void simulation_reset( void );
int32_t is_colliding( tParticleData *p1, tParticleData *t2 );
void do_collision( tParticleData *p1, tParticleData *t2 );
void do_wall_collision( tParticleData *p1 );
void simulation_run( uint32_t second_count );

void display_simulation_data( void );
uint32_t get_collision_count( void );
uint32_t get_simulation_time( void );
uint32_t get_simulation_frames( void );

#endif
