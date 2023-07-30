#ifndef SV_RENDER_HPP
#define SV_RENDER_HPP

#include "container.hpp"

namespace sv
{
  enum class RenderMode
  {
    HOR_BAR,
    HOR_LINE,
    HOR_COLOR,
    PIE_BAR,
    PIE_LINE,
    PIE_COLOR,
    COUNT,
  };

  void render(RenderMode mode, Status status, const Container &container, int w, int h);
}

#endif