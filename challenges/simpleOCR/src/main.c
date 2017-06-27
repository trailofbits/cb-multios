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
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_junk.h"
#include "cgc_myint.h"
#include "cgc_match_objects.h"

#ifdef DEBUG
  #define dbg(s, ...) fdprintf(STDERR, "DEBUG %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
  #define dbg(s, ...)
#endif

#define err(s, ...) \
({ \
  cgc_fdprintf(STDERR, "DEBUG %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
  cgc_exit(1); \
})


int cgc_send_n_bytes(int fd, cgc_size_t n, char* buf)
{
  if (!n || !buf)
    return -1;

  cgc_size_t tx = 0;
  cgc_size_t to_send = n;

  while (to_send > 0) {
    if (cgc_transmit(fd, buf + (n - to_send), to_send, &tx) != 0)
    {
      return -1;
    }
    else if (tx == 0) {
      break;
    }
    else
    {
      to_send -= tx;
    }
  }

  return n - to_send;
}

int cgc_read_n_bytes(int fd, cgc_size_t n, char* buf)
{
  if (!n || !buf)
    return -1;

  cgc_size_t rx = 0;
  cgc_size_t to_read = n;

  while (to_read > 0) {
    if (cgc_receive(fd, buf + (n - to_read), to_read, &rx) != 0)
    {
      return -1;
    }
    else if (rx == 0)
    {
      break;
    }
    else
    {
      to_read -= rx;
    }
  }

  return n - to_read;
}

int cgc_read_until(int fd, cgc_size_t n, char terminator, char* buf)
{
  cgc_size_t cgc_read = 0;
  while (cgc_read < n)
  {
    cgc_ssize_t tmp_read = cgc_read_n_bytes(fd, 1, buf + cgc_read);
    if (tmp_read < 0)
    {
      return -1;
    }
    else if (tmp_read == 0)
    {
      break;
    }

    if (cgc_memchr(buf + cgc_read, terminator, tmp_read) != NULL)
    {
      *((char* )cgc_memchr(buf + cgc_read, terminator, tmp_read)) = '\0';
      return cgc_read + tmp_read;
    }
    else
    {
      cgc_read += tmp_read;
    }
  }

  return -1;
}

cgc_size_t cgc_read_image(int fd, cgc_size_t width, cgc_size_t height, u8** input)
{
  if (!input)
    return 0;

  *input = NULL;
  u8* tmp_input = cgc_calloc(width * height, sizeof(char));
  if (!tmp_input)
    err("calloc() failed");

  cgc_size_t idx = 0;
  int mid_line = 0;

  while (idx < width * height)
  {
    int tmp_read;
    if (!mid_line)
      tmp_read = cgc_read_until(fd, width + 1, '\n', (char *)tmp_input + idx);
    else
      tmp_read = cgc_read_until(fd, width + 1, '\n', (char *)tmp_input + idx + mid_line);

    if (tmp_read < 0)
    {
      cgc_free(tmp_input);
      return 0;
    }
    else if (tmp_read == 0)
    {
      goto error;
    }
    else if (mid_line && tmp_read + mid_line != width + 1)
    {
      mid_line += tmp_read - 1;
    }
    else if (!mid_line && tmp_read != width + 1)
    {
      mid_line = tmp_read - 1;
    }
    else
    {
      idx += width;
      mid_line = 0;
    }
  }

  if (idx == width * height)
    goto done;

error:
  cgc_free(tmp_input);
  return 0;
done:
  *input = tmp_input;
  return idx / width;
}

typedef struct array_2d_view_t array_2d_view_t;
struct array_2d_view_t
{
  u8* data;
  u32 width, height;
  u32 dwidth, dheight;
  u32 x_off, y_off;
};

array_2d_view_t* cgc_make_2d_view(u8* data, u32 w, u32 h, u32 x_off, u32 y_off)
{
  array_2d_view_t* view = cgc_calloc(1, sizeof(array_2d_view_t));
  if (!view)
    err("calloc() failed");
  view->data = data;
  if (!view->data)
    err("calloc() failed");

  view->dwidth = w;
  view->dheight = h;

  view->x_off = x_off;
  view->y_off = y_off;

  view->width = w - x_off;
  view->height = h - y_off;

  return view;
}

// index is view relative
int cgc_index_through_view(u32 x, u32 y, array_2d_view_t* view, u8* val)
{
  if (x >= view->width || y >= view->height ||
      x + view->x_off >= view->dwidth ||
      y + view->y_off >= view->dheight)
    return -1;

  u32 drow = y + view->y_off;
  u32 dcol = x + view->x_off;;
  *val = view->data[drow * view->dwidth + dcol];
  return 0;
}


int cgc_parse_dimensions(char* buf, u32 max, u32* w, u32* h)
{
  char* endptr = NULL;

  for (char* p = buf; p < buf + max && *p != '\0'; p++)
    if (!(cgc_isspace(*p) || cgc_isdigit(*p)))
        return -1;

  if (!cgc_isdigit(*buf))
    return -1;

  *w = cgc_strtol(buf, &endptr, 10);
  if (*w == 0)
    return -1;

  while (endptr <  buf + max && cgc_isspace(*endptr))
    endptr++;

  if (endptr == buf + max)
    return -1;

  *h = cgc_strtol(endptr, &endptr, 10);
  if (*h == 0)
    return -1;

  if (endptr != buf + max)
    return -1;

  return 0;
}

float cgc_match_percent(array_2d_view_t* view, match_object_t* match_object)
{
  u32 match_count = 0;
  for (u32 y = 0; y < match_object->height; y++)
  {
    for (u32 x = 0; x < match_object->width; x++)
    {
      u8 val;
      if (cgc_index_through_view(x, y, view, &val) < 0)
        continue;
      else
        match_count += val == match_object->map[y* match_object->width + x];
    }
  }

  return (float) match_count / (match_object->height * match_object->width);
}

match_object_t* cgc_find_matching_object(array_2d_view_t* view, float match_threshold_pct)
{
  float best_match_pct = .0;
  match_object_t* best_match = NULL;

  for (u32 i = 0; i < NUM_MATCH_OBJECTS; i++)
  {
    if (match_objects[i].height > view->height || match_objects[i].width > view->width)
      continue;

    float match_pct = cgc_match_percent(view, &match_objects[i]);
    // dbg("%c -> %d\n", match_objects[i].character, (int)(match_pct * 100.0));
    if (match_pct >= best_match_pct && match_pct < 0.958)
    {
      best_match_pct = match_pct;
      best_match = &match_objects[i];
    }
  }

  if (best_match_pct >= match_threshold_pct)
    return best_match;
  else
    return NULL;
}

char* cgc_perform_ocr(u8* image, u32 width, u32 height, float match_threshold_pct)
{
#define MAX_OCR_DATA_SIZE 64
  char output[MAX_OCR_DATA_SIZE];

  u32 x_off= 0, y_off = 0;
  u32 out_idx = 0;

  while (x_off < width && y_off < height)
  {
    array_2d_view_t* view = cgc_make_2d_view(image, width, height, x_off, y_off);
    match_object_t* match = cgc_find_matching_object(view, match_threshold_pct);
    if (!match)
    {
      if (x_off < width)
      {
        x_off++;
      }
      else if (y_off < height)
      {
        x_off = 0;
        y_off++;
      }
      else
      {
        break;
      }
    }
    else
    {
#ifdef PATCHED
      if (out_idx >= MAX_OCR_DATA_SIZE)
        break;
#endif
      output[out_idx++] = match->character;

      if (x_off + match->width < width)
      {
        x_off += match->width;
      }
      else if (y_off + match->height < height)
      {
        x_off = 0;
        y_off += match->height;
      }
      else
      {
        break;
      }
    }
  }

  if (out_idx)
  {
    char *ret = cgc_calloc(out_idx, sizeof(char));
    if (!ret)
      err("calloc() failed");
    cgc_strncpy(ret, output, out_idx);
    return ret;
  }
  else
    return NULL;
}

int cgc_check_junk(void)
{
  u32 chk = 0;
  cgc_size_t max = cgc_strlen(junk);
  for (cgc_size_t k = 0; k < 0x10; k++)
  {
    for(cgc_size_t i = 0; i < max; i++)
    {
      if (i + k > 256)
        chk ^= ((junk[i + k - 256]) << (i + k % 64));

      if (i + k > 2048)
        chk ^= junk[i + k] | junk[i + k - 2048];

      if (i + k > 30000)
        chk ^= junk[i + k] | junk[i + k - 30000];
    }
  }

  return chk == 0x1afd7f;
}

static const char* magic = "Z1";

int main(int cgc_argc, char *cgc_argv[])
{
  if (!cgc_check_junk())
    err("bad junk");

  cgc_printf("Welcome to the super awesome OCR engine! Enter your input to have it OCR'd\n");

  int infd = STDIN;

  #define LINE_SIZE 32
  char line[LINE_SIZE];
  cgc_memset(line, 0, LINE_SIZE);
  if (cgc_read_until(infd, LINE_SIZE, '\n', line) < 0)
    err("bad line");
  else
    dbg("good line");

  if (cgc_strlen(line) != cgc_strlen(magic) || cgc_strncmp(line, magic, cgc_strlen(line)) != 0)
    err("bad magic");
  else
    dbg("good magic");

  cgc_memset(line, 0, LINE_SIZE);
  if (cgc_read_until(infd, LINE_SIZE, '\n', line) < 0)
    err("bad line");
  else
    dbg("good line");

  u32 w, h;
  if (cgc_parse_dimensions(line, cgc_strlen(line), &w, &h) != 0)
    err("bad dimensions");
  else
    dbg("good dimensions, %dx%d", w, h);

  u8 *image;
  u32 read_height = cgc_read_image(infd, w, h, &image);
  if (read_height != h || !image)
    err("bad image");
  else
    dbg("good image");


#define MATCH_THRESHOLD .90
  char* output = cgc_perform_ocr(image, w, h, MATCH_THRESHOLD);

  if (output)
    cgc_printf("Result: %s\n", output);
  else
    cgc_printf("No characters recognized\n");
}
