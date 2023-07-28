#include "algorithm.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

static int compare(buffer_t *b, queue_t *q, int idx1, int idx2)
{
  status_t status = {idx1, idx2, SV_STAT_COMPARE};
  enqueue_queue(q, &status);
  return compare_buffer(b, idx1, idx2);
}

static void swap(buffer_t *b, queue_t *q, int idx1, int idx2)
{
  status_t status = {idx1, idx2, SV_STAT_SWAP};
  enqueue_queue(q, &status);
  swap_buffer(b, idx1, idx2);
}

static void set(buffer_t *b, queue_t *q, int idx, int value)
{
  status_t status = {idx, value, SV_STAT_SET};
  enqueue_queue(q, &status);
  set_buffer(b, idx, value);
}

void randomize(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);

  srand(time(NULL));

  size_t i;
  for (i = 0; i < size - 1; ++i)
  {
    size_t j = rand() % (size - i) + i;
    swap(b, q, i, j);
  }
}

void bubble_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  size_t i, j;
  bool swapped;
  for (i = 0; i < size - 1; ++i)
  {
    swapped = false;
    for (j = 0; j < size - i - 1; ++j)
    {
      if (compare(b, q, j, j + 1) > 0)
      {
        swap(b, q, j, j + 1);
        swapped = true;
      }
    }
    if (!swapped)
    {
      break;
    }
  }
}

void comb_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  size_t j = size;
  size_t i;
  bool swapped;
  while (j != 1 || swapped)
  {
    j = (j * 10) / 13;
    if (j < 1)
    {
      j = 1;
    }
    swapped = false;
    for (i = 0; i < size - j; ++i)
    {
      if (compare(b, q, i, i + j) > 0)
      {
        swap(b, q, i, i + j);
        swapped = true;
      }
    }
  }
}

void insertion_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  size_t i, j;
  for (i = 1; i < size; ++i)
  {
    for (j = i; j > 0 && compare(b, q, j - 1, j) > 0; --j)
    {
      swap(b, q, j - 1, j);
    }
  }
}

void shell_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  size_t i, j, k;
  for (k = size / 2; k > 0; k /= 2)
  {
    for (i = k; i < size; ++i)
    {
      for (j = i; j >= k && compare(b, q, j - k, j) > 0; j -= k)
      {
        swap(b, q, j - k, j);
      }
    }
  }
}

void selection_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  size_t i, j, k;
  for (i = 0; i < size - 1; ++i)
  {
    k = i;
    for (j = i + 1; j < size; ++j)
    {
      if (compare(b, q, j, k) < 0)
      {
        k = j;
      }
    }
    if (i != k)
    {
      swap(b, q, i, k);
    }
  }
}

static void heapify(buffer_t *b, queue_t *q, size_t size, size_t root)
{
  size_t i = root;
  size_t l = i * 2 + 1;
  size_t r = i * 2 + 2;

  if (l < size && compare(b, q, i, l) < 0)
  {
    i = l;
  }
  if (r < size && compare(b, q, i, r) < 0)
  {
    i = r;
  }
  if (i != root)
  {
    swap(b, q, i, root);
    heapify(b, q, size, i);
  }
}

void heap_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  size_t i;
  for (i = size / 2 - 1; i > 0; i--)
  {
    heapify(b, q, size, i);
  }
  heapify(b, q, size, 0);

  for (i = size - 1; i > 0; i--)
  {
    swap(b, q, 0, i);
    heapify(b, q, i, 0);
  }
}

static void merge(buffer_t *b, queue_t *q, size_t l, size_t m, size_t r)
{
  int *aux = malloc(sizeof(int) * (r - l + 1));

  size_t i, j, k;

  i = l;
  j = m + 1;
  k = 0;
  while (i <= m && j <= r)
  {
    if (compare(b, q, i, j) <= 0)
    {
      aux[k] = get_buffer(b, i);
      ++i;
    }
    else
    {
      aux[k] = get_buffer(b, j);
      ++j;
    }
    ++k;
  }

  while (i <= m)
  {
    aux[k] = get_buffer(b, i);
    ++k;
    ++i;
  }
  while (j <= r)
  {
    aux[k] = get_buffer(b, j);
    ++k;
    ++j;
  }

  for (i = l; i <= r; ++i)
  {
    set(b, q, i, aux[i - l]);
  }

  free(aux);
}

static void mergeRec(buffer_t *b, queue_t *q, size_t l, size_t r)
{
  if (l < r)
  {
    size_t m = l + (r - l) / 2;

    mergeRec(b, q, l, m);
    mergeRec(b, q, m + 1, r);
    merge(b, q, l, m, r);
  }
}

void merge_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  mergeRec(b, q, 0, size - 1);
}

static size_t partition(buffer_t *b, queue_t *q, size_t l, size_t r)
{
  swap(b, q, l + (r - l) / 2, r);
  size_t p = r;

  size_t i = l;
  size_t j;
  for (j = l; j < r; ++j)
  {
    if (compare(b, q, j, p) < 0)
    {
      swap(b, q, i, j);
      ++i;
    }
  }
  swap(b, q, i, p);
  return i;
}

static void quickRec(buffer_t *b, queue_t *q, size_t l, size_t r)
{
  if (l < r)
  {
    size_t p = partition(b, q, l, r);

    if (p > 0)
    {
      quickRec(b, q, l, p - 1);
    }
    if (p < r)
    {
      quickRec(b, q, p + 1, r);
    }
  }
}

void quick_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  quickRec(b, q, 0, size - 1);
}

static void stooge(buffer_t *b, queue_t *q, size_t l, size_t r)
{
  if (compare(b, q, l, r) > 0)
  {
    swap(b, q, l, r);
  }
  if (r - l + 1 > 2)
  {
    size_t t = (r - l + 1) / 3;
    stooge(b, q, l, r - t);
    stooge(b, q, l + t, r);
    stooge(b, q, l, r - t);
  }
}

void stooge_sort(buffer_t *b, queue_t *q)
{
  size_t size = size_buffer(b);
  stooge(b, q, 0, size - 1);
}