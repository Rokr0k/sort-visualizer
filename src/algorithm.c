#include "algorithm.h"
#include <stdlib.h>
#include <time.h>

status_t status;

static int compare(buffer_t *b, int idx1, int idx2)
{
  status.idx1 = idx1;
  status.idx2 = idx2;
  status.stat = SV_STAT_COMPARE;
  return compare_buffer(b, idx1, idx2);
}

static void swap(buffer_t *b, int idx1, int idx2)
{
  status.idx1 = idx1;
  status.idx2 = idx2;
  status.stat = SV_STAT_SWAP;
  swap_buffer(b, idx1, idx2);
}

static void none()
{
  status.stat = SV_STAT_NONE;
}

int randomize(buffer_t *buffer)
{
  srand(time(NULL));

  static buffer_t *_b;
  static size_t i;
  if (buffer != NULL)
  {
    _b = buffer;
    i = 0;
    return 0;
  }

  size_t size = size_buffer(_b);

  if (i < size)
  {
    int idx = rand() % (size - i) + i;
    swap(_b, i, idx);
    ++i;
    return 0;
  }

  none();

  return -1;
}

int bubble_sort(buffer_t *buffer)
{
  static buffer_t *_b;
  static size_t i, j;
  static int comp;
  static int swapped;
  if (buffer != NULL)
  {
    _b = buffer;
    i = 0;
    j = 0;
    comp = 221;
    swapped = 0;
    return 0;
  }

  size_t size = size_buffer(_b);

  if (i < size - 1)
  {
    if (j < size - i - 1)
    {
      if (comp == 221)
      {
        comp = compare(_b, j, j + 1);

        return 0;
      }
      if (comp > 0)
      {
        comp = 221;
        swapped = 1;

        swap(_b, j, j + 1);

        ++j;
        if (j >= size - i - 1)
        {
          j = 0;
          ++i;
        }

        return 0;
      }
      else
      {
        ++j;
        if (j >= size - i - 1)
        {
          if (!swapped)
          {
            none();
            return 0;
          }

          j = 0;
          ++i;
        }

        comp = compare(_b, j, j + 1);

        return 0;
      }
    }
  }

  none();

  return -1;
}

int insertion_sort(buffer_t *buffer)
{
  static buffer_t *_b;
  static size_t i, j;
  static int comp;
  if (buffer != NULL)
  {
    _b = buffer;
    i = 1;
    j = 1;
    comp = 221;
    return 0;
  }

  size_t size = size_buffer(_b);

  if (i < size)
  {
    if (j > 0)
    {
      if (comp == 221)
      {
        comp = compare(_b, j - 1, j);

        return 0;
      }
      if (comp > 0)
      {
        comp = 221;

        swap(_b, j - 1, j);

        --j;
        if (j <= 0)
        {
          ++i;
          j = i;
        }

        return 0;
      }
      else
      {
        ++i;
        j = i;

        comp = compare(_b, j - 1, j);

        return 0;
      }
    }
  }

  none();

  return -1;
}