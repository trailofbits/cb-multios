/*

Author: Joe Rogers <joe@cromulence.com>

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_common.h"
#include "cgc_service.h"

/*
Service that parses a pcm-encoded file on cgc_stdin
and decodes a morse-code-like symbol stream.
The resulting message is printed on cgc_stdout
*/

#define MAX_PCM_SIZE 1048576
#define MAX_SAMPLES 524282
#define MAX_SYMBOLS 1024
#define MIN_VARIANCE 0.9
#define MAX_VARIANCE 1.1

extern struct language cgc_lh;

// used to identify mark and gap symbols in the data stream
struct time_bucket {
  short valid;
  unsigned int time;
  unsigned int count;
  char mark;
  char gap;
};
struct time_bucket Bucket[4];

/*
Once the pcm file has been decoded into dit and dah symbols
parse those into corresponding english letters
*/
void cgc_ParseCode(char *buf, char *output) {
  int i = 0;
  int o = 0;
  struct language *lp = &cgc_lh;

  while (buf[i] != '\0') {
    if (o > MAX_SYMBOLS-1) {
      cgc_puts("message too long\n");
      cgc__terminate(UNABLE_TO_PARSE_PCM);
    }

    switch (buf[i]) {
      case '|':
        // end of a character
        if (lp) {
          output[o++] = lp->c;
          lp = &cgc_lh;
        } else {
          cgc_puts("unknown character\n");
          cgc__terminate(UNABLE_TO_PARSE_PCM);
        }
        break;
      case ' ':
        // end of a word
        if (lp == &cgc_lh) {
          output[o++] = ' ';
        } else if (lp) {
          output[o++] = lp->c;
          lp = &cgc_lh;
          output[o++] = ' ';
        } else {
          cgc_puts("unknown character\n");
          cgc__terminate(UNABLE_TO_PARSE_PCM);
        }
        break;
      case '.':
        // dit symbol
        if (lp) {
          lp = lp->dit;
        } else {
          cgc_puts("unknown character\n");
          cgc__terminate(UNABLE_TO_PARSE_PCM);
        }
        break;
      case '-':
        // dah symbol
        if (lp) {
          lp = lp->dah;
        } else {
          cgc_puts("unknown character\n");
          cgc__terminate(UNABLE_TO_PARSE_PCM);
        }
        break;
      case '\n':
        // newline...just ingore it
        break;

      default:
        cgc_puts("invalid symbol\n");
        cgc__terminate(UNABLE_TO_PARSE_PCM);
    }

    i++;
  }
  if (lp) {
    output[o++] = lp->c;
    lp = &cgc_lh;
  } else {
    cgc_puts("unknown character\n");
    cgc__terminate(UNABLE_TO_PARSE_PCM);
  }
}

/*
 * receive all requested bytes
 */
int cgc_recv(int fd, void *buf, cgc_size_t count, cgc_size_t *rx_bytes) {
	cgc_size_t total_bytes = 0;
	cgc_size_t rx;
	int rval;	

	while (total_bytes < count) {
		rval = cgc_receive(fd, buf+total_bytes, 1, &rx);
		if (rval != 0) {
			return(rval);
		}
		if (rx != 1) {
			return(-1);
		}
		total_bytes++;
	}

	*rx_bytes = total_bytes;	
	return(0);
}

/*
Read the pcm file from cgc_stdin
*/
unsigned char *cgc_ReadWav(unsigned char *pcm) {
  cgc_size_t size;
  unsigned int total_size;
  struct pcm_header *p;

  // cgc_read in the pcm header
  if (cgc_recv(STDIN, pcm, 12, &size) != 0) {
    cgc_puts("Read error\n");
    cgc__terminate(READ_ERROR);
  }

  // use our pcm_header struct to check some input values
  p = (struct pcm_header *)pcm;
  if (p->ID != PCM) {
      cgc_puts("Invalid PCM format\n");
      cgc__terminate(INVALID_PCM_FMT);
  }
  if (p->NumSamples > MAX_SAMPLES) {
      cgc_puts("Invalid PCM length\n");
    cgc__terminate(INVALID_PCM_LEN);
  }
  if (p->NumSamples == 0) {
      cgc_puts("Invalid PCM format\n");
    cgc__terminate(INVALID_PCM_FMT);
  }

#ifdef PATCHED
  // make sure the SampleSize value is valid
  if (p->DataSize*8.0 / p->NumSamples != 16.0) {
    cgc_puts("Invalid PCM length\n");
    cgc__terminate(INVALID_PCM_LEN);
  }
#else
  // make sure the SampleSize value is valid
  // BUG. Check is done with integer division instead of
  // floating point which leads to an incorrectly
  // checked DataSize
  if (p->DataSize*8/p->NumSamples != 16) {
    cgc_puts("Invalid PCM length\n");
    cgc__terminate(INVALID_PCM_LEN);
  }
#endif

  // cgc_read in the data portion of the pcm
  total_size = 0;
  while (total_size != p->DataSize) {
    if (cgc_receive(STDIN, pcm+12+total_size, (p->DataSize-total_size), &size) != 0) {
      cgc_puts("Read error\n");
      cgc__terminate(READ_ERROR);
      }
    if (size == 0) {
      cgc_puts("Read error\n");
      cgc__terminate(READ_ERROR);
    }
    total_size +=  size;
  }

  return(pcm);
}

  /*
For a given symbol detected in the pcm file,
assign it to a paritcular bucket of similar
symbol length.
*/
int cgc_AssignToBucket(unsigned int symbol_time) {
  int i;

  // find a valid bucket to hold this symbol
  for (i = 1; i < 4; i++) {
    if (Bucket[i].valid) {
      if (Bucket[i].time > symbol_time*MIN_VARIANCE && Bucket[i].time < symbol_time*MAX_VARIANCE) {
        // found match, count it
        Bucket[i].count++;
        return(i);
      }
    }
  }
  // didn't find one, so allocate a new one (if possible)
  for (i = 1; i < 4; i++) {
      if (Bucket[i].valid == 0) {
        // found emtpy bucket, populate it
        Bucket[i].valid = 1;
        Bucket[i].time = symbol_time;
        Bucket[i].count = 1;
        return(i);
      }
  }

  cgc_puts("Couldn't find a bucket\n");
  cgc__terminate(UNABLE_TO_PARSE_PCM);
}

/*
Check that the symbol bucket times are
at the correct ratios
*/
void cgc_CheckLimits(int dit, int dah, int word) {
  if (Bucket[dah].time < Bucket[dit].time*3*MIN_VARIANCE || Bucket[dah].time > Bucket[dit].time*3*MAX_VARIANCE) {
    // Bucket dah is outside of our limits
    cgc_puts("Too much variance in symbol times\n");
    cgc__terminate(UNABLE_TO_PARSE_PCM);
  }
  if (word) {
    if (Bucket[word].time < Bucket[dit].time*7*MIN_VARIANCE || Bucket[word].time > Bucket[dit].time*7*MAX_VARIANCE) {
      // Bucket word is outside of our limits
      cgc_puts("Too much variance in symbol times\n");
      cgc__terminate(UNABLE_TO_PARSE_PCM);
    }
  }
}

/*
Figure out how the pcm symbol timings correlate
to morse-like symbols
*/
void cgc_ValidateBuckets(void) {
  int dit = 0;
  int dah = 0;
  int word = 0;

  // if all three buckets are valid,
  // the largest bucket is word gap
  // second largest is inter-char gap or dah
  // third largest is intra-char gap or dit
  if (Bucket[1].valid && Bucket[2].valid && Bucket[3].valid) {
    if (Bucket[1].time > Bucket[2].time && Bucket[1].time > Bucket[3].time) {
      word = 1;
      if (Bucket[2].time > Bucket[3].time) {
        dah = 2;
        dit = 3;
      } else {
        dah = 3;
        dit = 2;
      }
    } else if (Bucket[2].time > Bucket[1].time && Bucket[2].time > Bucket[3].time) {
      word = 2;
      if (Bucket[1].time > Bucket[3].time) {
        dah = 1;
        dit = 3;
      } else {
        dah = 3;
        dit = 1;
      }
    } else if (Bucket[3].time > Bucket[1].time && Bucket[3].time > Bucket[2].time) {
      word = 3;
      if (Bucket[1].time > Bucket[2].time) {
        dah = 1;
        dit = 2;
      } else {
        dah = 2;
        dit = 1;
      }
    }

  // if only two are valid,
  // largest is the inter-char gap or dah
  // second largest is intra-char gap or dit
  } else if (Bucket[1].valid && Bucket[2].valid) {
    word = 0;
    if (Bucket[1].time > Bucket[2].time) {
      dah = 1;
      dit = 2;
    } else {
      dah = 2;
      dit = 1;
    }
  } else {
      cgc_puts("Insufficient symbol diversity\n");
      cgc__terminate(INVALID_PCM_FMT);
  }

  Bucket[word].mark = ' ';
  Bucket[word].gap = ' ';
  Bucket[dah].mark = '-';
  Bucket[dah].gap = '|';
  Bucket[dit].mark = '.';
  Bucket[dit].gap = '\0';
  cgc_CheckLimits(dit,dah,word);
}

/*
Read the samples in the pcm file looking
for periods of tones and silence
*/
void cgc_ParseWav(unsigned char *pcm) {
  unsigned char *pcm_pos;
  unsigned char *end_pcm;
  unsigned int symbol_start;
  unsigned int symbol_end;
  struct pcm_header *p;
  int silence;
  int count;
  short s;
  char Symbols[MAX_SYMBOLS];
  int sp = 0;
  unsigned int symbol_time;
  char output[MAX_SYMBOLS];
  char output2[MAX_SYMBOLS];
  int i;
  int b;
  int first = 1;

  // init some vars
  cgc_bzero(Symbols, MAX_SYMBOLS);
  cgc_bzero(output, MAX_SYMBOLS);
  sp = 0;
  Bucket[1].valid = 0;
  Bucket[2].valid = 0;
  Bucket[3].valid = 0;
  p = (struct pcm_header *)pcm;

  // calc the end byte of the pcm data
  end_pcm = pcm+12+(p->DataSize);

  // start with the first sample
  pcm_pos = pcm+12;
  symbol_start = 12;
  symbol_end = 0;
  silence = 1;
  count = 0;
  while (pcm_pos < end_pcm && sp < MAX_SYMBOLS-2) {
    // grab the sample's value
    s = *(short *)pcm_pos;

    // see if it's a new silence or a tone
    if ((s > -10 && s < 10) && (!silence || first)) {
      // got a new silence

      // check 50 sample to be sure
      if (++count < 50) {
        pcm_pos+=2;
        continue;
      }

      // see if this is our first symbol
      if (first) {
        silence = 1;
        count = 0;
        first = 0;
        pcm_pos = pcm+12;
        symbol_start = 12;
        symbol_end = 0;
        continue;
      }

      // yep, found new silence, reset our flag vars
      silence = 1;
      count = 0;

      // calc the length of the previous tone symbol
      symbol_end = (int)(pcm_pos-pcm);
      symbol_time = ((symbol_end-(50*2)-symbol_start))/2;

      // get ready for the next symbol
      symbol_start = symbol_end-(50*2);

      // Assign to a symbol bucket
      Symbols[sp++] = cgc_AssignToBucket(symbol_time);

    } else if ((s < -10 || s > 10) && (silence || first)) {
      // got a new tone

      // check 50 sample to be sure
      if (++count < 50) {
        pcm_pos+=2;
        continue;
      }

      // see if this is our first symbol
      if (first) {
        silence = 0;
        count = 0;
        first = 0;
        pcm_pos = pcm+12;
        symbol_start = 12;
        symbol_end = 0;
        continue;
      }

      // yep, found new tone, reset our flag vars
      silence = 0;
      count = 0;

      // calc the length of the previous tone symbol
      symbol_end = (int)(pcm_pos-pcm);
      symbol_time = ((symbol_end-(50*2)-symbol_start))/2;

      // get ready for the next symbol
      symbol_start = symbol_end-(50*2);

      // Assign to a symbol bucket
      Symbols[sp++] = cgc_AssignToBucket(symbol_time) * -1;
    } else {
      count = 0;
    }
    pcm_pos+=2;
  }

  // handle the last symbol we were processing
  symbol_end = (int)(pcm_pos-pcm);
  symbol_time = ((short)(symbol_end-symbol_start))/2;
  if (!silence) {
    Symbols[sp++] = cgc_AssignToBucket(symbol_time);
  }

  // validate the buckets we discovered
  cgc_ValidateBuckets();

  // now that we've parsed the tones and silences
  // use that data to build the symbol string
  sp = 0;
  for (i = 0; i < MAX_SYMBOLS-1; i++) {
    if (Symbols[i] == 0) {
      continue;
    }
    // silence
    if (Symbols[i] < 0) {
      b = Symbols[i]*-1;
      if (Bucket[b].gap != '\0') {
        output[sp++] = Bucket[b].gap;
      }

    // tone
    } else {
      b = Symbols[i];
      if (Bucket[b].mark != '\0') {
        output[sp++] = Bucket[b].mark;
      }
    }
  }
  output[sp++] = '\n';

  // parse the symbols back to characters
  cgc_ParseCode(output, output2);

  // output the resulting message
  cgc_puts(output2);
  cgc_puts("\n");

}

int main(int cgc_argc, char *cgc_argv[]) {
    unsigned char pcm[MAX_PCM_SIZE];

    // zero the pcm var
    cgc_bzero(pcm, MAX_PCM_SIZE);

    // init the language data structures
    cgc_InitLang(&cgc_lh, NULL);

    // cgc_read in the pcm file
    cgc_ReadWav(pcm);

    // Read in each symbol
    cgc_ParseWav(pcm);

    return(0);
}
