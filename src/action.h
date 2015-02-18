#ifndef __ui_action__
#define __ui_action__
#include "stdbool.h"
#include <Elementary.h>
#include <Eina.h>

typedef struct _Action JkAction;

struct _Action
{
  Evas_Object* root;
  Evas_Object* box;
  Evas_Object* gl;
};

JkAction* widget_action_new(Evas_Object* win);

typedef void (*button_callback)(void *data);

typedef struct _ButtonCallbackData ButtonCallbackData;
struct _ButtonCallbackData
{
  void* data;
  button_callback fn;
};

void action_button_new(
      JkAction* action,
      const char* name,
      void* data,
      button_callback fn);

#endif

