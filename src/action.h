#ifndef __ui_action__
#define __ui_action__
#include "stdbool.h"
#include <Elementary.h>
#include <Eina.h>
#include "window.h"
#include "common.h"

typedef struct _Action JkAction;
typedef struct Evas_Object JkLabel;
typedef struct Evas_Object JkEntry;

struct _Action
{
  Evas_Object* win;
  Evas_Object* root;
  Evas_Object* box;
  Evas_Object* gl;
};

JkAction* window_action_new(Window* w);
JkAction* window_action_new_up(Window* w);

Evas_Object* action_button_new(
      JkAction* action,
      const char* name,
      void* data,
      button_callback fn);

Evas_Object* action_button_new1(
      JkAction* action,
      const char* name);

Eo* action_label_new(
      const JkAction* action,
      const char* name);

Eo* action_entry_new(
      JkAction* action,
      const char* name,
      void* data,
      entry_callback fn);

void jk_label_set(
      Eo* label,
      const char* name);

void action_show(
      JkAction* action,
      bool b);

#endif

