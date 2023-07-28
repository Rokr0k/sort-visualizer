#ifndef SV_ALGORITHM_H
#define SV_ALGORITHM_H

#include "buffer.h"

typedef struct status_t
{
  size_t idx1, idx2;
  enum
  {
    SV_STAT_NONE,
    SV_STAT_COMPARE,
    SV_STAT_SWAP,
  } stat;
} status_t;

extern status_t status;

typedef int (*algorithm_t)(buffer_t *);

int randomize(buffer_t *buffer);
int bubble_sort(buffer_t *buffer);
int insertion_sort(buffer_t *buffer);

#endif