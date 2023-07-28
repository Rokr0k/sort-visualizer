#include <SDL.h>
#include <GL/gl.h>
#include "buffer.h"
#include "algorithm.h"

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Sort Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
  SDL_GLContext gl = SDL_GL_CreateContext(window);

  buffer_t *buffer = create_buffer(512);

  algorithm_t algorithm = NULL;

  SDL_bool bQuit = SDL_FALSE;
  SDL_Event event;
  while (!bQuit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        bQuit = SDL_TRUE;
      }
      else if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_BACKSPACE:
          algorithm = NULL;
          reset_buffer(buffer);
          break;
        case SDLK_SPACE:
          algorithm = randomize;
          algorithm(buffer);
          break;
        case SDLK_b:
          algorithm = bubble_sort;
          algorithm(buffer);
          break;
        case SDLK_i:
          algorithm = insertion_sort;
          algorithm(buffer);
          break;
        }
      }
    }

    if (algorithm && algorithm(NULL))
    {
      algorithm = NULL;
    }

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    glViewport(0, 0, w, h);

    // glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    {
      glBegin(GL_TRIANGLES);
      size_t i;
      size_t size = size_buffer(buffer);
      for (i = 0; i < size; ++i)
      {
        int value = get_buffer(buffer, i);

        if (i == status.idx1 || i == status.idx2)
        {
          switch (status.stat)
          {
          case SV_STAT_NONE:
            glColor3f(1.0F, 1.0F, 1.0F);
            break;
          case SV_STAT_COMPARE:
            glColor3f(0.0F, 1.0F, 0.0F);
            break;
          case SV_STAT_SWAP:
            glColor3f(1.0F, 0.0F, 0.0F);
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
    }

    SDL_GL_SwapWindow(window);
  }

  free_buffer(buffer);

  SDL_GL_DeleteContext(gl);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}