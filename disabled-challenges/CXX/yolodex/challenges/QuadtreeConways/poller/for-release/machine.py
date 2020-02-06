from generator.actions import Actions
import random
import string
import struct
import ctypes
import sys

MAX_BOARD_WIDTH = 8192
NUM_RUNNERS = 25
NUM_STEPS = 10000
NUM_BOMBS = 5
NUM_SHOTS = 125

class ConwayPixel():
    def __init__(self, x=-1, y=-1, is_alive=0, bomb_set=0):
        self.x = x
        self.y = y
        self.is_alive = is_alive
        self.bomb_set = bomb_set

    def __eq__(self, b):
        if isinstance(b, ConwayPixel):
            return (self.x == b.x and self.y == b.y and self.is_alive == b.is_alive and self.bomb_set == b.bomb_set)
        return False

    def __hash__(self):
        return hash((self.x, self.y, self.is_alive, self.bomb_set))

def get_adjacent_coords_set(x,y):
    coords = [(x-1, y-1), (x, y-1), (x+1, y-1), (x-1, y), (x+1, y), (x-1, y+1), (x, y+1), (x+1, y+1)]
    coords_set = set()
    for (cx, cy) in coords:
        if cx < MAX_BOARD_WIDTH and cy < MAX_BOARD_WIDTH:
            coords_set.add((cx, cy))

    return coords_set

def random_seed():
    return random.randint(1, 4294967295)

def random_steps():
    return random.randint(100,1000)

def random_coordinate():
    x = random.randint(0, 8192 - 1)
    y = random.randint(0, 8192 - 1)

    return (x,y)

class GameOfLifeAndDeath(Actions):
    new_seed_text = ("Before we begin. Enter a number [1 - 4294967295]\n" +
                     "Or any number. We'll figure it out: ")

    game_ended_menu = ("                              --GAME OVER--\n" +
                       "1. New Game\n" +
                       "2. Quit\n\n")

    board_hidden_menu = ("                              --Board: HIDDEN--\n" +
                         "1. Shoot!\n" +
                         "2. Reveal Board\n" +
                         "3. New Game\n" +
                         "4. Quit\n")

    board_revealed_menu = ("                              --Board: REVEALED--\n" +
                           "1. Place Bomb\n" +
                           "2. Reveal Board\n" +
                           "3. Let them Run!\n" +
                           "4. New Game\n" +
                           "5. Quit\n")

    shoot_coordinate_text = "Enter Shot Coordinates Ex: 100, 100:: "
    bomb_coordinate_text = "Enter Bomb Coordinates Ex: 100, 100:: "

    shot_miss_text = "You missed. Better luck next time.\n"
    shot_empty_text = "You're out of bullets.\n"
    shot_hit_text = ("Great shot! You got one\n" +
                     "Scored: 100 points\n")

    bomb_planted_text = "Successfully planted bomb.\n"
    bomb_empty_text = "You're out of bombs.\n"
    bomb_failed_text= "There is already a bomb here. Try somewhere else.\n"

    run_steps_text = "Enter amount of time to run: [100-1000]:: "
    new_game_text = "New Game -- Ready, set, go!\n"
    high_score_text = "A new high score!!\n\n"
    game_over_text = "GAME OVER!\n"
    exit_text = "Thanks for Playing\nEXITING...\n"

    def _read(self, string):
        self.read(length=len(string), expect=string)

    def _read_menu(self):
        if self.steps_left <= 0:
            menu = self.game_ended_menu
            self._read(menu)
            self._read_highscore()
        else:
            if self.state['board_revealed']:
                menu = self.board_revealed_menu
            else:
                menu = self.board_hidden_menu

            self._read(menu)
            self._read_game_info()

        self._read("Selection-: ")

    def _read_highscore(self):
        self._read("High Score = {0}\n\n".format(self.high_score))

    def _read_game_info(self):
        self._read("Current Score = {0} | Total Time Remaining: {1} | High Score = {2} \n".format(
                    self.current_score, self.steps_left, self.high_score))
        self._read("Shots Remaining: {0} | Bombs Remaining: {1}\n\n".format(
                    self.shots_left, self.bombs_left))

    def _living_pixels_append(self, pixel):
        if pixel.x < 0 or pixel.y < 0 or pixel.x >= MAX_BOARD_WIDTH or pixel.y >= MAX_BOARD_WIDTH:
            pass
        else:
            self.living_pixels.append(pixel)


    def _bomb_pixels_append(self, pixel):
        if pixel.x < 0 or pixel.y < 0 or pixel.x >= MAX_BOARD_WIDTH or pixel.y >= MAX_BOARD_WIDTH:
            pass
        else:
            self.bomb_pixels.append(pixel)

    def _place_runner(self, x, y):
        self._living_pixels_append(ConwayPixel(x, y, 1))
        if (x < MAX_BOARD_WIDTH/2 and y < MAX_BOARD_WIDTH/2):
            self._living_pixels_append(ConwayPixel(x, y+1, 1))
            self._living_pixels_append(ConwayPixel(x, y+2, 1))
            self._living_pixels_append(ConwayPixel(x-1, y+2, 1))
            self._living_pixels_append(ConwayPixel(x-2, y+1, 1))
        elif (x >= MAX_BOARD_WIDTH/2 and y < MAX_BOARD_WIDTH/2):
            self._living_pixels_append(ConwayPixel(x, y+1, 1))
            self._living_pixels_append(ConwayPixel(x, y+2, 1))
            self._living_pixels_append(ConwayPixel(x+1, y+2, 1))
            self._living_pixels_append(ConwayPixel(x+2, y+1, 1))
        elif (x < MAX_BOARD_WIDTH/2 and y >= MAX_BOARD_WIDTH/2):
            self._living_pixels_append(ConwayPixel(x, y+1, 1))
            self._living_pixels_append(ConwayPixel(x, y+2, 1))
            self._living_pixels_append(ConwayPixel(x-1, y, 1))
            self._living_pixels_append(ConwayPixel(x-2, y+1, 1))
        elif (x >= MAX_BOARD_WIDTH/2 and y >= MAX_BOARD_WIDTH/2):
            self._living_pixels_append(ConwayPixel(x, y+1, 1))
            self._living_pixels_append(ConwayPixel(x, y+2, 1))
            self._living_pixels_append(ConwayPixel(x+1, y, 1))
            self._living_pixels_append(ConwayPixel(x+2, y+1, 1))

        self.living_pixels = list(set(self.living_pixels))


    def _rand_int(self):
        temp = self.a ^ ctypes.c_uint32(self.a << 11).value
        self.a = self.b
        self.b = self.c
        self.c = self.d
        self.d = ctypes.c_uint32((self.d ^ (self.d >> 19)) ^ (temp ^ (temp >> 8))).value
        return self.d


    def _create_runner(self):
        temp = 0
        x = -1
        y = -1

        x = self._rand_int() % MAX_BOARD_WIDTH
        y = self._rand_int() % MAX_BOARD_WIDTH
        self._place_runner(x, y)

    def _take_shot(self, x, y):
        if self.shots_left == 0:
            self._read(self.shot_empty_text)
            return

        self.shots_left -= 1
        for i in xrange(len(self.living_pixels)):
            if self.living_pixels[i].x == x and self.living_pixels[i].y == y:
                self.living_pixels.pop(i)
                self.current_score += 100
                self._read(self.shot_hit_text)
                return

        self._read(self.shot_miss_text)

    def _plant_bomb(self, x, y):
        if self.bombs_left == 0:
            self._read(self.bomb_empty_text)
            return

        for bomb in self.bomb_pixels:
            if bomb.x == x and bomb.y == y:
                self._read(self.bomb_failed_text)
                return

        self.bombs_left -= 1
        self._bomb_pixels_append(ConwayPixel(x, y, 0, 10))
        self._read(self.bomb_planted_text)

    def _read_pixels_in_order(self):
        ordered = sorted(self.living_pixels + self.bomb_pixels, key=lambda px: (px.x, px.y))

        self._read("GAME BOARD\n")
        for i in ordered:
            self._read("--| (x,y) = ({0},{1}) | Alive={2} | Bomb={3} |\n".format(i.x, i.y, i.is_alive, i.bomb_set))
        self._read("\n")

    #Main functionality:
    def _bomb_collisions(self):
        total_score = 0
        ordered = sorted(self.bomb_pixels, key=lambda px: (px.x, px.y))
        for bomb in ordered:
            bomb.bomb_set -= 1
            if bomb.bomb_set != 0:
                continue

            score = 0
            pixels_hit = 0
            living_pixels_set = self._get_living_pixels_set()
            adj_coords_set = get_adjacent_coords_set(bomb.x, bomb.y)
            adj_coords_set.add((bomb.x, bomb.y))

            bombed_pixels = living_pixels_set & adj_coords_set

            for i in reversed(xrange(len(self.living_pixels))):
                for (x,y) in bombed_pixels:
                    if self.living_pixels[i].x == x and self.living_pixels[i].y == y:
                        self.living_pixels.pop(i)
                        pixels_hit += 1
                        score += 100 + pixels_hit * score

            total_score += score

        for i in reversed(xrange(len(self.bomb_pixels))):
            if self.bomb_pixels[i].bomb_set == 0:
                self.bomb_pixels.pop(i)

        return total_score

    def _get_living_pixels_set(self):
        living_pixel_set = set()
        for living_pixel in self.living_pixels:
            living_pixel_set.add((living_pixel.x, living_pixel.y))

        return living_pixel_set

    def _run_single_generation(self):
        dead_pixels_to_check = set()
        next_gen_pixels = []
        living_pixels_set = self._get_living_pixels_set()

        for pixel in self.living_pixels:
            adj_live_pixels = 0
            adj_coords_set = get_adjacent_coords_set(pixel.x, pixel.y)

            adj_living_pixels = living_pixels_set & adj_coords_set
            if len(adj_living_pixels) == 2 or len(adj_living_pixels) == 3:
                next_gen_pixels.append(pixel)

            dead_pixels_to_check |= adj_coords_set - living_pixels_set

        for (deadx, deady) in dead_pixels_to_check:
            adj_coords_set = get_adjacent_coords_set(deadx, deady)
            adj_living_pixels = living_pixels_set & adj_coords_set
            if len(adj_living_pixels) == 3:
                next_gen_pixels.append(ConwayPixel(deadx, deady, 1))

        self.living_pixels = list(set(next_gen_pixels))

    def _new_game(self):
        self.high_score = self.current_score if self.high_score < self.current_score else self.high_score

        self.living_pixels = []
        self.bomb_pixels = []

        for x in xrange(NUM_RUNNERS):
            self._create_runner()

        self.state['board_revealed'] = False
        self.current_score = 0
        self.steps_left = NUM_STEPS
        self.shots_left = NUM_SHOTS
        self.bombs_left = NUM_BOMBS
        self._read(self.new_game_text)

    def start(self):
        self.a = ctypes.c_uint32(111111111).value
        self.b = ctypes.c_uint32(222222222).value
        self.c = ctypes.c_uint32(333333333).value
        self.d = ctypes.c_uint32(444444444).value

        self.high_score = 0
        self.current_score = 0
        self.seed = str(random_seed())
        self.a = ctypes.c_uint32(int(self.seed)).value

        self._read(self.new_seed_text)
        self.write(self.seed + '\n')
        self._new_game()

    def shoot(self):
        self._read_menu()
        self.write("1\n")
        self.read(self.shoot_coordinate_text)
        x, y = random_coordinate()
        self.write("{0}, {1}\n".format(x, y))
        self._take_shot(x,y)

    def reveal_board(self):
        self._read_menu()
        self.write("2\n")
        self._read_pixels_in_order()
        self.state['board_revealed'] = True

    def place_bomb(self):
        self._read_menu()
        self.write("1\n")
        self._read(self.bomb_coordinate_text)
        x, y = random_coordinate()
        self.write("{0}, {1}\n".format(x, y))
        self._plant_bomb(x,y)

    def let_run(self):
        score = 0
        self._read_menu()
        self.write("3\n")
        self._read(self.run_steps_text)
        num_steps = random_steps()
        self.write("{0}\n".format(num_steps))

        num_steps = self.steps_left if self.steps_left <= num_steps else num_steps
        for x in xrange(num_steps):
            self._run_single_generation()
            score += self._bomb_collisions()

        self.current_score += score
        if score != 0:
            score_str = "Nice bombing! You racked up {0} points.\n".format(score)
            self._read(score_str)

        if (self.steps_left <= num_steps):
            self.steps_left = 0
            self._read(self.game_over_text)
            if(self.current_score > self.high_score):
                self._read(self.high_score_text)
            self._read_menu()
            self.write("1\n")
        else:
            self.steps_left -= num_steps

        self.state['board_revealed'] = False

    def new_game(self):
        self._read_menu()
        if self.state['board_revealed']:
            self.write("4\n")
        else:
            self.write("3\n")

        self._new_game()

    def quit(self):
        self._read_menu()
        if self.state['board_revealed']:
            self.write("5\n")
        else:
            self.write("4\n")

        self._read(self.exit_text)
