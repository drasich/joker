#ifndef __window__
#define __window__
#include "stdbool.h"
#include "tree.h"

typedef struct _Creator Creator;

struct _Creator
{
  int test;
  Evas_Object* win;
  Evas_Object* edje;
};

Creator* creator_new();
Tree* creator_tree_new(Creator* c);
void creator_button_new(Creator* c);

typedef void (*rust_init_callback)(void* data);

void init_callback_set(rust_init_callback cb, void* data);
bool init_callback_call();

#endif
