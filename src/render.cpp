#include "render.hpp"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI (4 * std::atan(1))
#endif

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

static RGB hsv2rgb(HSV hsv)
{
  RGB rgb;

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

void sv::render(RenderMode mode, Status status, const Container &container, int w, int h)
{
    glViewport(0, 0, w, h);

    glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
    glClear(GL_COLOR_BUFFER_BIT);

  std::size_t size{container.display().size()};
  switch (mode)
  {
  case sv::RenderMode::HOR_BAR:
    glBegin(GL_TRIANGLES);
    for (std::size_t i{0}; i < size; ++i)
    {
      int value{container.display()[i]};

      if (status.mode != sv::StatusMode::None && (i == status.idx1 || status.mode != sv::StatusMode::Set && i == status.idx2))
      {
        switch (status.mode)
        {
        case sv::StatusMode::Compare:
          glColor3f(0.0F, 1.0F, 0.0F);
          break;
        case sv::StatusMode::Swap:
          glColor3f(1.0F, 0.0F, 0.0F);
          break;
        case sv::StatusMode::Set:
          glColor3f(0.0F, 0.0F, 1.0F);
          break;
        }
      }
      else
      {
        glColor3f(1.0F, 1.0F, 1.0F);
      }

      glVertex2f(2.0F * i / size - 1.0F, 2.0F * (value + 1) / size - 1.0F);
      glVertex2f(2.0F * i / size - 1.0F, -1.0F);
      glVertex2f(2.0F * (i + 1) / size - 1.0F, -1.0F);
      glVertex2f(2.0F * i / size - 1.0F, 2.0F * (value + 1) / size - 1.0F);
      glVertex2f(2.0F * (i + 1) / size - 1.0F, -1.0F);
      glVertex2f(2.0F * (i + 1) / size - 1.0F, 2.0F * (value + 1) / size - 1.0F);
    }
    glEnd();
    break;
  case sv::RenderMode::HOR_LINE:
    glBegin(GL_LINE_STRIP);
    for (std::size_t i{0}; i < size; ++i)
    {
      int value{container.display()[i]};

      if (status.mode != sv::StatusMode::None && (i == status.idx1 || status.mode != sv::StatusMode::Set && i == status.idx2))
      {
        switch (status.mode)
        {
        case sv::StatusMode::Compare:
          glColor3f(0.0F, 1.0F, 0.0F);
          break;
        case sv::StatusMode::Swap:
          glColor3f(1.0F, 0.0F, 0.0F);
          break;
        case sv::StatusMode::Set:
          glColor3f(0.0F, 0.0F, 1.0F);
          break;
        }
      }
      else
      {
        glColor3f(1.0F, 1.0F, 1.0F);
      }

      glVertex2f(2.0F * i / (size - 1.0F) - 1.0F, 2.0F * value / (size - 1) - 1.0F);
    }
    glEnd();
    break;
  case sv::RenderMode::HOR_COLOR:
    glBegin(GL_TRIANGLES);
    for (std::size_t i{0}; i < size; ++i)
    {
      int value{container.display()[i]};

      if (status.mode != sv::StatusMode::None && (i == status.idx1 || status.mode != sv::StatusMode::Set && i == status.idx2))
      {
        switch (status.mode)
        {
        case sv::StatusMode::Compare:
          glColor3f(0.0F, 1.0F, 0.0F);
          break;
        case sv::StatusMode::Swap:
          glColor3f(1.0F, 0.0F, 0.0F);
          break;
        case sv::StatusMode::Set:
          glColor3f(0.0F, 0.0F, 1.0F);
          break;
        }
      }
      else
      {
        RGB rgb{hsv2rgb(HSV{360.0F * value / size, 1.0F, 1.0F})};
        glColor3f(rgb.r, rgb.g, rgb.b);
      }

      glVertex2f(2.0F * i / size - 1.0F, 1.0F);
      glVertex2f(2.0F * i / size - 1.0F, -1.0F);
      glVertex2f(2.0F * (i + 1) / size - 1.0F, -1.0F);
      glVertex2f(2.0F * i / size - 1.0F, 1.0f);
      glVertex2f(2.0F * (i + 1) / size - 1.0F, -1.0F);
      glVertex2f(2.0F * (i + 1) / size - 1.0F, 1.0F);
    }
    glEnd();
    break;
  case sv::RenderMode::PIE_BAR:
    glBegin(GL_TRIANGLES);
    for (std::size_t i{0}; i < size; ++i)
    {
      int value{container.display()[i]};

      if (status.mode != sv::StatusMode::None && (i == status.idx1 || status.mode != sv::StatusMode::Set && i == status.idx2))
      {
        switch (status.mode)
        {
        case sv::StatusMode::Compare:
          glColor3f(0.0F, 1.0F, 0.0F);
          break;
        case sv::StatusMode::Swap:
          glColor3f(1.0F, 0.0F, 0.0F);
          break;
        case sv::StatusMode::Set:
          glColor3f(0.0F, 0.0F, 1.0F);
          break;
        }
      }
      else
      {
        glColor3f(1.0F, 1.0F, 1.0F);
      }

      glVertex2f((value + 1.0F) / size * std::sin(M_PI * 2.0F * i / size), (value + 1.0F) / size * std::cos(M_PI * 2.0F * i / size));
      glVertex2f(0.0F, 0.0F);
      glVertex2f((value + 1.0F) / size * std::sin(M_PI * 2.0F * (i + 1) / size), (value + 1.0F) / size * std::cos(M_PI * 2.0F * (i + 1) / size));
    }
    glEnd();
    break;
  case sv::RenderMode::PIE_LINE:
    glBegin(GL_LINE_LOOP);
    for (std::size_t i{0}; i < size; ++i)
    {
      int value{container.display()[i]};

      if (status.mode != sv::StatusMode::None && (i == status.idx1 || status.mode != sv::StatusMode::Set && i == status.idx2))
      {
        switch (status.mode)
        {
        case sv::StatusMode::Compare:
          glColor3f(0.0F, 1.0F, 0.0F);
          break;
        case sv::StatusMode::Swap:
          glColor3f(1.0F, 0.0F, 0.0F);
          break;
        case sv::StatusMode::Set:
          glColor3f(0.0F, 0.0F, 1.0F);
          break;
        }
      }
      else
      {
        glColor3f(1.0F, 1.0F, 1.0F);
      }

      glVertex2f(value / (size - 1.0F) * std::sin(M_PI * 2.0F * i / size), value / (size - 1.0F) * std::cos(M_PI * 2.0F * i / size));
    }
    glEnd();
    break;
  case sv::RenderMode::PIE_COLOR:
    glBegin(GL_TRIANGLES);
    for (std::size_t i{0}; i < size; ++i)
    {
      int value{container.display()[i]};

      if (status.mode != sv::StatusMode::None && (i == status.idx1 || status.mode != sv::StatusMode::Set && i == status.idx2))
      {
        switch (status.mode)
        {
        case sv::StatusMode::Compare:
          glColor3f(0.0F, 1.0F, 0.0F);
          break;
        case sv::StatusMode::Swap:
          glColor3f(1.0F, 0.0F, 0.0F);
          break;
        case sv::StatusMode::Set:
          glColor3f(0.0F, 0.0F, 1.0F);
          break;
        }
      }
      else
      {
        RGB rgb{hsv2rgb(HSV{360.0F * value / size, 1.0F, 1.0F})};
        glColor3f(rgb.r, rgb.g, rgb.b);
      }

      glVertex2f(std::sin(M_PI * 2.0F * i / size), std::cos(M_PI * 2.0F * i / size));
      glVertex2f(0.0F, 0.0F);
      glVertex2f(std::sin(M_PI * 2.0F * (i + 1) / size), std::cos(M_PI * 2.0F * (i + 1) / size));
    }
    glEnd();
    break;
  }
}