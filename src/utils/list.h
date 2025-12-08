#pragma once

typedef struct NodeList {

} NodeList;

typedef struct List {
  NodeList *data;
  unsigned int allocated;
  unsigned int size;
} List;

List *create_list(unsigned int size);
NodeList *append_list(List *);