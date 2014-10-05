#ifndef __list__
#define __list__

typedef struct _JkList JkList;

struct _JkList
{
  JkList* next;
  void* data;
};

JkList* jk_list_new();

#endif

