#include "FibonacciHeap.h"

int InitHeap(heap_t* heap, error_t* err) {
  *err = ALL_CORRECT;
  //validation of the applicability condition
  if (heap == NULL) {
    *err = INCORRECT_HEAP_POINTER;
    return ERROR;
  }
  //initialization
  heap->min = NULL;
  heap->size = 0;

  return SUCCESS;
}

int Insert(heap_t* heap, int key, error_t* err) {
  node_t *newNode, *min;

  *err = ALL_CORRECT;
  //validation of the applicability condition
  if (heap == NULL) {
    *err = INCORRECT_HEAP_POINTER;
    return ERROR;
  }

  newNode = malloc(sizeof(node_t));
  //checking the creation of a new node
  if (newNode == NULL) {
    *err = NOT_ENOUGH_MEMORY;
    return ERROR;
  }
  //filling in the fields of the new node
  newNode->degree = 0;
  newNode->parent = NULL;
  newNode->child = NULL;
  newNode->key = key;
  //inserting a node into the root list
  if (heap->size == 0) {//an empty heap
    heap->min = newNode;
    heap->min->right = newNode;
    heap->min->left = newNode;
  }
  else {//not an empty heap
    min = heap->min;
    newNode->right = min->right;
    newNode->left = min;
    min->right->left = newNode;
    min->right = newNode;
  }
  //change pointer to minimum if needed
  if (newNode->key < heap->min->key)
    heap->min = newNode;

  heap->size++;

  return SUCCESS;
}

static int consolidate(heap_t* heap) {
  node_t *cur, **arr, *next = heap->min, *child, *min, *prev;
  unsigned counter, D = (unsigned)log2(heap->size), d;

  arr = calloc(D + 1, sizeof(node_t*));
  //checking the creation of an auxiliary array
  if (arr == NULL)
    return ERROR;

  //break the list
  next->left->right = NULL;
  next->left = NULL;
  do {//for each node of the root list
    cur = next;
    d = cur->degree;
    next = next->right;
    while (arr[d] != NULL && d <= D) {
      prev = arr[d];
      
      if (prev->key < cur->key) {
        node_t* tmp = cur;
        //swapping
        cur = prev;
        prev = tmp;
      }

      prev->parent = cur;
      //removal from the root list
      if (prev->left != NULL)
        prev->left->right = prev->right;
      if (prev->right != NULL)
        prev->right->left = prev->left;
      if (cur->child == NULL) {//inserting into an empty list of children
        prev->left = prev;
        prev->right = prev;
        cur->child = prev;
      }
      else {//inserting into not an empty list of children
        child = cur->child;
        prev->left = child;
        prev->right = child->right;
        child->right->left = prev;
        child->right = prev;
      }
      cur->degree++;

      arr[d] = NULL;
      d++;
    }
    arr[d] = cur;
  } while (next != NULL);
  //creating the root list of the resulting heap
  heap->min = NULL;
  for (counter = 0; counter <= D; counter++) {
    cur = arr[counter];
    if (cur != NULL) {
      if (heap->min == NULL) {//inserting into an empty list
        cur->left = cur;
        cur->right = cur;
        heap->min = cur;
      }
      else {//inserting into not an empty list
        min = heap->min;
        cur->left = min;
        cur->right = min->right;
        min->right->left = cur;
        min->right = cur;
      }
      //change pointer to minimum if needed
      if (cur->key < heap->min->key)
        heap->min = cur;
    }
  }

  free(arr);

  return SUCCESS;
}

int ExtractMin(heap_t* heap, error_t* err) {
  node_t *tmp, *prevMin;
  int key;

  *err = ALL_CORRECT;
  //validation of the applicability condition
  if (heap == NULL) {
    *err = INCORRECT_HEAP_POINTER;
    return ERROR;
  }
  if (heap->min == NULL) {
    *err = EMPTY_HEAP;
    return ERROR;
  }
  //adding a list of children of the deleted node to the root list
  if (heap->min->child != NULL) {
    tmp = heap->min->child;
    do {
      tmp->parent = NULL;
      tmp = tmp->right;
    } while (tmp != heap->min->child);
    heap->min->child->left->right = heap->min->right;
    heap->min->right->left = heap->min->child->left;
    heap->min->right = heap->min->child;
    heap->min->child->left = heap->min;
  }

  prevMin = heap->min;
  //removal from the root list
  prevMin->left->right = prevMin->right;
  prevMin->right->left = prevMin->left;

  if (prevMin->right == prevMin)
    heap->min = NULL;
  else {//heap rebuild
    heap->min = prevMin->right;
    if (consolidate(heap) == ERROR) {
      //restore deleted node
      heap->min->left->right = prevMin;
      heap->min->left = prevMin;
      heap->min = prevMin;

      *err = NOT_ENOUGH_MEMORY;
      return ERROR;
    }
  }

  key = prevMin->key;

  free(prevMin);
  heap->size--;

  return key;
}

int Minimum(heap_t* heap, error_t* err) {
  *err = ALL_CORRECT;
  //validation of the applicability condition
  if (heap == NULL) {
    *err = INCORRECT_HEAP_POINTER;
    return ERROR;
  }

  if (heap->min != NULL)
    return heap->min->key;
  else {
    *err = EMPTY_HEAP;
    return ERROR;
  }
}

static void clear(node_t* node) {
  node_t *cur = node, *tmp;

  do {
    tmp = cur;
    //clear the list of children
    if (cur->child != NULL)
      clear(cur->child);

    cur = cur->right;
    free(tmp);
  } while (cur != node);
}

void ClearHeap(heap_t* heap) {
  if(heap != NULL && heap->min != NULL)
    clear(heap->min);
}