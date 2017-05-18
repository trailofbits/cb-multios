/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_gld.h"

// Global Variables
static qtree_t *g_conway_gld = NULL; //Conway's Game of Life and Death

/*** Forward Declarations ***/
static int cgc_qt_insert(qtree_t *qt, conway_pixel_t px);
static conway_pixel_t *cgc_qt_get_pixel(qtree_t *qt, coord_t point);
static qtree_t *cgc_qt_create(int max_level, region_t valid_region);
static int cgc_qt_delete(qtree_t*qt, conway_pixel_t px);
static int cgc_cg_step(int num_steps);
static int cgc_shoot_pixel(coord_t point);
static int cgc_set_bomb(coord_t point);

/*** Utility Functions ***/
static int cgc_within_region(coord_t point, region_t valid_region)
{
    return (point.x >= valid_region.start.x && point.x < valid_region.end.x &&
            point.y >= valid_region.start.y && point.y < valid_region.end.y);
}

static pixel_list_t *cgc_create_cell_list(qtree_t *qt, cell_filter_e filter)
{
    pixel_list_t *list = NULL, *temp = NULL;
    if (qt->is_subdivided) {
        temp = cgc_create_cell_list(qt->nw, filter);
        APPEND_LIST(pixel_list_t, list, temp);
        temp = cgc_create_cell_list(qt->ne, filter);
        APPEND_LIST(pixel_list_t, list, temp);
        temp = cgc_create_cell_list(qt->sw, filter);
        APPEND_LIST(pixel_list_t, list, temp);
        temp = cgc_create_cell_list(qt->se, filter);
        APPEND_LIST(pixel_list_t, list, temp);

        return list;
    }

    pixel_list_t *pixel = qt->pixels;
    while(pixel != NULL) {
        if (filter == LIVING_CELL && !pixel->px.is_alive);
        else if (filter == BOMB && !pixel->px.bomb_set);
        else if (filter == DEAD_CELL && (pixel->px.is_alive || pixel->px.bomb_set));
        else {
            temp = cgc_calloc(1, sizeof(pixel_list_t));
            temp->px = pixel->px;
            INSERT_ITEM(list, temp);
        }

        pixel = pixel->next;
    }

    return list;
}

coord_t *cgc_create_adjacent_coords(coord_t coord)
{
    coord_t *adj_cells = cgc_malloc(sizeof(coord_t) * 8);

    SET_COORD(adj_cells[0], coord.x - 1, coord.y - 1);
    SET_COORD(adj_cells[1], coord.x - 0, coord.y - 1);
    SET_COORD(adj_cells[2], coord.x + 1, coord.y - 1);
    SET_COORD(adj_cells[3], coord.x - 1, coord.y - 0);
    SET_COORD(adj_cells[4], coord.x + 1, coord.y - 0);
    SET_COORD(adj_cells[5], coord.x - 1, coord.y + 1);
    SET_COORD(adj_cells[6], coord.x - 0, coord.y + 1);
    SET_COORD(adj_cells[7], coord.x + 1, coord.y + 1);

    return adj_cells;
}

int cgc_bomb_collisions(pixel_list_t *bombs, pixel_list_t *living_cells)
{
    pixel_list_t *iter = NULL;
    conway_pixel_t *dead_cell;
    int i, total_score = 0, score = 0, cells_hit = 0;
    while (bombs != NULL) {
        score = 0;
        cells_hit = 0;
        if (bombs->px.bomb_set != 0) {
            bombs = bombs->next;
            continue;
        }

        coord_t *adj_cells = cgc_create_adjacent_coords(bombs->px.point);
        coord_t *bomb_cells = cgc_malloc(sizeof(coord_t) * 9);
        cgc_memcpy(bomb_cells, adj_cells, sizeof(coord_t) * 8);
        bomb_cells[8] = bombs->px.point;
        cgc_free(adj_cells);

        iter = living_cells;
        while (iter != NULL) {
            for (i = 0; i < 9; i++) {
                if (COORD_EQUALS(iter->px.point, bomb_cells[i])) {
                    // You get a multiplicative bonus for hitting multiple cells with 1 bomb
                    dead_cell = cgc_qt_get_pixel(g_conway_gld, bomb_cells[i]);
#ifdef PATCHED
                    if (dead_cell != NULL && dead_cell->is_alive) {
#else
                    if (dead_cell->is_alive) {
#endif
                        dead_cell->is_alive = FALSE;
                        cells_hit++;
                        score += 100 + cells_hit * score;

                        if (!dead_cell->bomb_set)
                            cgc_qt_delete(g_conway_gld, *dead_cell);
                    }

                    iter = iter->next;
                    break;
                }
            }

            if (i == 9)
                iter = iter->next;
        }

        bombs = bombs->next;
        cgc_free(bomb_cells);
        total_score += score;
    }

    return total_score;
}

static int cgc_is_dead_cell_generation(coord_t coord)
{
    coord_t *adj_cells = cgc_create_adjacent_coords(coord);
    conway_pixel_t *pixel;
    int i, num_living_cells = 0;
    for (i = 0; i < 8; i++) {
        pixel = cgc_qt_get_pixel(g_conway_gld, adj_cells[i]);
        if (pixel != NULL && pixel->is_alive)
            num_living_cells++;
    }
    cgc_free(adj_cells);

    if (num_living_cells == 3)
        return TRUE;

    return FALSE;
}

static void cgc_conway_step(conway_pixel_t cell, pixel_list_t **pgenerated_cells, pixel_list_t **pdeceased_cells,
                                coord_list_t **pchecked_coords)
{
    int i = 0, num_living_cells = 0;
    coord_list_t *cc_iter = *pchecked_coords;

    coord_t *adj_cells = cgc_create_adjacent_coords(cell.point);
    conway_pixel_t *pixel;

    pixel_list_t *generated_cell = NULL;
    coord_list_t *checked_coord = NULL;

    for (i = 0; i < 8; i++) {
        // Negative cells and out of bounds cells are not ignored
        if (adj_cells[i].x < 0 || adj_cells[i].y < 0 ||
            adj_cells[i].x > MAX_BOARD_WIDTH || adj_cells[i].y > MAX_BOARD_WIDTH)
           continue;

        //Skip cells we've already checked
        while (cc_iter != NULL) {
            if (COORD_EQUALS(adj_cells[i], cc_iter->coord))
                break;
            cc_iter = cc_iter->next;
        }

        pixel = cgc_qt_get_pixel(g_conway_gld, adj_cells[i]);
        if (pixel == NULL || !pixel->is_alive) {    //dead cell
            if (cc_iter != NULL)    //Already checked
                continue;

            checked_coord = cgc_calloc(1, sizeof(coord_list_t));
            checked_coord->coord = adj_cells[i];
            INSERT_ITEM((*pchecked_coords), checked_coord);

            if (cgc_is_dead_cell_generation(adj_cells[i])) {
                generated_cell = cgc_calloc(1, sizeof(pixel_list_t));
                if (pixel != NULL)
                    generated_cell->px = *pixel;
                else
                    generated_cell->px.point = adj_cells[i];
                generated_cell->px.is_alive = TRUE;
                INSERT_ITEM((*pgenerated_cells), generated_cell);
            }
        } else {
            num_living_cells++;
        }
    }

    checked_coord = cgc_calloc(1, sizeof(coord_list_t));
    checked_coord->coord = cell.point;
    INSERT_ITEM((*pchecked_coords), checked_coord);

    generated_cell = cgc_calloc(1, sizeof(pixel_list_t));
    generated_cell->px = cell;

    if (num_living_cells == 2 || num_living_cells == 3) {
        generated_cell->px.is_alive = TRUE;
        INSERT_ITEM((*pgenerated_cells), generated_cell);
    } else {
        generated_cell->px.is_alive = FALSE;
        INSERT_ITEM((*pdeceased_cells), generated_cell);
    }

    cgc_free(adj_cells);
}
/*** END UTILITY FUNCTIONS ***/

/***QUADTREE PRIVATE FUNCTIONS ***/
static qtree_t *cgc_find_subregion_tree(qtree_t *qt, coord_t p)
{
    if (!qt->is_subdivided)
        return NULL;

    if (cgc_within_region(p, qt->nw->valid_region))
        return qt->nw;
    if (cgc_within_region(p, qt->ne->valid_region))
        return qt->ne;
    if (cgc_within_region(p, qt->sw->valid_region))
        return qt->sw;
    if (cgc_within_region(p, qt->se->valid_region))
        return qt->se;

    return NULL;
}

static int cgc_subdivide(qtree_t*qt)
{
    if(qt->max_levels == 0)
        return -1; //should never get here

    region_t nw, ne, sw, se;
    unsigned int width = 1<<(qt->max_levels - 1);
    unsigned int startx = qt->valid_region.start.x, starty = qt->valid_region.start.y;
    unsigned int endx = qt->valid_region.end.x, endy = qt->valid_region.end.y;

    SET_REGION(nw, startx, starty, startx + width, starty + width);
    SET_REGION(ne, startx + width, starty, endx, starty + width);
    SET_REGION(sw, startx, starty + width, startx + width, endy);
    SET_REGION(se, startx + width, starty + width, endx, endy);

    qt->nw = cgc_qt_create(qt->max_levels - 1, nw);
    qt->ne = cgc_qt_create(qt->max_levels - 1, ne);
    qt->sw = cgc_qt_create(qt->max_levels - 1, sw);
    qt->se = cgc_qt_create(qt->max_levels - 1, se);
    qt->is_subdivided = TRUE;

    return 0;
}

static void cgc_move_pixels(qtree_t *qt, pixel_list_t *xfer_pixels, int num_pixels) {
    if (num_pixels == 0)
        return;       //Successfully copied 0

    APPEND_LIST(pixel_list_t, qt->pixels, xfer_pixels);
    qt->num_pixels += num_pixels;

}

static int cgc_qt_undivide(qtree_t *qt) {
    if (!qt->is_subdivided)
        return -1;

    //If any node is subdivided, there is n+1 objects --> no collapse
    if (qt->nw->is_subdivided || qt->ne->is_subdivided ||
        qt->sw->is_subdivided || qt->se->is_subdivided)
        return -1;

     if ((qt->num_pixels + qt->nw->num_pixels + qt->ne->num_pixels + qt->sw->num_pixels + qt->se->num_pixels) >
                qt->max_pixels)
        return -1;

    //Ready to undivide
    cgc_move_pixels(qt, qt->nw->pixels, qt->nw->num_pixels);
    cgc_move_pixels(qt, qt->ne->pixels, qt->ne->num_pixels);
    cgc_move_pixels(qt, qt->sw->pixels, qt->sw->num_pixels);
    cgc_move_pixels(qt, qt->se->pixels, qt->se->num_pixels);

    cgc_free(qt->nw);
    cgc_free(qt->ne);
    cgc_free(qt->sw);
    cgc_free(qt->se);

    qt->nw = NULL;
    qt->ne = NULL;
    qt->sw = NULL;
    qt->se = NULL;

    qt->is_subdivided = FALSE;

    return 0;
}

static int cgc_qt_delete(qtree_t *qt, conway_pixel_t px)
{
    if (!cgc_within_region(px.point, qt->valid_region))
        return -1;

    qtree_t *subtree = cgc_find_subregion_tree(qt, px.point);
    if (subtree != NULL) {
        if (cgc_qt_delete(subtree, px) == 0) {
            return cgc_qt_undivide(qt);
        } else {
            return -1;
        }
    }

    pixel_list_t *pixel = qt->pixels;
    while(pixel != NULL) {
        if (COORD_EQUALS(px.point, pixel->px.point)) {
            FREE_ITEM(qt->pixels, pixel);

            qt->num_pixels--;
            return 0;
        }

        pixel = pixel->next;
    }

    return -1;
}

static qtree_t *cgc_qt_create(int max_level, region_t valid_region)
{
    qtree_t *qt;
    qt = cgc_malloc(sizeof(qtree_t));
    qt->max_levels = max_level;
    qt->max_pixels = PIXELS_PER_TRIE;
    qt->num_pixels = 0;
    qt->pixels = NULL;

    qt->valid_region = valid_region;
    qt->is_subdivided = FALSE;

    // Functions
    qt->insert = cgc_qt_insert;
    qt->get_pixel = cgc_qt_get_pixel;
    qt->step = cgc_cg_step;
    qt->shoot_pixel = cgc_shoot_pixel;
    qt->set_bomb = cgc_set_bomb;

    qt->nw = NULL;
    qt->ne = NULL;
    qt->sw = NULL;
    qt->se = NULL;

    return qt;
}

/***END QUADTREE PRIVATE FUNCTIONS ***/

/*** QUADTREE MEMBER FUNCTIONS ***/
static int cgc_qt_insert(qtree_t *qt, conway_pixel_t px)
{
    if (!cgc_within_region(px.point, qt->valid_region))
        return -1;

    qtree_t *subtree = cgc_find_subregion_tree(qt, px.point);
    if (subtree != NULL)
        return cgc_qt_insert(subtree, px);

    pixel_list_t *pixel = qt->pixels;
    while(pixel != NULL) {
        if (COORD_EQUALS(px.point, pixel->px.point)) {
            pixel->px = px;
            return 0;           //Updated Pixel, no insert
        }

        pixel = pixel->next;
    }

    if (qt->num_pixels < qt->max_pixels) {
        pixel_list_t *new_pixel = cgc_calloc(1, sizeof(pixel_list_t));
        new_pixel->px = px;
        INSERT_ITEM(qt->pixels, new_pixel);

        qt->num_pixels++;
        return 0;
    } else {    //Subdivide and spread pixels accoss the nodes
       if (cgc_subdivide(qt) != 0)
            return -1;

        //Insert all existing pixels
        pixel = qt->pixels;
        while(pixel != NULL) {
            subtree = cgc_find_subregion_tree(qt, pixel->px.point);
            if (cgc_qt_insert(subtree, pixel->px) != 0)
                return -1;

            pixel = pixel->next;
        }
        FREE_LIST(pixel_list_t, qt->pixels);
        qt->pixels = NULL;
        qt->num_pixels = 0;

        //Finally - Insert the original pixel
        subtree = cgc_find_subregion_tree(qt, px.point);
        return cgc_qt_insert(subtree, px);
    }
}

static conway_pixel_t *cgc_qt_get_pixel(qtree_t *qt, coord_t point)
{
    if (!cgc_within_region(point, qt->valid_region))
        return NULL;

    qtree_t *subtree = cgc_find_subregion_tree(qt, point);
    if (subtree != NULL)
        return cgc_qt_get_pixel(subtree, point);

    pixel_list_t *pixel = qt->pixels;
    while(pixel != NULL) {
        if (COORD_EQUALS(point, pixel->px.point)) {
            return &pixel->px;
        }

        pixel = pixel->next;
    }

    return NULL;
}

static int cgc_cg_step(int num_steps) {
    int i, total_score = 0;
    pixel_list_t *bombs = NULL;
    pixel_list_t *living_cells = NULL;
    pixel_list_t *generated_cells = NULL;
    pixel_list_t *deceased_cells = NULL;
    coord_list_t *checked_coords = NULL;
    pixel_list_t *bombs_ordered = NULL, *temp = NULL;
    pixel_list_t *iter = NULL;

    for (i = 0; i < num_steps; i++) {
        living_cells = cgc_create_cell_list(g_conway_gld, LIVING_CELL);
        iter = living_cells;
        while(iter != NULL) {

            cgc_conway_step(iter->px, &generated_cells, &deceased_cells, &checked_coords);
            iter = iter->next;
        }
        FREE_LIST(pixel_list_t, living_cells);
        FREE_LIST(coord_list_t, checked_coords);

        iter = generated_cells;
        while(iter != NULL) {
            cgc_qt_insert(g_conway_gld, iter->px);
            iter = iter->next;
        }
        FREE_LIST(pixel_list_t, generated_cells);

        iter = deceased_cells;
        while(iter != NULL) {
            cgc_qt_insert(g_conway_gld, iter->px);
            iter = iter->next;
        }
        FREE_LIST(pixel_list_t, deceased_cells);

        bombs = cgc_create_cell_list(g_conway_gld, BOMB);
        iter = bombs;
        while (iter != NULL) {
            iter->px.bomb_set--;
            cgc_qt_insert(g_conway_gld, iter->px);

            temp = cgc_calloc(1, sizeof(pixel_list_t));
            temp->px = iter->px;
            INSERT_PIXEL_IN_ORDER((bombs_ordered), temp);
            iter = iter->next;
        }
        FREE_LIST(pixel_list_t, bombs);
        bombs = bombs_ordered;
        bombs_ordered = NULL;

        living_cells = cgc_create_cell_list(g_conway_gld, LIVING_CELL);
        total_score += cgc_bomb_collisions(bombs, living_cells);
        FREE_LIST(pixel_list_t, living_cells);
        FREE_LIST(pixel_list_t, bombs);

        deceased_cells = cgc_create_cell_list(g_conway_gld, DEAD_CELL);
        iter = deceased_cells;
        while(iter != NULL) {
            cgc_qt_delete(g_conway_gld, iter->px);
            iter = iter->next;
        }
        FREE_LIST(pixel_list_t, deceased_cells);
    }

    return total_score;
}

static int cgc_shoot_pixel(coord_t point)
{
    conway_pixel_t *dead_cell;
    dead_cell = cgc_qt_get_pixel(g_conway_gld, point);

    if (dead_cell != NULL && dead_cell->is_alive) {
        dead_cell->is_alive = FALSE;
        if(!dead_cell->bomb_set)
            cgc_qt_delete(g_conway_gld, *dead_cell);

        return 100;
    }

    return 0;
}

static int cgc_set_bomb(coord_t point)
{
    conway_pixel_t *bomb, new_bomb;
    bomb = cgc_qt_get_pixel(g_conway_gld, point);

    if (bomb == NULL) {
        new_bomb.point = point;
        new_bomb.is_alive = FALSE;
        new_bomb.bomb_set = 10;
        return (cgc_qt_insert(g_conway_gld, new_bomb) == 0);
    } else {
        if(!bomb->bomb_set) {
            bomb->bomb_set = 10;
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

/*** QUADTREE MEMBER FUNCTIONS ***/

/*** PUBLIC FUNCTIONS ***/
qtree_t *cgc_gld_init_game()
{
    if (g_conway_gld == NULL) {
        region_t valid_region;
        SET_REGION(valid_region, 0, 0, MAX_BOARD_WIDTH, MAX_BOARD_WIDTH);
        g_conway_gld = cgc_qt_create(MAX_LEVELS, valid_region);
    }

    return g_conway_gld;
}

void cgc_gld_clear_board()
{
    if(g_conway_gld == NULL)
        return;

    pixel_list_t *all_cells = cgc_create_cell_list(g_conway_gld, ALL), *iter;
    iter = all_cells;
    while(iter != NULL) {
        cgc_qt_delete(g_conway_gld, iter->px);
        iter = iter->next;
    }
    FREE_LIST(pixel_list_t, all_cells);
}

static void cgc_print_board_helper(qtree_t *qt, pixel_list_t **list)
{
    if (qt->is_subdivided) {
        cgc_print_board_helper(qt->nw, list);
        cgc_print_board_helper(qt->ne, list);
        cgc_print_board_helper(qt->sw, list);
        cgc_print_board_helper(qt->se, list);
    }

    pixel_list_t *pixel = qt->pixels, *temp;
    while(pixel != NULL) {
        if (pixel->px.is_alive || pixel->px.bomb_set) {
            temp = cgc_calloc(1, sizeof(pixel_list_t));
            temp->px = pixel->px;
            INSERT_PIXEL_IN_ORDER((*list), temp);
        }

        pixel = pixel->next;
    }
}

void cgc_gld_print_board(char *str)
{
    pixel_list_t *list = NULL, *iter = NULL;
    cgc_print_board_helper(g_conway_gld, &list);

    iter = list;
    cgc_printf("%s", str);
    while(iter != NULL) {
        cgc_printf("--| (x,y) = (%d,%d) | Alive=%d | Bomb=%d |\n",
                iter->px.point.x, iter->px.point.y, iter->px.is_alive, iter->px.bomb_set);
        iter = iter->next;
    }
    FREE_LIST(pixel_list_t, list);
}

void cgc_qt_debug_print_tree(qtree_t *qt, char *str) {
    if (qt == NULL)
        return;
    if(qt->num_pixels > 0) {
        cgc_printf("Level: %d, ID: %s\n", MAX_LEVELS - qt->max_levels, str);

        int i = 0;
        pixel_list_t *iter = qt->pixels;

        while(iter != NULL) {
            for(i = 0; i < MAX_LEVELS - qt->max_levels; i++)
                cgc_printf("    >");

            cgc_printf("--| (x,y) = (%d,%d) | Alive=%d | Bomb=%d |\n",
                    iter->px.point.x, iter->px.point.y, iter->px.is_alive, iter->px.bomb_set);
            iter = iter->next;
        }
    }

    cgc_qt_debug_print_tree(qt->nw, "NW");
    cgc_qt_debug_print_tree(qt->ne, "NE");
    cgc_qt_debug_print_tree(qt->sw, "SW");
    cgc_qt_debug_print_tree(qt->se, "SE");
}
