#pragma once
#include "utils/queue.h"

typedef struct NodeCG {
  struct NodeCG *outgoing;
  struct NodeCG *incoming;
  unsigned int nout, nin;
} NodeCG;

typedef struct ComputationGraphDAG {
  struct NodeCG *start;
  struct Queue *tail;
  unsigned int n_start;
} ComputationGraphDAG;

NodeCG *create_node_cg();
ComputationGraphDAG *create_cg();
NodeCG *push_by_pop(ComputationGraphDAG *cg);
NodeCG *push(ComputationGraphDAG *cg);