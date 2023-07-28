#include "buffer.h"
#include <stdlib.h>

struct buffer_t
{
  int *ptr;
  size_t size;
};

buffer_t *create_buffer(size_t size)
{
  buffer_t *buffer = malloc(sizeof(buffer_t));
  buffer->ptr = malloc(sizeof(int) * (buffer->size = size));
  reset_buffer(buffer);
  return buffer;
}

void resize_buffer(buffer_t *buffer, size_t size)
{
  buffer->ptr = realloc(buffer->ptr, sizeof(int) * (buffer->size = size));
}

void reset_buffer(buffer_t *buffer)
{
  size_t i;
  for (i = 0; i < buffer->size; ++i)
  {
    buffer->ptr[i] = i;
  }
}

size_t size_buffer(buffer_t *buffer)
{
  return buffer->size;
}

int get_buffer(buffer_t *buffer, size_t idx)
{
  if (idx >= buffer->size)
  {
    return -1;
  }
  return buffer->ptr[idx];
}

void set_buffer(buffer_t *buffer, size_t idx, int value)
{
  if (idx >= buffer->size)
  {
    return;
  }
  buffer->ptr[idx] = value;
}

int compare_buffer(buffer_t *buffer, size_t idx1, size_t idx2)
{
  if (idx1 >= buffer->size || idx2 >= buffer->size)
  {
    return -2147483648;
  }

  int a = get_buffer(buffer, idx1);
  int b = get_buffer(buffer, idx2);

  if (a < b)
  {
    return -1;
  }
  else if (a > b)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void swap_buffer(buffer_t *buffer, size_t idx1, size_t idx2)
{
  if (idx1 >= buffer->size || idx2 >= buffer->size)
  {
    return;
  }

  int a = get_buffer(buffer, idx1);
  int b = get_buffer(buffer, idx2);

  set_buffer(buffer, idx1, b);
  set_buffer(buffer, idx2, a);
}

void free_buffer(buffer_t *buffer)
{
  free(buffer->ptr);
  free(buffer);
}