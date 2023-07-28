#include "queue.h"
#include <stdlib.h>
#include <string.h>

struct node_t
{
  void *data;
  struct node_t *next;
};

struct queue_t
{
  struct node_t *front;
  struct node_t *rear;
  size_t itemsize;
};

queue_t *create_queue(size_t itemsize)
{
  queue_t *queue = malloc(sizeof(queue_t));
  queue->itemsize = itemsize;
  queue->front = queue->rear = NULL;
  return queue;
}

int empty_queue(const queue_t *queue)
{
  return queue->front == NULL && queue->rear == NULL;
}

void enqueue_queue(queue_t *queue, const void *item)
{
  struct node_t *node = malloc(sizeof(struct node_t));
  node->data = malloc(queue->itemsize);
  memcpy(node->data, item, queue->itemsize);
  node->next = NULL;

  if (empty_queue(queue))
  {
    queue->front = node;
  }
  else
  {
    queue->rear->next = node;
  }
  queue->rear = node;
}

int peek_queue(const queue_t *queue, void *item)
{
  if (empty_queue(queue))
  {
    return -1;
  }

  memcpy(item, queue->front->data, queue->itemsize);

  return 0;
}

int dequeue_queue(queue_t *queue, void *item)
{
  if (empty_queue(queue))
  {
    return -1;
  }

  struct node_t *node = queue->front;
  queue->front = queue->front->next;
  if(queue->front == NULL)
  {
    queue->rear = NULL;
  }
  memcpy(item, node->data, queue->itemsize);
  free(node->data);
  free(node);

  return 0;
}

void clear_queue(queue_t *queue)
{
  struct node_t *node = queue->front;
  while(node != NULL)
  {
    struct node_t *next = node->next;
    free(node->data);
    free(node);
    node = next;
  }
  queue->front = queue->rear = NULL;
}

void free_queue(queue_t *queue)
{
  struct node_t *node = queue->front;
  while(node != NULL)
  {
    struct node_t *next = node->next;
    free(node->data);
    free(node);
    node = next;
  }
  free(queue);
}