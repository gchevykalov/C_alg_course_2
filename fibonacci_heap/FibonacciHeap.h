#ifndef __FIBONACCIHEAP_H_INCLUDED
#define __FIBONACCIHEAP_H_INCLUDED

#include <stdlib.h>
#include <math.h>

#define ERROR -1
#define SUCCESS 0

//heap node type
typedef struct node_t {
  int key;
  unsigned degree;
  struct node_t* left;
  struct node_t* right;
  struct node_t* parent;
  struct node_t* child;
} node_t;
//heap type
typedef struct {
  unsigned size;
  struct node_t* min;
} heap_t;
//type to report additional information about the error 
typedef enum {
  ALL_CORRECT,
  EMPTY_HEAP,
  NOT_ENOUGH_MEMORY,
  INCORRECT_HEAP_POINTER
} error_t;

//heap initialization function
int InitHeap(heap_t* heap, error_t* err);
//element insertion function
int Insert(heap_t* heap, int key, error_t* err);
//minimum element extraction function
int ExtractMin(heap_t* heap, error_t* err);
//function to get the value of the minimum element without extracting
int Minimum(heap_t* heap, error_t* err);
//full heap cleanup function
void ClearHeap(heap_t* heap);

#endif /* __FIBONACCIHEAP_H_INCLUDED */