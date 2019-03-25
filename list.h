#ifndef DEF_LIST_H
#define DEF_LIST_H

typedef struct DATA_List List;
struct DATA_List
{
  void *data;
  List *prev, *next;
};

List *new_list(List *, List *, void *);
int del_list(List *);
int append_list(List *, void *);
int ins_list(List *, int , void *);
int set_list(List *, int , void *);
void *get_list(List *, int n);

#endif