#ifndef SV_QUEUE_H
#define SV_QUEUE_H

#include <stddef.h>

typedef struct queue_t queue_t;

queue_t *create_queue(size_t itemsize);
int empty_queue(const queue_t *queue);
void enqueue_queue(queue_t *queue, const void *item);
int peek_queue(const queue_t *queue, void *item);
int dequeue_queue(queue_t *queue, void *item);
void clear_queue(queue_t *queue);
void free_queue(queue_t *queue);

#endif