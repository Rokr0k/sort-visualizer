#include "color.h"
#include <math.h>
#ifndef M_PI
#define M_PI (atan(1)*4)
#endif

void hsv2rgb(float h, float s, float v, float *r, float *g, float *b)
{
  if (s == 0.0F)
  {
    *r = v;
    *g = v;
    *b = v;
    return;
  }

  int i;
  float f, p, q, t;

  if (h == 360)
  {
    h = 0;
  }
  else
  {
    h /= 60;
  }

  i = trunc(h);
  f = h - i;
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - s * (1 - f));

  switch (i)
  {
  case 0:
    *r = v;
    *g = t;
    *b = p;
    break;
  case 1:
    *r = q;
    *g = v;
    *b = p;
    break;
  case 2:
    *r = p;
    *g = v;
    *b = t;
    break;
  case 3:
    *r = p;
    *g = q;
    *b = v;
    break;
  case 4:
    *r = t;
    *g = p;
    *b = v;
    break;
  case 5:
    *r = v;
    *g = p;
    *b = q;
    break;
  }
}