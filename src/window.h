#ifndef __window__
#define __window__
#include "stdbool.h"
#include "tree.h"

typedef struct _Window Window;

struct _Window
{
  int test;
  Evas_Object* win;
  Evas_Object* edje;
};

Window* window_new();
Tree* window_tree_new(Window* c);
void window_button_new(Window* c);

typedef void (*rust_init_callback)(void* data);

void init_callback_set(rust_init_callback cb, void* data);
bool init_callback_call();

#endif
