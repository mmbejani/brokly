#include "util/map.h"

int main(int argc, char **argv) {
  TensorMap *map = map_create(5);
  Tensor t = {};
  map_insert(map, 0, &t);
  return 0;
}