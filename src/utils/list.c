#include "utils/list.h"
#include <stdlib.h>

List *create_list(unsigned int size) {
  List *list = malloc(sizeof(List));
  list->size = size;
  list->allocated = 0;
  list->data = malloc(sizeof(size));
  return list;
}