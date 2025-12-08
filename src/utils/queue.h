#pragma once

typedef struct QueueNode {
  struct QueueNode *next;
  struct QueueNode *prev;
} QueueNode;

typedef struct Queue {
  struct QueueNode *head;
  struct QueueNode *bottom;
  unsigned int size;
} Queue;

Queue *create_queue();
QueueNode *enque(Queue *q);
QueueNode *deque(Queue *q);
QueueNode *peek(Queue *q);
