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
#include "render.h"

tRenderGrid *g_renderGrid;
double g_render_delta_x;
double g_render_delta_y;

void init_render_grid( void )
{
    void *pMemory;
    uint32_t grid_x, grid_y;

    // Calculate render grid size
    uint32_t render_grid_elements = (RENDER_GRID_X_SIZE * RENDER_GRID_Y_SIZE);

    // Allocate elements for the render grid
    uint32_t render_grid_allocation_size = (render_grid_elements * sizeof(tRenderGrid));

    g_renderGrid = NULL;

    if ( allocate( render_grid_allocation_size, 0, &pMemory ) != 0 )
    {
        // Handle memory exceptions
        _terminate(1);
    }

    g_renderGrid = (tRenderGrid *)pMemory;

    double delta_x = ((SIMULATION_GRID_MAX_X - SIMULATION_GRID_MIN_X) / RENDER_GRID_X_SIZE);
    double delta_y = ((SIMULATION_GRID_MAX_Y - SIMULATION_GRID_MIN_Y) / RENDER_GRID_Y_SIZE);


    g_render_delta_x = delta_x;
    g_render_delta_y = delta_y;

    // Initialize grid
    for ( grid_x = 0; grid_x < RENDER_GRID_X_SIZE; grid_x++ )
        for ( grid_y = 0; grid_y < RENDER_GRID_Y_SIZE; grid_y++ )
        {
            uint32_t grid_position = (grid_x * RENDER_GRID_X_SIZE) + grid_y;

            // Start at bounds [0,0]
            double bounds_x = (SIMULATION_GRID_MIN_X) + (delta_x * grid_x);
            double bounds_y = (SIMULATION_GRID_MIN_Y) + (delta_y * grid_y);

            g_renderGrid[grid_position].bounds_x = bounds_x;
            g_renderGrid[grid_position].bounds_y = bounds_y;

            g_renderGrid[grid_position].particles_in_grid = 0;
        }
}

void clear_render_grid( void )
{
    uint32_t grid_x, grid_y;

    for ( grid_x = 0; grid_x < RENDER_GRID_X_SIZE; grid_x++ )
        for ( grid_y = 0; grid_y < RENDER_GRID_Y_SIZE; grid_y++ )
        {
            uint32_t grid_position = (grid_x * RENDER_GRID_X_SIZE) + grid_y;

            g_renderGrid[grid_position].particles_in_grid = 0;
        }
}

void add_render_grid( tParticleData *pItem )
{
    uint32_t x_pos = (uint32_t)(pItem->x_pos - SIMULATION_GRID_MIN_X);
    uint32_t y_pos = (uint32_t)(pItem->y_pos - SIMULATION_GRID_MIN_Y);

    // Find render grid location
    uint32_t render_grid_x = (x_pos / g_render_delta_x);
    uint32_t render_grid_y = (y_pos / g_render_delta_y);

#ifdef PATCHED
    if ( render_grid_x >= RENDER_GRID_X_SIZE || render_grid_y >= RENDER_GRID_Y_SIZE )
        return;
#endif

    // Increase particle count in that grid
    g_renderGrid[(render_grid_x * RENDER_GRID_X_SIZE) + render_grid_y].particles_in_grid++;
}

void display_render_grid( void )
{
    uint32_t grid_x, grid_y;

    for ( grid_y = 0; grid_y < RENDER_GRID_Y_SIZE; grid_y++ )
        printf( "-" );

    printf( "\n" );
    for ( grid_y = RENDER_GRID_Y_SIZE; grid_y > 0; grid_y-- )
    {
        for ( grid_x = 0; grid_x < RENDER_GRID_X_SIZE; grid_x++ )
        {
            uint32_t grid_position = (grid_x * RENDER_GRID_X_SIZE) + (grid_y-1);

            printf( "@d", g_renderGrid[grid_position].particles_in_grid );
        }

        printf( "\n" );
    }

    for ( grid_x = 0; grid_x < RENDER_GRID_X_SIZE; grid_x++ )
        printf( "-" );

    printf( "\n" );
}

