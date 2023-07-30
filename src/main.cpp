#include <SDL.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI (4 * std::atan(1))
#endif
#include "algorithm.hpp"
#include "color.hpp"

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
}

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);

  SDL_Window *window{SDL_CreateWindow("Sort Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL)};
  SDL_GLContext gl{SDL_GL_CreateContext(window)};

  constexpr std::size_t initialSize{512};
  std::vector<int> baseBuffer(initialSize);
  std::vector<int> displayBuffer(initialSize);
  for (int i{0}; i < initialSize; ++i)
  {
    baseBuffer[i] = i;
    displayBuffer[i] = i;
  }
  std::queue<sv::Status> statusQueue;

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
          for (int i{0}; i < baseBuffer.size(); ++i)
          {
            baseBuffer.push_back(i);
            displayBuffer.push_back(i);
          }
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          break;
        case SDLK_RIGHTBRACKET:
        {
          std::size_t newSize = baseBuffer.size() * 2;
          baseBuffer.resize(newSize);
          displayBuffer.resize(newSize);
          for (int i{0}; i < newSize; ++i)
          {
            baseBuffer[i] = i;
            displayBuffer[i] = i;
          }
        }
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          break;
        case SDLK_LEFTBRACKET:
          if (baseBuffer.size() > 2)
          {
            std::size_t newSize = baseBuffer.size() / 2;
            baseBuffer.resize(newSize);
            displayBuffer.resize(newSize);
            for (int i{0}; i < newSize; ++i)
            {
              baseBuffer[i] = i;
              displayBuffer[i] = i;
            }
          }
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          break;
        case SDLK_TAB:
          renderMode = static_cast<sv::RenderMode>((static_cast<int>(renderMode) + 1) % static_cast<int>(sv::RenderMode::COUNT));
          break;
        case SDLK_RETURN:
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          sv::randomize(baseBuffer, statusQueue);
          break;
        case SDLK_SPACE:
          paused = !paused;
          break;
        case SDLK_RIGHT:
          if (paused)
          {
            if (!statusQueue.empty())
            {
              status = statusQueue.front();
              statusQueue.pop();
              switch (status.mode)
              {
              case sv::StatusMode::COMPARE:
                break;
              case sv::StatusMode::SWAP:
                std::swap(displayBuffer[status.idx1], displayBuffer[status.idx2]);
                break;
              case sv::StatusMode::SET:
                displayBuffer[status.idx1] = status.idx2;
                break;
              }
            }
            else
            {
              status.mode = sv::StatusMode::NONE;
            }
          }
          break;
        case SDLK_b:
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          if (event.key.keysym.mod & KMOD_SHIFT)
          {
            sv::comb_sort(baseBuffer, statusQueue);
          }
          else
          {
            sv::bubble_sort(baseBuffer, statusQueue);
          }
          break;
        case SDLK_i:
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          if (event.key.keysym.mod & KMOD_SHIFT)
          {
            sv::shell_sort(baseBuffer, statusQueue);
          }
          else
          {
            sv::insertion_sort(baseBuffer, statusQueue);
          }
          break;
        case SDLK_s:
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          sv::selection_sort(baseBuffer, statusQueue);
          break;
        case SDLK_h:
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          sv::heap_sort(baseBuffer, statusQueue);
          break;
        case SDLK_m:
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          sv::merge_sort(baseBuffer, statusQueue);
          break;
        case SDLK_q:
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          sv::quick_sort(baseBuffer, statusQueue);
          break;
        case SDLK_o:
          while (!statusQueue.empty())
          {
            statusQueue.pop();
          }
          sv::stooge_sort(baseBuffer, statusQueue);
          break;
        }
      }
    }

    if (!paused)
    {
      if (!statusQueue.empty())
      {
        status = statusQueue.front();
        statusQueue.pop();
        switch (status.mode)
        {
        case sv::StatusMode::COMPARE:
          break;
        case sv::StatusMode::SWAP:
          std::swap(displayBuffer[status.idx1], displayBuffer[status.idx2]);
          break;
        case sv::StatusMode::SET:
          displayBuffer[status.idx1] = status.idx2;
          break;
        }
      }
      else
      {
        status.mode = sv::StatusMode::NONE;
      }
    }

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    glViewport(0, 0, w, h);

    glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    std::size_t size{displayBuffer.size()};
    switch (renderMode)
    {
    case sv::RenderMode::HOR_BAR:
      glBegin(GL_TRIANGLES);
      for (std::size_t i{0}; i < size; ++i)
      {
        int value{displayBuffer[i]};

        if (status.mode != sv::StatusMode::NONE && (i == status.idx1 || status.mode != sv::StatusMode::SET && i == status.idx2))
        {
          switch (status.mode)
          {
          case sv::StatusMode::COMPARE:
            glColor3f(0.0F, 1.0F, 0.0F);
            break;
          case sv::StatusMode::SWAP:
            glColor3f(1.0F, 0.0F, 0.0F);
            break;
          case sv::StatusMode::SET:
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
        int value{displayBuffer[i]};

        if (status.mode != sv::StatusMode::NONE && (i == status.idx1 || status.mode != sv::StatusMode::SET && i == status.idx2))
        {
          switch (status.mode)
          {
          case sv::StatusMode::COMPARE:
            glColor3f(0.0F, 1.0F, 0.0F);
            break;
          case sv::StatusMode::SWAP:
            glColor3f(1.0F, 0.0F, 0.0F);
            break;
          case sv::StatusMode::SET:
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
        int value{displayBuffer[i]};

        if (status.mode != sv::StatusMode::NONE && (i == status.idx1 || status.mode != sv::StatusMode::SET && i == status.idx2))
        {
          switch (status.mode)
          {
          case sv::StatusMode::COMPARE:
            glColor3f(0.0F, 1.0F, 0.0F);
            break;
          case sv::StatusMode::SWAP:
            glColor3f(1.0F, 0.0F, 0.0F);
            break;
          case sv::StatusMode::SET:
            glColor3f(0.0F, 0.0F, 1.0F);
            break;
          }
        }
        else
        {
          sv::RGB rgb{sv::hsv2rgb(sv::HSV{360.0F * value / size, 1.0F, 1.0F})};
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
        int value{displayBuffer[i]};

        if (status.mode != sv::StatusMode::NONE && (i == status.idx1 || status.mode != sv::StatusMode::SET && i == status.idx2))
        {
          switch (status.mode)
          {
          case sv::StatusMode::COMPARE:
            glColor3f(0.0F, 1.0F, 0.0F);
            break;
          case sv::StatusMode::SWAP:
            glColor3f(1.0F, 0.0F, 0.0F);
            break;
          case sv::StatusMode::SET:
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
        int value{displayBuffer[i]};

        if (status.mode != sv::StatusMode::NONE && (i == status.idx1 || status.mode != sv::StatusMode::SET && i == status.idx2))
        {
          switch (status.mode)
          {
          case sv::StatusMode::COMPARE:
            glColor3f(0.0F, 1.0F, 0.0F);
            break;
          case sv::StatusMode::SWAP:
            glColor3f(1.0F, 0.0F, 0.0F);
            break;
          case sv::StatusMode::SET:
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
        int value{displayBuffer[i]};

        if (status.mode != sv::StatusMode::NONE && (i == status.idx1 || status.mode != sv::StatusMode::SET && i == status.idx2))
        {
          switch (status.mode)
          {
          case sv::StatusMode::COMPARE:
            glColor3f(0.0F, 1.0F, 0.0F);
            break;
          case sv::StatusMode::SWAP:
            glColor3f(1.0F, 0.0F, 0.0F);
            break;
          case sv::StatusMode::SET:
            glColor3f(0.0F, 0.0F, 1.0F);
            break;
          }
        }
        else
        {
          sv::RGB rgb{sv::hsv2rgb(sv::HSV{360.0F * value / size, 1.0F, 1.0F})};
          glColor3f(rgb.r, rgb.g, rgb.b);
        }

        glVertex2f(std::sin(M_PI * 2.0F * i / size), std::cos(M_PI * 2.0F * i / size));
        glVertex2f(0.0F, 0.0F);
        glVertex2f(std::sin(M_PI * 2.0F * (i + 1) / size), std::cos(M_PI * 2.0F * (i + 1) / size));
      }
      glEnd();
      break;
    }

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(gl);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}