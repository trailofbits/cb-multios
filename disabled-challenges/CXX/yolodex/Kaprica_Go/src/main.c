/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include "cgc_ctype.h"
#include "cgc_stdint.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef enum action_t action_t;
enum action_t {
  AUNUSED = 0,
  PLAY,
  PASS
};

typedef enum color_t color_t;
enum color_t {
  CUNUSED = 0,
  BLACK,
  WHITE,
  EMPTY,
  OFF_BOARD
};

#define error(__status) cgc_exit(__status)

#define BOARD_DIM 19
#define NUM_PLAYERS 2
#define NUM_HISTORIES 16
#define SET_BOARD(board, x, y, pt) (board[y][x] = pt)
#define COLOR_STRING(c) (c == WHITE ? "White" : "Black")
#define OTHER_PLAYER(c) (c == WHITE ? BLACK : WHITE)

typedef color_t board_t[BOARD_DIM][BOARD_DIM];
typedef u8 sboard_t[BOARD_DIM][BOARD_DIM];

typedef u64 hash_t;

static u32 pcnt = 0;
static u64 prng_s = 0;
u64 cgc_prand(void)
{
  pcnt++;
  prng_s = prng_s * 1103515245 + 12345;
  return (u32)(prng_s / (2 << 15));
}

typedef struct hashl_t hashl_t;
struct hashl_t {
  hash_t hash;
  hashl_t* next;
};

static inline void INIT_LIST(hashl_t** list, hash_t hash)
{
  *list = cgc_calloc(1, sizeof(hashl_t));
  if (!list) error(1);
  (*list)->hash = hash;
  (*list)->next = *list;
}

static inline void EXTD_LIST(hashl_t* list, hash_t hash)
{
  hashl_t* new = cgc_calloc(1, sizeof(hashl_t));
  if (!new)
    error(1);
  for (; list->next != list; list = list->next)
    if (list->hash == hash)
      return;

  new->next = new;
  new->hash = hash;
  list->next = new;
}

static inline int CONT_LIST(hashl_t* list, hash_t hash)
{
  u32 cnt = 1;
  do {
    if (list->hash == hash) {
      return 1;
    } else if (list->next != list) {
      list = list->next;
      cnt++;
    } else {
      break;
    }
  } while (1);

  return 0;
}

typedef struct game_t game_t;
struct game_t {
  board_t board;
  u32 scores[NUM_PLAYERS];
  u32 caps[NUM_PLAYERS];
  u32 used[NUM_PLAYERS];
  u64 ticks;
  u8 passes;
  color_t current;
  hashl_t* history;
};

static hash_t ztable[BOARD_DIM * BOARD_DIM][NUM_PLAYERS];
int cgc_init_zobrist(void)
{
  for (u16 y = 0; y < BOARD_DIM * BOARD_DIM; y++) {
    for (u16 x = 0; x < NUM_PLAYERS; x++) {
      ztable[y][x] = cgc_prand();
    }
  }
  return 0;
}

hash_t cgc_hash_zobrist(board_t board)
{
  hash_t h = 0;
  for (u16 y = 0; y < BOARD_DIM * BOARD_DIM; y++) {
    if (board[y / BOARD_DIM][y % BOARD_DIM] != EMPTY) {
      h ^= ztable[y][board[y / BOARD_DIM][y % BOARD_DIM] - 1];
    }
  }
  return h;
}

void cgc_push_game_state(game_t* game) {
  hash_t h = cgc_hash_zobrist(game->board);
  EXTD_LIST(game->history, h);
}

static inline u64 abs(s32 x)
{
  return (x < 0) ? -x : x;
}

u8 cgc_ndigits(int x)
{
  if (x == 0)
    return 1;

  u8 n = 0;
  while (x) {
    x /= 10;
    n++;
  }
  return n;
}

game_t* cgc_init_game(board_t board)
{
  game_t* game = cgc_calloc(1, sizeof(game_t));
  if (!game)
    return NULL;

  if (board) {
    for (u32 y = 0; y < BOARD_DIM; y++) {
      for (u32 x = 0; x < BOARD_DIM; x++) {
        game->board[y][x] = board[y][x];
      }
    }
  } else {
    for (u32 y = 0; y < BOARD_DIM; y++) {
      for (u32 x = 0; x < BOARD_DIM; x++) {
        game->board[y][x] = EMPTY;
      }
    }
  }

  for (u32 i = 0; i < NUM_PLAYERS; i++) {
    game->scores[i] = 0;
    game->caps[i] = 0;
    game->used[i] = 0;
  }

  game->history = NULL;
  hash_t h = cgc_hash_zobrist(game->board);
  INIT_LIST(&game->history, h);
  game->ticks = 0;
  game->passes = 0;

  return game;
}

game_t* cgc_copy_game(game_t* game)
{
  game_t* copy = cgc_calloc(1, sizeof(game_t));
  if (!copy)
    error(1);
  cgc_memcpy(copy, game, sizeof(game_t));
  return copy;
}

color_t cgc_get_color(board_t board, u8 x, u8 y)
{
  if (x >= BOARD_DIM || x < 0 || y >= BOARD_DIM || y < 0)
    return OFF_BOARD;

  return board[y][x];
}

int cgc_has_liberty(game_t* game, sboard_t sboard, u8 x, u8 y, color_t color)
{
  color_t c = cgc_get_color(game->board, x, y);
  if (c == OFF_BOARD)
    return 0;
  if (sboard[y][x] == 1)
    return 0;

  color_t u = cgc_get_color(game->board, x, y + 1);
  color_t d = cgc_get_color(game->board, x, y - 1);
  color_t l = cgc_get_color(game->board, x - 1, y);
  color_t r = cgc_get_color(game->board, x + 1, y);

  sboard[y][x] = 1;
  if (u == EMPTY || d == EMPTY || l == EMPTY || r == EMPTY) {
    return 1;
  }

  if (u == color && cgc_has_liberty(game, sboard, x, y + 1, color)) {
    return 1;
  } else if (d == color && cgc_has_liberty(game, sboard, x, y - 1, color)) {
    return 1;
  } else if (l == color && cgc_has_liberty(game, sboard, x - 1, y, color)) {
    return 1;
  } else if (r == color && cgc_has_liberty(game, sboard, x + 1, y, color)) {
    return 1;
  }

  return 0;
}

u8 cgc_surrounded_by(game_t* game, sboard_t sboard, u8 x, u8 y, color_t color)
{
  if (!game || !sboard)
    error(1);

  color_t cur = cgc_get_color(game->board, x, y);
  if (cur == OFF_BOARD || sboard[y][x] == 1)
    return 1;

  if (cur == color) {
      sboard[y][x] = 1;
      return 2;
  } else if (cur == OTHER_PLAYER(color)) {
      sboard[y][x] = 1;
      return 0;
  } else if (cur == EMPTY) {
      sboard[y][x] = 1;
  }

  u8 u = cgc_surrounded_by(game, sboard, x, y + 1, color);
  u8 d = cgc_surrounded_by(game, sboard, x, y - 1, color);
  u8 l = cgc_surrounded_by(game, sboard, x + 1, y, color);
  u8 r = cgc_surrounded_by(game, sboard, x - 1, y, color);

  if (u + d + l + r > 4) {
    return 2;
  } else {
    return 0;
  }
}


int cgc_remove_captures(game_t* game, color_t color)
{
  u32 cnt = 0;
  sboard_t sboard;
  game_t* frozen = cgc_copy_game(game);
  for (u8 y = 0; y < BOARD_DIM; y++) {
    for (u8 x = 0; x < BOARD_DIM; x++) {
      cgc_memset(sboard, 0, sizeof(sboard));
      if (cgc_get_color(frozen->board, x, y) == color && !cgc_has_liberty(frozen, sboard, x, y, color)) {
        cnt++;
        SET_BOARD(game->board, x, y, EMPTY);
      }
    }
  }
  cgc_free(frozen);
  return cnt;
}

int cgc_has_happened(game_t* proposed, game_t* current)
{
  hash_t h = cgc_hash_zobrist(proposed->board);
  if (CONT_LIST(current->history, h)) {
    return 1;
  }
  return 0;
}

int cgc_score(game_t* game, u32* black, u32* white)
{
  sboard_t sboard;
  *black = game->caps[BLACK - 1];
  *white = game->caps[WHITE - 1];

  for (u8 y = 0; y < BOARD_DIM; y++) {
    for (u8 x = 0; x < BOARD_DIM; x++) {
      cgc_memset(sboard, 0, sizeof(sboard));
      color_t cur = cgc_get_color(game->board, x, y);
      if (cur == WHITE) {
        *white += 1;
        continue;
      } else if (cur == BLACK) {
        *black += 1;
        continue;
      }

      u8 s = cgc_surrounded_by(game, sboard, x, y, BLACK);
      if (s > 1) {
        *black += 1;
        continue;
      }

      s = cgc_surrounded_by(game, sboard, x, y, WHITE);
      if (s > 1) {
        *white += 1;
        continue;
      }
    }
  }

  return 0;
}

int cgc_check_and_play(game_t** game, u8 x, u8 y, color_t color, u8 play)
{
  if (color != EMPTY && (*game)->board[y][x] != EMPTY) {
    return -1;
  }


  game_t* simulated = cgc_copy_game(*game);
  SET_BOARD(simulated->board, x, y, color);
  u16 our_cap = cgc_remove_captures(simulated, OTHER_PLAYER(color));
  u16 thr_cap = cgc_remove_captures(simulated, color);

  if (cgc_has_happened(simulated, *game)) {
    cgc_free(simulated);
    return -1;
  } else if (play) {
    cgc_free(*game);
    *game = simulated;
    (*game)->used[color - 1]++;
    (*game)->caps[color - 1] += our_cap;
    (*game)->caps[OTHER_PLAYER(color) - 1] += thr_cap;
    return 0;
  } else {
    cgc_free(simulated);
    return 0;
  }
}

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30
#define BOARD_WIDTH 37

static inline void clear_screen(void)
{
  cgc_fdprintf(STDOUT, "\033[2J");
}

static inline void print_char(char color)
{
  cgc_fdprintf(STDOUT, "%c", color);
}

void cgc_print_rchar(char c, u8 r)
{
  for (u8 i = 0; i < r; i++)
    print_char(c);
}

void cgc_print_player(game_t* game, color_t color)
{
#define OFFSET 7
  cgc_fdprintf(STDOUT, "%s: %d", COLOR_STRING(color), game->scores[color - 1]);
  cgc_print_rchar(' ', (((SCREEN_WIDTH - BOARD_WIDTH) / 2) - OFFSET) - cgc_ndigits(game->scores[color - 1]));
}

void cgc_print_point(game_t* game, u8 x, u8 y)
{
  if (x != 0)
    print_char(' ');

  switch (cgc_get_color(game->board, x, y)) {
  case EMPTY:
    print_char('-');
    break;
  case WHITE:
    print_char('W');
    break;
  case BLACK:
    print_char('B');
    break;
  default:
    return;
  }

  if (x != BOARD_DIM - 1)
    print_char(' ');
  else
    print_char('\n');
}

void cgc_draw_game(game_t* game)
{
  //clear_screen();

  cgc_print_rchar('\n', (SCREEN_HEIGHT - BOARD_DIM) / 2);

  for (u32 y = 0; y < BOARD_DIM; y++) {
    if (abs(y - (BOARD_DIM / 2)) == 3) {
      cgc_print_player(game, y < BOARD_DIM / 2 ? WHITE : BLACK);
    } else if (y == BOARD_DIM / 2) {
      cgc_fdprintf(STDOUT, "Ticks: %u", game->ticks);
      cgc_print_rchar(' ', (((SCREEN_WIDTH - BOARD_WIDTH) / 2) - OFFSET)- cgc_ndigits(game->ticks));
    } else {
      cgc_print_rchar(' ', (SCREEN_WIDTH - BOARD_WIDTH) / 2);
    }
    for (u32 x = 0; x < BOARD_DIM; x++) {
      cgc_print_point(game, x, y);
    }
  }

  cgc_print_rchar('\n', (SCREEN_HEIGHT - BOARD_DIM) / 2);
}

void cgc_sleep(int s, int us)
{
  struct cgc_timeval t;
  t.tv_sec = s;
  t.tv_usec = us;
  cgc_fdwait(0, NULL, NULL, &t, NULL);
}

int cgc_read_n_bytes(int fd, cgc_size_t n, char *buf, int has_terminator, char terminator)
{
  if (!n || !buf)
    return -1;

  cgc_size_t rx = 0, total_read = 0;

  while (total_read < n) {
    if (cgc_receive(fd, buf + total_read, 1, &rx) != 0) {
      return -1;
    } else if (rx == 0) {
      break;
    } else {
      if (has_terminator && *(buf + total_read) == terminator) {
        *(buf + total_read) = '\0';
        break;
      }
      total_read += rx;
    }
  }

  return total_read;
}

int cgc_read_move(u8* x, u8* y, u8* pass)
{
#define INPUT_MAX 8
  int ret = -1;
  char buf[INPUT_MAX + 1];
  *pass = 0;
  cgc_memset(buf, 0, INPUT_MAX);
  cgc_read_n_bytes(STDIN, INPUT_MAX, buf, 1, '\n');
  buf[INPUT_MAX] = '\0';

  char* p = NULL;

  if (!cgc_strncmp("pass", buf, cgc_strlen("pass"))) {
    *pass = 1;
    ret = 0; goto out;
  }

  long n1 = cgc_strtol(buf, &p, 10);

  if (p == buf)
    goto out;

  if (p >= buf + INPUT_MAX)
    goto out;

  while (p && *p && p < buf + INPUT_MAX && !cgc_isdigit(*p))
    p++;

  long n2 = cgc_strtol(p, NULL, 10);

  if (n1 >= 0 && n1 < BOARD_DIM && n2 >= 0 && n2 < BOARD_DIM) {
    *x = n1;
    *y = n2;
    ret = 0; goto out;
  }
out:
  return ret;
}

void cgc_end_game(game_t* game, char *name, u8 reason)
{
  cgc_free(game);
  cgc_fdprintf(STDOUT, "Game Over ");
  switch (reason) {
  case 0:
    cgc_fdprintf(STDOUT, "Both Passed\n");
    break;
  case 1:
    cgc_fdprintf(STDOUT, "Game Time Exceeded\n");
    break;
  case 2:
    cgc_fdprintf(STDOUT, "Stones Exhausted\n");
    break;
  }

  cgc_fdprintf(STDOUT, "You are a ");
  cgc_fdprintf(STDOUT, ((game->scores[BLACK - 1] > game->scores[WHITE - 1])) ? "Winner, " : "Loser, ");
#ifdef PATCHED
  cgc_fdprintf(STDOUT, "%s", name);
#else
  cgc_fdprintf(STDOUT, name);
#endif

  cgc_exit(0);
  return;
}

void cgc_prompt_move(game_t* game, color_t color)
{
  cgc_fdprintf(STDOUT, "%d ", game->ticks);
  if (color == BLACK)
    cgc_fdprintf(STDOUT, "B >");
  else if (color == WHITE)
    cgc_fdprintf(STDOUT, "W >");
}

char* cgc_color_to_string(color_t c)
{
  switch (c) {
  case WHITE:
    return "White";
  case BLACK:
    return "Black";
  case EMPTY:
    return "Empty";
  case OFF_BOARD:
    return "Off";
  default:
    error(1);
  }

  return NULL;
}

int cgc_pass_for(game_t* game, color_t color)
{
  game->passes++;
  if (color == WHITE && game->passes > 1)
    return -1;
  return 0;
}

int cgc_interact(game_t** game, color_t color)
{
  u8 x, y, pass;

  cgc_prompt_move(*game, color);
  if (cgc_read_move(&x, &y, &pass) < 0) {
    return -1;
  }

  if (pass) {
    return cgc_pass_for(*game, color) < 0;
  }

  (*game)->passes = 0;
  if (cgc_check_and_play(game, x, y, color, 1) < 0) {
    return -1;
  }

  cgc_push_game_state(*game);
  return 0;
}

action_t cgc_calculate_move(game_t** game, u8* ox, u8* oy, color_t color)
{
  s32 vote, bvote = 0;
  u8 bx, by;
  sboard_t sboard;
  u32 chance;
  u8 gend = 0;

  for (u8 y = 0; y < BOARD_DIM; y++) {
    for (u8 x = 0; x < BOARD_DIM; x++) {
      vote = 0;
      cgc_memset(sboard, 0, sizeof(sboard));

      u8 neigh_cnt = 0;
      neigh_cnt += (cgc_get_color((*game)->board, x + 1, y) == color);
      neigh_cnt += (cgc_get_color((*game)->board, x - 1, y) == color);
      neigh_cnt += (cgc_get_color((*game)->board, x, y + 1) == color);
      neigh_cnt += (cgc_get_color((*game)->board, x, y - 1) == color);

      if (neigh_cnt == 4)
        vote -= 3;
      else if (neigh_cnt == 2)
        vote += 1;
      else if (neigh_cnt == 1)
        vote += 2;

      if (vote >= bvote) {
        if (cgc_check_and_play(game, x, y, color, 0) < 0) {
          continue;
        }

        chance = cgc_prand();
        if (chance % 100 > (vote == bvote ? 90 : 75)) {
          gend++;
          bx = x;
          by = y;
          bvote = vote;
          if (gend > 5)
            goto done;
        }
      }
    }
  }

done:
  if (!gend)
    return PASS;
  else {
    *ox = bx, *oy = by;
    return PLAY;
  }
}

int cgc_ai(game_t** game, color_t color)
{
  u8 x, y;
  switch (cgc_calculate_move(game, &x, &y, color)) {
    case PLAY:
      cgc_check_and_play(game, x, y, color, 1);
      cgc_push_game_state(*game);
      break;
    case PASS:
      (*game)->passes++;
      break;
    default:
      error(1);
  }

  return 0;
}

void cgc_pb(game_t* game)
{
  cgc_fdprintf(STDERR, "@@");
  for (u16 y = 0; y < BOARD_DIM; y++) {
    for (u16 x = 0; x < BOARD_DIM; x++) {
      cgc_fdprintf(STDERR, "%d", game->board[y][x]);
    }
  }
  cgc_fdprintf(STDERR, "\n");
}

int main(int cgc_argc, char *cgc_argv[])
{
#define NAME_LEN 8
  char name[NAME_LEN];
  int iret = -1;

  cgc_read_n_bytes(STDIN, sizeof(prng_s), (char *)&prng_s, 0, 0);
  if (cgc_init_zobrist() != 0)
    error(1);

  game_t* game = cgc_init_game(NULL);
  if (!game)
    error(1);

  cgc_fdprintf(STDOUT, "What is your name?\n");
  if (cgc_read_n_bytes(STDIN, NAME_LEN, name, 1, '\n') < 0) {
    cgc_printf("Need a name, bro\n");
    cgc_exit(1);
  }

  cgc_printf("Hi, %s\n", name);
  cgc_draw_game(game);
  while (1) {
    while (1) {
      int r = cgc_interact(&game, BLACK);
      if (r == -1) {
        continue;
      } else if (r == 0) {
        break;
      } else if (r == 1) {
        cgc_end_game(game, name, 0);
      }
    }

    cgc_score(game, &(game->scores[BLACK - 1]), &(game->scores[WHITE -1]));

    cgc_draw_game(game);
    cgc_ai(&game, WHITE);
    cgc_score(game, &(game->scores[BLACK - 1]), &(game->scores[WHITE - 1]));

#define MAX_STONES 90
#define MAX_TICKS 150
    game->ticks++;
    if (game->ticks > MAX_TICKS)
      cgc_end_game(game, name, 1);
    if (game->used[BLACK - 1] > MAX_STONES || game->used[WHITE - 1] > MAX_STONES)
      cgc_end_game(game, name, 2);
  }
}
