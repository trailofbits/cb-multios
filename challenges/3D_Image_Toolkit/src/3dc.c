/*

Copyright (c) 2016 Cromulence LLC

Authors: Dan Czarnecki <cgc@cromulence.com>

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

#include "cgc_3dc.h"

extern t3DCPixel **px_list;

void cgc_Push(t3DCPixel **px_list, t3DCPixel *px) {
    if (px == NULL)
      return;

    if (px_list == NULL)
      return;

    int i;

    t3DCPixel *new = cgc_malloc(sizeof(t3DCPixel));

    cgc_memcpy(new, px, sizeof(t3DCPixel));

    for (i = 0; i <= MAX_PIXELS; i++) {
      if (px_list[i] == NULL) {
          px_list[i] = new;
          break;
      }
    }

    return;
}

void cgc_RunTask(t3DCPixel **px_list, task_callback exec_task, int16_t fptr_arg) {
  int16_t count = MAX_PIXELS;
  int16_t i = 0;

  while (count--) {
    exec_task(px_list[i++], fptr_arg);

  }

  return;
}

void cgc_ReadFile(t3DCPixel **px_list) {
  int32_t dataSize = MAGIC_PAGE_SIZE;
  cgc_seed_prng(*(unsigned int*)MAGIC_PAGE);

  t3DCPixel *px;
  uint32_t offset = 0;

  while(dataSize > 0) {
    px = cgc_malloc(sizeof(t3DCPixel));

    px->x = (int16_t) cgc_prng();
    px->y = (int16_t) cgc_prng();
    px->z = (int16_t) cgc_prng();
    px->r = (uint8_t) cgc_prng();
    px->g = (uint8_t) cgc_prng();
    px->b = (uint8_t) cgc_prng();
    px->a = (uint8_t) cgc_prng();

    cgc_Push(px_list, px);

    dataSize -= sizeof(t3DCPixel);

    cgc_free(px);
  }

}

void cgc_NewFile(t3DCPixel **px_list, char *buf) {
  uint16_t maxSize = MAX_FILE_SIZE;
  cgc_printf("Please submit your new file data ($d bytes):\n", maxSize);
  cgc_receive_bytes(buf, maxSize);

  uint16_t offset = 0;
  uint16_t i = 0;
  t3DCPixel *tmp;

  while (offset < maxSize) {
    tmp = px_list[i++];

    cgc_memcpy(&tmp->x, buf+offset, sizeof(int16_t));
    offset += sizeof(int16_t);

    cgc_memcpy(&tmp->y, buf+offset, sizeof(int16_t));
    offset += sizeof(int16_t);

    cgc_memcpy(&tmp->z, buf+offset, sizeof(int16_t));
    offset += sizeof(int16_t);

    cgc_memcpy(&tmp->r, buf+offset, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    cgc_memcpy(&tmp->g, buf+offset, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    cgc_memcpy(&tmp->b, buf+offset, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    cgc_memcpy(&tmp->a, buf+offset, sizeof(uint8_t));
    offset += sizeof(uint8_t);

  }

  cgc_printf("New file loaded\n");

}

void cgc_ShowPixel(t3DCPixel *px) {

  cgc_printf("XYZ:  ($d, $d, $d)\n", px->x, px->y, px->z);
  cgc_printf("RGBA: (#$02x$02x$02x$02x)\n", px->r, px->g, px->b, px->a);
  cgc_printf("\n");

  return;
}

// Check File
void cgc_CheckFile(t3DCPixel **px, int16_t num) {
  if (px == NULL)
    return;

  for (int i=0; i < num; i++) {
    cgc_printf("XYZ:  ($d, $d, $d)\n", px[i]->x, px[i]->y, px[i]->z);
    cgc_printf("RGBA: (#$02x$02x$02x$02x)\n", px[i]->r, px[i]->g, px[i]->b, px[i]->a);
    cgc_printf("\n");
  }

}

// Rotate
void cgc_RotateX(t3DCPixel *px, int16_t degree) {
  // degree to rad
  double a = cgc_degree_to_radian(degree);

  px->y = (int16_t)cgc_multiply(px->y, cgc_cos(a)) - cgc_multiply(px->z, cgc_sin(a));
  px->z = (int16_t)cgc_multiply(px->y, cgc_sin(a)) + cgc_multiply(px->z, cgc_cos(a));

}

void cgc_RotateY(t3DCPixel *px, int16_t degree) {
  // degree to rad
  double a = cgc_degree_to_radian(degree);

  px->x = (int16_t)cgc_multiply(px->z, cgc_sin(a)) + cgc_multiply(px->x, cgc_cos(a));
  px->z = (int16_t)cgc_multiply(px->z, cgc_cos(a)) - cgc_multiply(px->x, cgc_sin(a));

}

void cgc_RotateZ(t3DCPixel *px, int16_t degree) {
  // degree to rad
  double a = cgc_degree_to_radian(degree);

  px->x = (int16_t)cgc_multiply(px->x, cgc_cos(a)) - cgc_multiply(px->y, cgc_sin(a));
  px->y = (int16_t)cgc_multiply(px->x, cgc_sin(a)) + cgc_multiply(px->y, cgc_cos(a));

}

// Skew
void cgc_SkewX(t3DCPixel *px, int16_t skew_val) {
    px->x = (int16_t)(skew_val + px->x);
}

void cgc_SkewY(t3DCPixel *px, int16_t skew_val) {
    px->y += skew_val;
}

void cgc_SkewZ(t3DCPixel *px, int16_t skew_val) {
    px->z += skew_val;
}

void cgc_Scale(t3DCPixel *px, int16_t scale_val) {
  if (scale_val < 1 ||scale_val > 200) {
    return;
  }

  double percent = cgc_divide(scale_val, 100);

  int32_t tmp_x, tmp_y, tmp_z;

  tmp_x = cgc_multiply(px->x, percent);
  tmp_y = cgc_multiply(px->y, percent);
  tmp_z = cgc_multiply(px->z, percent);

  if (tmp_x > 0xffff) {
    if(px->x < 0) {
      px->x = -32768;
    } else {
      px->x = 32767;
    }
  } else {
    px->x = (int16_t)tmp_x;
  }

  if (tmp_y > 0xffff) {
    if(px->y < 0) {
      px->y = -32768;
    } else {
      px->y = 32767;
    }
  } else {
    px->y = (int16_t)tmp_y;
  }

  if (tmp_z > 0xffff) {
    if(px->z < 0) {
      px->z = -32768;
    } else {
      px->z = 32767;
    }
  } else {
    px->z = (int16_t)tmp_z;
  }

}

// Brightness
void cgc_Brightness(t3DCPixel *px, int16_t bright_val) {
  if (bright_val < -255  || bright_val > 255) {
    return;
  }

  int16_t new_r, new_g, new_b;

  new_r = (int16_t)(px->r + bright_val);
  new_g = (int16_t)(px->g + bright_val);
  new_b = (int16_t)(px->b + bright_val);

  if (new_r > 255) {
    px->r = 255;
  } else if (new_r < 0) {
    px->r = 0;
  } else {
    px->r = (uint8_t)new_r;
  }

  if (new_g > 255) {
    px->g = 255;
  } else if (new_g < 0) {
    px->g = 0;
  } else {
    px->g = (uint8_t)new_g;
  }

  if (new_b > 255) {
    px->b = 255;
  } else if (new_b < 0) {
    px->b = 0;
  } else {
    px->b = (uint8_t)new_b;
  }

  return;
}

// Opacity
void cgc_Opacity(t3DCPixel *px, int16_t opacity_val) {

  px->a = (uint8_t)opacity_val;

}

// math helpers
int32_t cgc_multiply(double a, double b) {
  return (int32_t)((double)a * (double) b);
}

int16_t cgc_divide(double a, double b) {
  return (int16_t)((double)a / (double) b);
}

int16_t cgc_degree_to_radian(int16_t degree) {
  return cgc_multiply(degree, cgc_divide(M_PI,180));
}

double cgc_cosine(int16_t a) {
  return cgc_cos(a);
}

double cgc_sine(int16_t a) {
  return cgc_sin(a);
}
