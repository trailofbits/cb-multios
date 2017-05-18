/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "cgc_joke.h"

// load default jokes into joke storage
void cgc_load_default_jokes(jokedb_struct *jokedb) {

	cgc_insert_joke(jokedb, "When Alexander Bell invented the telephone he had 3 missed calls from Chuck Norris.");
	cgc_insert_joke(jokedb, "Fear of spiders is aracnaphobia, fear of tight spaces is chlaustraphobia, fear of Chuck Norris is called Logic");
	cgc_insert_joke(jokedb, "There used to be a street named after Chuck Norris, but it was changed because nobody crosses Chuck Norris and lives.");
	cgc_insert_joke(jokedb, "Chuck Norris has a grizzly bear carpet in his room. The bear isn't dead it is just afriad to move.");
	cgc_insert_joke(jokedb, "Chuck Norris died 20 years ago, Death just hasn't built up the courage to tell him yet.");
	cgc_insert_joke(jokedb, "Chuck Norris has already been to Mars; that's why there are no signs of life.");
	cgc_insert_joke(jokedb, "Chuck Norris doesn't call the wrong number. You answer the wrong phone.");
	cgc_insert_joke(jokedb, "Some magicans can walk on water, Chuck Norris can swim through land.");
	cgc_insert_joke(jokedb, "Chuck Norris and Superman once fought each other on a bet. The loser had to start wearing his underwear on the outside of his pants.");
	cgc_insert_joke(jokedb, "Chuck Norris once urinated in a semi truck's gas tank as a joke....that truck is now known as Optimus Prime.");
	cgc_insert_joke(jokedb, "Chuck Norris can cut through a hot knife with butter");
	cgc_insert_joke(jokedb, "Chuck Norris counted to infinity - twice.");
	cgc_insert_joke(jokedb, "Chuck Norris is the reason why Waldo is hiding.");
	cgc_insert_joke(jokedb, "When the Boogeyman goes to sleep every night, he checks his closet for Chuck Norris.");
	cgc_insert_joke(jokedb, "Death once had a near-Chuck Norris experience");
	cgc_insert_joke(jokedb, "Chuck Norris can slam a revolving door.");
	cgc_insert_joke(jokedb, "Chuck Norris once kicked a horse in the chin. Its decendants are known today as Giraffes.");
	cgc_insert_joke(jokedb, "Chuck Norris will never have a heart attack. His heart isn't nearly foolish enough to attack him.");
	cgc_insert_joke(jokedb, "Chuck Norris can win a game of Connect Four in only three moves.");
	cgc_insert_joke(jokedb, "Chuck Norris once got bit by a rattle snake........ After three days of pain and agony ..................the rattle snake died");
	cgc_insert_joke(jokedb, "There is no theory of evolution. Just a list of animals Chuck Norris allows to live.");
	cgc_insert_joke(jokedb, "Chuck Norris can light a fire by rubbing two ice-cubes together.");
	cgc_insert_joke(jokedb, "When Chuck Norris does a pushup, he isn't lifting himself up, he's pushing the Earth down.");
	cgc_insert_joke(jokedb, "Chuck Norris is so fast, he can dodge raindrops.");
	cgc_insert_joke(jokedb, "Chuck Norris doesn't wear a watch. HE decides what time it is.");
	cgc_insert_joke(jokedb, "The original title for Alien vs. Predator was Alien and Predator vs Chuck Norris.");
	cgc_insert_joke(jokedb, "Chuck Norris doesn't read books. He stares them down until he gets the information he wants.");
	cgc_insert_joke(jokedb, "If Chuck Norris were to ever run out of ammo, his weapon would continue to fire out of fear of disappointing Chuck Norris.");
	cgc_insert_joke(jokedb, "Chuck Norris' hand is the only hand that can beat a Royal Flush.");
	cgc_insert_joke(jokedb, "Chuck Norris made a Happy Meal cry.");
	cgc_insert_joke(jokedb, "If you spell Chuck Norris in Scrabble, you win. Forever.");
	cgc_insert_joke(jokedb, "Fear of Chuck Norris is also called common sense.");
	cgc_insert_joke(jokedb, "Outer space exists because it's afraid to be on the same planet with Chuck Norris.");
	cgc_insert_joke(jokedb, "Chuck Norris destroyed the periodic table, because Chuck Norris only recognizes the element of surprise.");
	cgc_insert_joke(jokedb, "Some people wear Superman pajamas. Superman wears Chuck Norris pajamas.");
	cgc_insert_joke(jokedb, "Einstein said you can't move at the speed of light. Obviously he was never kicked by Chuck Norris...");
	cgc_insert_joke(jokedb, "Chuck Norris does not sleep. He waits.");
	cgc_insert_joke(jokedb, "Chuck Norris has no shadow....nothing's stupid enough to follow Chuck Norris.");
	cgc_insert_joke(jokedb, "Chuck Norris is so intimidating even his reflection won't look back at him.");
	cgc_insert_joke(jokedb, "When Chuck Norris throws you into a bottomless pit, you hit the bottom.");
	cgc_insert_joke(jokedb, "Some kids pee their name in snow. Chuck Norris pees his name in concrete.");
	cgc_insert_joke(jokedb, "Chuck Norris has the greatest Poker-Face of all time.");
	cgc_insert_joke(jokedb, "Chuck Norris played Russian Roulette with a fully loaded gun and won.");
	cgc_insert_joke(jokedb, "Chuck Norris doesn't fold paper airplanes, he folds airplanes into paper.");
	cgc_insert_joke(jokedb, "Chuck Norris knows the last digit of pi.");

}

// This is the vulnerable function.

// add joke to joke_db.
int cgc_insert_joke(jokedb_struct *jokedb, const char *joke_str) {
	
	// return error (-1) if jokedb is already full.
	if (jokedb->count >= MAX_JOKES) {
		return -1;
	
	// return error (-2) if the joke_str is too long.
	} else if (cgc_strlen(joke_str) >= MAX_JOKE_STRING_LEN - 1) {
		if (LOGLEVEL >= LOG_INFO) {
			cgc_syslog(LOG_ERROR, "Joke was too long -->\n");

#ifdef PATCHED
			cgc_syslog(LOG_ERROR, "~c\n", joke_str);
#else
			cgc_syslog(LOG_ERROR, joke_str);
#endif
		}
		return -2;

	} else {
		int idx = jokedb->count;
		// copy joke_str into next slot in joke db
		cgc_strncpy(jokedb->jokes[idx].joke_string, joke_str, cgc_strlen(joke_str));
		// assign id to that joke
		jokedb->jokes[idx].joke_id = idx;
		// update joke count
		jokedb->count++;
		if (LOGLEVEL == LOG_DEBUG) {
			cgc_syslog(LOG_DEBUG, "Added joke: ~n - ~c\n", idx, joke_str);
		}
		return idx;
	}
}

// return number of jokes currently in jokedb
int cgc_joke_count(jokedb_struct *jokedb) {
	return jokedb->count;
}
