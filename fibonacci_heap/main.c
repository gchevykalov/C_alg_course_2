#pragma warning (disable:4996)
#define _CRTDBG_MAP_ALLOC

#include <stdio.h>
#include "FibonacciHeap.h"
#include <crtdbg.h>

int Read(int* data) {
  char ch = (char)getchar();

  if (ch == EOF)
    return 0;

  switch (ch) {
  case 'a':
    scanf_s("%i", data);
    getchar();
    return 1;
  case 'm':
    getchar();
    return 2;
  case 'e':
    getchar();
    return 3;
  default:
    return 0;
  }
}

int main(void) {
  int num, var;
  heap_t heap;
  error_t err;

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  InitHeap(&heap, &err);

  printf("Commands and their format:\n");
  printf("\ta <num> - adding an item\n");
  printf("\tm - obtaining the minimum value\n");
  printf("\te - extracting the minimum element\n\n");

  var = Read(&num);
  while (var) {
    switch (var) {
    case 1:
      Insert(&heap, num, &err);
      break;
    case 2:
      printf("Minimum is %d\n", Minimum(&heap, &err));
      if(err == EMPTY_HEAP)
        printf("Heap was empty\n");
      break;
    default:
      printf("Has been retrieved %d\n", ExtractMin(&heap, &err));
      if (err == EMPTY_HEAP)
        printf("Heap was empty\n");
      break;
    }

    var = Read(&num);
  }

  ClearHeap(&heap);
  return 0;
}