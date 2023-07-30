#include "color.hpp"
#include <cmath>
#ifndef M_PI
#define M_PI (atan(1) * 4)
#endif

sv::RGB sv::hsv2rgb(sv::HSV hsv)
{
  sv::RGB rgb;

  if (hsv.s == 0.0F)
  {
    rgb.r = hsv.v;
    rgb.g = hsv.v;
    rgb.b = hsv.v;
    return rgb;
  }

  int i;
  float f, p, q, t;

  if (hsv.h == 360)
  {
    hsv.h = 0;
  }
  else
  {
    hsv.h /= 60;
  }

  i = std::trunc(hsv.h);
  f = hsv.h - i;
  p = hsv.v * (1 - hsv.s);
  q = hsv.v * (1 - hsv.s * f);
  t = hsv.v * (1 - hsv.s * (1 - f));

  switch (i)
  {
  case 0:
    rgb.r = hsv.v;
    rgb.g = t;
    rgb.b = p;
    break;
  case 1:
    rgb.r = q;
    rgb.g = hsv.v;
    rgb.b = p;
    break;
  case 2:
    rgb.r = p;
    rgb.g = hsv.v;
    rgb.b = t;
    break;
  case 3:
    rgb.r = p;
    rgb.g = q;
    rgb.b = hsv.v;
    break;
  case 4:
    rgb.r = t;
    rgb.g = p;
    rgb.b = hsv.v;
    break;
  case 5:
    rgb.r = hsv.v;
    rgb.g = p;
    rgb.b = q;
    break;
  }

  return rgb;
}