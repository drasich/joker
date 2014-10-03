#ifndef __window__
#define __window__
#include "stdbool.h"

typedef struct _Creator Creator;

struct _Creator
{
  int test;
  Evas_Object* win;
};

Creator* creator_new();
void creator_tree_new(Creator* c);

typedef void (*rust_init_callback)();

void init_callback_set(rust_init_callback cb);
bool init_callback_call();

#endif
