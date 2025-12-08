#include "utils/queue.h"
#include <stdlib.h>

Queue *create_queue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->size = 0;
  q->bottom = q->head = NULL;
  return q;
}

QueueNode *enque(Queue *q) {
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
  node->next = q->bottom;
  q->bottom = node;
  q->size++;
  return node;
}
QueueNode *deque(Queue *q) {
  QueueNode *node = q->head;
  q->head = node->prev;
  q->size--;
  return node;
}
__attribute__((always_inline)) QueueNode *peek(Queue *q) { return q->head; }