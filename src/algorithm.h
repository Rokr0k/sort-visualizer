#ifndef SV_ALGORITHM_H
#define SV_ALGORITHM_H

#include "buffer.h"
#include "queue.h"

typedef struct status_t
{
  size_t idx1, idx2;
  enum
  {
    SV_STAT_NONE,
    SV_STAT_COMPARE,
    SV_STAT_SWAP,
    SV_STAT_SET,
  } stat;
} status_t;

void randomize(buffer_t *b, queue_t *q);
void bubble_sort(buffer_t *b, queue_t *q);
void comb_sort(buffer_t *b, queue_t *q);
void insertion_sort(buffer_t *b, queue_t *q);
void shell_sort(buffer_t *b, queue_t *q);
void selection_sort(buffer_t *b, queue_t *q);

void heap_sort(buffer_t *b, queue_t *q);
void merge_sort(buffer_t *b, queue_t *q);
void quick_sort(buffer_t *b, queue_t *q);
void stooge_sort(buffer_t *b, queue_t *q);

#endif