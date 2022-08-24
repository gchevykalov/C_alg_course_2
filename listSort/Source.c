#include <stdlib.h>
#include <string.h>
#include "Sort.h"

#define TRUE 1

/*
Реализация сортировки односвязного списка строк.
Строки сортируются в алфавитном порядке(пустые строки и элементы списка с NULLptr переносятся в начало).
Алгоритм: Сортировка слиянием.
Сложность алгоритма - N*logN
*/

void Merge(list_t* first, list_t** second, list_t** list, list_t** tail, int step) {
  list_t* node = 0;
  int firstSize, secondSize;

  firstSize = secondSize = step;

  while ((firstSize > 0 && first) || (secondSize > 0 && *second)) {
    if (firstSize == 0 || !first) {
      node = *second;
      *second = (*second)->next;
      secondSize--;
    }
    else if (secondSize == 0 || !*second) {
      node = first;
      first = first->next;
      firstSize--;
    }
    else if (first->data == NULL) {
      node = first;
      first = first->next;
      firstSize--;
    }
    else if((*second)->data == NULL) {
      node = *second;
      *second = (*second)->next;
      secondSize--;
    }
    else if (strcmp(first->data, (*second)->data) <= 0) {
      node = first;
      first = first->next;
      firstSize--;
    }
    else {
      node = *second;
      *second = (*second)->next;
      secondSize--;
    }

    if (*tail) {
      (*tail)->next = node;
    }
    else {
      *list = node;
    }
    *tail = node;
  }
}

list_t* MergeSort(list_t* list) {
  list_t* first, *second;
  list_t* tail;
  int step;
  int numMerges;
  int counter;

  if (!list)
    return NULL;

  step = 1;

  while (TRUE) {
    first = list;
    list = NULL;
    tail = NULL;

    numMerges = 0;

    while (first) {
      numMerges++;

      second = first;
      for (counter = 0; counter < step;counter++) {
        second = second->next;
        if (!second)
          break;
      }

      Merge(first, &second, &list, &tail, step);
      
      first = second;
    }
    tail->next = NULL;

    if (numMerges <= 1)
      return list;

    step *= 2;
  }
}