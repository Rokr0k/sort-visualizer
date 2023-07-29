#include <SDL.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#include "algorithm.h"

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);

  SDL_Window *window = SDL_CreateWindow("Sort Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
  SDL_GLContext gl = SDL_GL_CreateContext(window);

  buffer_t *baseBuffer = create_buffer(512);
  buffer_t *displayBuffer = create_buffer(512);
  queue_t *statusQueue = create_queue(sizeof(status_t));

  status_t status;

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
        case SDLK_ESCAPE:
          bQuit = SDL_TRUE;
          break;
        case SDLK_BACKSPACE:
          reset_buffer(baseBuffer);
          reset_buffer(displayBuffer);
          clear_queue(statusQueue);
          break;
        case SDLK_RIGHTBRACKET:
          resize_buffer(baseBuffer, size_buffer(baseBuffer) * 2);
          reset_buffer(baseBuffer);
          resize_buffer(displayBuffer, size_buffer(displayBuffer) * 2);
          reset_buffer(displayBuffer);
          clear_queue(statusQueue);
          break;
        case SDLK_LEFTBRACKET:
          if (size_buffer(baseBuffer) > 2)
          {
            resize_buffer(baseBuffer, size_buffer(baseBuffer) / 2);
          }
          reset_buffer(baseBuffer);
          if (size_buffer(displayBuffer) > 2)
          {
            resize_buffer(displayBuffer, size_buffer(displayBuffer) / 2);
          }
          reset_buffer(displayBuffer);
          clear_queue(statusQueue);
          break;
        case SDLK_SPACE:
          clear_queue(statusQueue);
          randomize(baseBuffer, statusQueue);
          break;
        case SDLK_b:
          clear_queue(statusQueue);
          if (event.key.keysym.mod & KMOD_SHIFT)
          {
            comb_sort(baseBuffer, statusQueue);
          }
          else
          {
            bubble_sort(baseBuffer, statusQueue);
          }
          break;
        case SDLK_i:
          clear_queue(statusQueue);
          if (event.key.keysym.mod & KMOD_SHIFT)
          {
            shell_sort(baseBuffer, statusQueue);
          }
          else
          {
            insertion_sort(baseBuffer, statusQueue);
          }
          break;
        case SDLK_s:
          clear_queue(statusQueue);
          selection_sort(baseBuffer, statusQueue);
          break;
        case SDLK_h:
          clear_queue(statusQueue);
          heap_sort(baseBuffer, statusQueue);
          break;
        case SDLK_m:
          clear_queue(statusQueue);
          merge_sort(baseBuffer, statusQueue);
          break;
        case SDLK_q:
          clear_queue(statusQueue);
          quick_sort(baseBuffer, statusQueue);
          break;
        case SDLK_o:
          clear_queue(statusQueue);
          stooge_sort(baseBuffer, statusQueue);
          break;
        }
      }
    }

    if (dequeue_queue(statusQueue, &status) != -1)
    {
      switch (status.stat)
      {
      case SV_STAT_COMPARE:
        break;
      case SV_STAT_SWAP:
        swap_buffer(displayBuffer, status.idx1, status.idx2);
        break;
      case SV_STAT_SET:
        set_buffer(displayBuffer, status.idx1, status.idx2);
        break;
      }
    }
    else
    {
      status.stat = SV_STAT_NONE;
    }

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    glViewport(0, 0, w, h);

    glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    size_t i;
    size_t size = size_buffer(displayBuffer);
    for (i = 0; i < size; ++i)
    {
      int value = get_buffer(displayBuffer, i);

      if (status.stat != SV_STAT_NONE && (i == status.idx1 || status.stat != SV_STAT_SET && i == status.idx2))
      {
        switch (status.stat)
        {
        case SV_STAT_COMPARE:
          glColor3f(0.0F, 1.0F, 0.0F);
          break;
        case SV_STAT_SWAP:
          glColor3f(1.0F, 0.0F, 0.0F);
          break;
        case SV_STAT_SET:
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

    SDL_GL_SwapWindow(window);
  }

  free_buffer(baseBuffer);
  free_buffer(displayBuffer);
  free_queue(statusQueue);

  SDL_GL_DeleteContext(gl);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}