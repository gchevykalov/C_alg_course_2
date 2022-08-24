#ifndef LIST_H_INCLUDED__
#define LIST_H_INCLUDED__
#pragma once
//определение типа Список
typedef struct list_t {
  const char* data;
  struct list_t* next;
} list_t;

#endif /* ERROR_H_INCLUDED__ */