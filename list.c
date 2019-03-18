/**
 * fuckin list implement
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

// list allocate
List *new_list(List *prev, List *next, void *data){
  List *l = (List *)malloc(sizeof(List));
  l->data = data;
  l->next = next;
  l->prev = prev == NULL ? l : prev;
  return l;
}

// list delete
int del_list(List *l){
  List *n;
  List *d;

  while(l != NULL){
    if(l->data != NULL){
      free(l->data);
    }
    d = l;
    n = l->next;
    free(d);
  }
  return 0;
}

// append data pointer to list last pointer
int append_list(List *l, void *data){
  List *nl = new_list(l->prev, NULL, data);

  l->prev->next = nl;
  l->prev = nl;
  return 0;
}

// insert data pointer to the n-th list
int ins_list(List *l, int n, void *data){
  List *nl;
  List *p = l;
  int i;

  for(i = 0; i < n; i++){
    if(p != NULL) p = p->next;
  }

  if(p == NULL) return 1;

  nl = new_list(p, p->next, data);
  return 0;
}

// set data pointer to the n-th list
int set_list(List *l, int n, void *data){
  List *nl;
  List *p = l;
  int i;
  for(i = 0; i < n; i++){
    if(p != NULL) p = p->next;
  }

  if(p == NULL) return 1;

  p->data = data;
  return 0;
}

// get data pointer from the n-th list
// if you use this function, you use together cast
// ex.
// int *d = (int *)malloc(sizeof(int));
// *d = 100;
// List *l = new_list(NULL, NULL, d);
// int res = *((int *)get_list(l, 0));
void *get_list(List *l, int n){
  List *p = l;
  int i;
  for(i = 0; i < n; i++){
    if(p != NULL) p = p->next;
  }

  if(p == NULL) return NULL;

  return p->data;
}
