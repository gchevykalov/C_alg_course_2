#include "pch.h"
#include "../ListMergeSort/list.h"
#include "../ListMergeSort/Source.c"
#include <stdlib.h>
#include <stdio.h>

#define EVEN_NUMBER_OF_STRING 6
#define ODD_NUMBER_OF_STRING 7
#define HUGE_NUMBER_OF_STRING 100000
#define STEP 1

void push(list_t** list, const char* newTok) {
  list_t* node = (list_t*)malloc(sizeof(list_t));

  node->data = newTok;
  node->next = *list;
  *list = node;
}

void clearList(list_t* list) {
  list_t* node = NULL;

  while (list != NULL) {
    node = list;
    list = list->next;
    free(node);
  }
}

TEST(Merge_NullFirstPointer_returnSecondPointer) {
  list_t* secondPointer;
  list_t* firstPointer = NULL;
  list_t* list = NULL;
  list_t* tail = NULL;
  list_t node = {0,0};
  list_t* exp;

  exp = secondPointer = &node;
  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(exp, list);
}

TEST(Merge_NullSecondPointer_returnFirstPointer) {
  list_t* secondPointer = NULL;
  list_t* firstPointer;
  list_t* list = NULL;
  list_t* tail = NULL;
  list_t node = { 0,0 };

  firstPointer = &node;
  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(firstPointer, list);
}

TEST(Merge_NullBothPointers_returnNull) {
  list_t* secondPointer = NULL;
  list_t* firstPointer = NULL;
  list_t* list = NULL;
  list_t* tail = NULL;

  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(NULL, list);
}

TEST(Merge_NullFirstDataPointer_returnFirstPointer) {
  list_t* secondPointer;
  list_t* firstPointer;
  list_t* list = NULL;
  list_t* tail = NULL;
  list_t node1 = { NULL, NULL };
  list_t node2 = { "string", NULL };

  firstPointer = &node1;
  secondPointer = &node2;
  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(firstPointer, list);
}

TEST(Merge_NullSecondDataPointer_returnSecondPointer) {
  list_t* secondPointer;
  list_t* firstPointer;
  list_t* list = NULL;
  list_t* tail = NULL;
  list_t node1 = { "string", NULL };
  list_t node2 = { NULL, NULL };
  list_t* exp;

  firstPointer = &node1;
  exp = secondPointer = &node2;
  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(exp, list);
}

TEST(Merge_NullBothDataPointers_returnFirstPointer) {
  list_t* secondPointer;
  list_t* firstPointer;
  list_t* list = NULL;
  list_t* tail = NULL;
  list_t node1 = { NULL, NULL };
  list_t node2 = { NULL, NULL };

  firstPointer = &node1;
  secondPointer = &node2;
  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(firstPointer, list);
}

TEST(Merge_firstMoreThenSecond_returnFirstPointer) {
  list_t* secondPointer;
  list_t* firstPointer;
  list_t* list = NULL;
  list_t* tail = NULL;
  list_t node1 = { "b", NULL };
  list_t node2 = { "a", NULL };
  list_t* exp;

  firstPointer = &node1;
  exp = secondPointer = &node2;
  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(exp, list);
}

TEST(Merge_firstLessThenSecond_returnFirstPointer) {
  list_t* secondPointer;
  list_t* firstPointer;
  list_t* list = NULL;
  list_t* tail = NULL;
  list_t node1 = { "a", NULL };
  list_t node2 = { "b", NULL };

  firstPointer = &node1;
  secondPointer = &node2;
  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(firstPointer, list);
}

TEST(Merge_tailIsNotNUll_returnListPointerWithoutChanges) {
  list_t* secondPointer;
  list_t* firstPointer;
  list_t* list = NULL;
  list_t* tail = NULL;
  list_t node1 = { "a", NULL };
  list_t node2 = { "b", NULL };
  list_t* exp;

  list = firstPointer = &node1;
  tail = secondPointer = &node2;
  exp = list;
  Merge(firstPointer, &secondPointer, &list, &tail, STEP);
  EXPECT_EQ(exp, list);
}

TEST(MergeSort_NullPointer_returnNull) {
  list_t* list = NULL;

  EXPECT_EQ(NULL, MergeSort(list));
}

TEST(MergeSort_EvenNumObjects_returnSortedList) {
  list_t* listPointer = NULL;
  char* strings[EVEN_NUMBER_OF_STRING] = {"1string", "string1", "aaaa", "fsfsf", "00001", ""};
  int counter = 0;
  list_t* node = NULL;

  for (; counter < EVEN_NUMBER_OF_STRING; counter++) {
    push(&listPointer, strings[counter]);
  }

  listPointer = MergeSort(listPointer);
  node = listPointer;

  for (counter = 0; counter < EVEN_NUMBER_OF_STRING - 1; counter++) {
    EXPECT_LE(strcmp(node->data, node->next->data),0);
    node = node->next;
  }

  clearList(listPointer);
}

TEST(MergeSort_OddNumObjects_returnSortedList) {
  list_t* listPointer = NULL;
  char* strings[ODD_NUMBER_OF_STRING] = { "sdbsbdb", "11111", "23421342", "rjrjrj", "sdfgerse", "", "aasada"};
  int counter = 0;
  list_t* node = NULL;

  for (; counter < ODD_NUMBER_OF_STRING; counter++) {
    push(&listPointer, strings[counter]);
  }

  listPointer = MergeSort(listPointer);
  node = listPointer;

  for (counter = 0; counter < ODD_NUMBER_OF_STRING - 1; counter++) {
    EXPECT_LE(strcmp(node->data, node->next->data), 0);
    node = node->next;
  }

  clearList(listPointer);
}

TEST(MergeSort_HugeNumObjects_returnSortedList) {
  list_t* listPointer = NULL;
  char** strings = (char**)malloc(HUGE_NUMBER_OF_STRING * sizeof(char*));
  int counter = 0;
  list_t* node = NULL;

  for (; counter < HUGE_NUMBER_OF_STRING; counter++) {
    strings[counter] = (char*)malloc(2*sizeof(char));
    strings[counter][0] = rand() % (122 - 47) + 48;
    strings[counter][1] = '\0';
  }

  for (counter = 0; counter < HUGE_NUMBER_OF_STRING; counter++) {
    push(&listPointer, strings[counter]);
  }
  listPointer = MergeSort(listPointer);
  node = listPointer;

  for (counter = 0; counter < HUGE_NUMBER_OF_STRING - 1; counter++) {
    EXPECT_LE(strcmp(node->data, node->next->data), 0);
    node = node->next;
  }

  for (counter = 0; counter < HUGE_NUMBER_OF_STRING; counter++) {
    free(strings[counter]);
  }
  free(strings);
  clearList(listPointer);
}

TEST(MergeSort_SortedList_returnSortedList) {
  list_t* listPointer = NULL;
  char* strings[ODD_NUMBER_OF_STRING] = { "", "00001", "1string", "aaaa", "fsfsf", "string1", "xzxzxzzz" };
  int counter = 0;
  list_t* node = NULL;

  for (; counter < ODD_NUMBER_OF_STRING; counter++) {
    push(&listPointer, strings[counter]);
  }

  listPointer = MergeSort(listPointer);
  node = listPointer;

  for (counter = 0; counter < ODD_NUMBER_OF_STRING; counter++) {
    EXPECT_STREQ(strings[counter], node->data);
    node = node->next;
  }

  clearList(listPointer);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}