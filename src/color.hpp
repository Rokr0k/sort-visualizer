#ifndef SV_COLOR_HPP
#define SV_COLOR_HPP

namespace sv
{
  struct HSV
  {
    float h;
    float s;
    float v;
  };
  struct RGB
  {
    float r;
    float g;
    float b;
  };

  RGB hsv2rgb(HSV hsv);
}

#endif