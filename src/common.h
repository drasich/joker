#ifndef __ui_common__
#define __ui_common__
#include <Elementary.h>
#include "stdbool.h"

typedef void (*button_callback)(void *data);
typedef void (*entry_callback)(void *data, const char* text);
typedef void (*select_callback)(void *data, const char* name);

typedef struct _ButtonCallbackData ButtonCallbackData;
struct _ButtonCallbackData
{
  void* data;
  button_callback fn;
};

typedef struct _EntryCallbackData EntryCallbackData;
struct _EntryCallbackData
{
  void* data;
  entry_callback fn;
};

void btn_cb_set(
      Eo* bt,
      button_callback fn,
      void* data);


void object_show(Evas_Object* o, bool b);

typedef void (*panel_geom_cb)(
      void* data, int x, int y, int w, int h);

#endif
