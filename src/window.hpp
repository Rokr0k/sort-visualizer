#ifndef SV_WINDOW_HPP
#define SV_WINDOW_HPP

#include <SDL_video.h>
#include <SDL_opengl.h>
#include "container.hpp"

namespace sv
{
  struct Window
  {
    Window();
    ~Window();

    void display();

  private:
    SDL_Window *window;
    SDL_GLContext gl;
    Container container;
  };
}

#endif