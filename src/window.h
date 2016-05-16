#ifndef __window__
#define __window__
#include "stdbool.h"
#include "tree.h"
#include "property.h"
#include "input.h"
#include "cypher.h"

typedef struct _Window Window;

struct _Window
{
  Evas_Object* win;
  Evas_Object* edje;
  Evas_Object* glview;
  Evas_Object* rect;

  const void* data;
  jk_mouse_down mouse_down;
  jk_mouse_up mouse_up;
  jk_mouse_move mouse_move;
  jk_mouse_wheel mouse_wheel;
  jk_key_down key_down;
};

Window* window_new(int width,int height);

void tmp_func(
      Window* window,
      void* data,
      rust_callback init,
      rust_callback draw,
      resize_callback resize);

void window_callback_set(
      Window* w,
      const void* data,
      jk_mouse_down mouse_down,
      jk_mouse_up mouse_up,
      jk_mouse_move mouse_move,
      jk_mouse_wheel mouse_wheel,
      jk_key_down key_down
      );

void window_button_new(Window* w);

typedef void (*rust_elm_callback)(void* data);

void init_callback_set(rust_elm_callback cb, void* data);
bool init_callback_call();
void exit_callback_set(rust_elm_callback cb, void* data);
bool exit_callback_call();

JkProperty* window_property_new(Window* w);
JkPropertyList* jk_property_list_new(Window* w, int x, int y, int width, int height);

void window_rect_visible_set(Window* w, bool b);
void window_rect_set(Window* win, float x, float y, float w, float h);

//Evas_Object* jk_window_new();
Evas_Object* jk_window_new(rust_elm_callback cb, const void* cb_data);

//JkTree* window_tree_new(Window* w, int x, int y, int width, int height);
//
void jk_window_request_update(Window* w);

#endif
