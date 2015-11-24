#ifndef __ui_action__
#define __ui_action__
#include "stdbool.h"
#include <Elementary.h>
#include <Eina.h>
#include "window.h"

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

JkLabel* action_label_new(
      const JkAction* action,
      const char* name);

JkEntry* action_entry_new(
      JkAction* action,
      const char* name,
      void* data,
      button_callback fn);

void jk_label_set(
      const JkLabel* label,
      const char* name);

void action_show(
      JkAction* action,
      bool b);

#endif

