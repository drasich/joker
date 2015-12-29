#ifndef __list__
#define __list__

#include "Elementary.h"
#include "window.h"

typedef struct _JkList JkList;

struct _JkList
{
  JkList* next;
  void* data;
};

JkList* jk_list_new();

Eo* jk_list_wdg_new(Window* win, const char* name);


#endif

