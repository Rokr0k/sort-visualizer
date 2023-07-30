#include "window.hpp"
#include <SDL.h>
#include "algorithm.hpp"
#include "render.hpp"

sv::Window::Window() : window{nullptr}, gl{nullptr}
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);

  window = SDL_CreateWindow("Sort Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
  gl = SDL_GL_CreateContext(window);

  if (SDL_GL_SetSwapInterval(-1) < 0)
  {
    SDL_GL_SetSwapInterval(1);
  }
}

sv::Window::~Window()
{
  SDL_GL_DeleteContext(gl);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

void sv::Window::display()
{
  sv::Status status;

  sv::RenderMode renderMode = sv::RenderMode::HOR_BAR;

  bool paused{false};

  bool quit{false};
  SDL_Event event;
  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = SDL_TRUE;
      }
      else if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          quit = SDL_TRUE;
          break;
        case SDLK_BACKSPACE:
          container.reset();
          status = sv::Status{};
          break;
        case SDLK_RIGHTBRACKET:
        {
          std::size_t newSize = container.base().size() * 2;
          container.resize(newSize);
          status = sv::Status{};
          break;
        }
        case SDLK_LEFTBRACKET:
          if (container.base().size() > 2)
          {
            std::size_t newSize = container.base().size() / 2;
            container.resize(newSize);
            status = sv::Status{};
            break;
          }
        case SDLK_TAB:
          renderMode = static_cast<sv::RenderMode>((static_cast<int>(renderMode) + 1) % static_cast<int>(sv::RenderMode::COUNT));
          break;
        case SDLK_RETURN:
          while (container.popStatus().mode != sv::StatusMode::None)
            ;
          sv::randomize(container);
          break;
        case SDLK_SPACE:
          paused = !paused;
          break;
        case SDLK_RIGHT:
          if (paused)
          {
            status = container.popStatus();
          }
          break;
        case SDLK_b:
          while (container.popStatus().mode != sv::StatusMode::None)
            ;
          if (event.key.keysym.mod & KMOD_SHIFT)
          {
            sv::comb_sort(container);
          }
          else
          {
            sv::bubble_sort(container);
          }
          break;
        case SDLK_i:
          while (container.popStatus().mode != sv::StatusMode::None)
            ;
          if (event.key.keysym.mod & KMOD_SHIFT)
          {
            sv::shell_sort(container);
          }
          else
          {
            sv::insertion_sort(container);
          }
          break;
        case SDLK_s:
          while (container.popStatus().mode != sv::StatusMode::None)
            ;
          sv::selection_sort(container);
          break;
        case SDLK_h:
          while (container.popStatus().mode != sv::StatusMode::None)
            ;
          sv::heap_sort(container);
          break;
        case SDLK_m:
          while (container.popStatus().mode != sv::StatusMode::None)
            ;
          sv::merge_sort(container);
          break;
        case SDLK_q:
          while (container.popStatus().mode != sv::StatusMode::None)
            ;
          sv::quick_sort(container);
          break;
        case SDLK_o:
          while (container.popStatus().mode != sv::StatusMode::None)
            ;
          sv::stooge_sort(container);
          break;
        }
      }
    }

    if (!paused)
    {
      status = container.popStatus();
    }

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    sv::render(renderMode, status, container, w, h);

    SDL_GL_SwapWindow(window);
  }
}