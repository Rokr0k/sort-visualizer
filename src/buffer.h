#ifndef SV_BUFFER_H
#define SV_BUFFER_H

#include <stddef.h>

typedef struct buffer_t buffer_t;

buffer_t *create_buffer(size_t size);
void resize_buffer(buffer_t *buffer, size_t size);
void reset_buffer(buffer_t *buffer);
size_t size_buffer(buffer_t *buffer);
int get_buffer(buffer_t *buffer, size_t idx);
void set_buffer(buffer_t *buffer, size_t idx, int value);
int compare_buffer(buffer_t *buffer, size_t a, size_t b);
void swap_buffer(buffer_t *buffer, size_t a, size_t b);
void free_buffer(buffer_t *buffer);

#endif