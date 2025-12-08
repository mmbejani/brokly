#include "utils/dag.h"
#include "utils/queue.h"
#include <stdlib.h>

NodeCG *create_node_cg() {
  NodeCG *node = malloc(sizeof(NodeCG));
  return node;
}

ComputationGraphDAG *create_cg() {
  ComputationGraphDAG *cg = malloc(sizeof(ComputationGraphDAG));
  cg->tail = create_queue();
  return cg;
}