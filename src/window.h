#ifndef __window__
#define __window__
#include "stdbool.h"
#include "tree.h"
#include "property.h"
#include "action.h"
#include "command.h"

typedef struct _Window Window;

typedef void (*window_mouse_down)(
      const void* data,
      int mod_flag,
      int buttons,
      int x,
      int y,
      int timestamp
      );
typedef void (*window_mouse_up)(
      const void* data,
      int mod_flag,
      int buttons,
      int x,
      int y,
      int timestamp
      );
typedef void (*window_mouse_move)(
      const void* data,
      int mod_flag,
      int button,
      int cur_x,
      int cur_y,
      int prev_x,
      int prev_y,
      int timestamp
      );
typedef void (*window_mouse_wheel)(
      const void* data,
      int mod_flag,
      int direction,
      int z,
      int x,
      int y,
      int timestamp
      );
typedef void (*window_key_down)(
      const void* data,
      int mod_flag,
      char* keyname,
      const char* key,
      int timestamp
      );

struct _Window
{
  Evas_Object* win;
  Evas_Object* edje;
  Evas_Object* glview;
  Evas_Object* rect;

  const void* data;
  window_mouse_down mouse_down;
  window_mouse_up mouse_up;
  window_mouse_move mouse_move;
  window_mouse_wheel mouse_wheel;
  window_key_down key_down;
};

Window* window_new();
void tmp_func(
      Window* window,
      void* data,
      rust_callback init,
      rust_callback draw,
      resize_callback resize);

void window_callback_set(
      Window* w,
      const void* data,
      window_mouse_down mouse_down,
      window_mouse_up mouse_up,
      window_mouse_move mouse_move,
      window_mouse_wheel mouse_wheel,
      window_key_down key_down
      );

JkTree* window_tree_new(Window* w);
JkAction* window_action_new(Window* w);
JkCommand* window_command_new(Window* w);
void window_button_new(Window* w);

typedef void (*rust_elm_callback)(void* data);

void init_callback_set(rust_elm_callback cb, void* data);
bool init_callback_call();
void exit_callback_set(rust_elm_callback cb, void* data);
bool exit_callback_call();

JkProperty* window_property_new(Window* w);
JkPropertySet* jk_window_property_set_new(Window* w);
JkPropertyList* jk_property_list_new(Window* w);

void window_rect_visible_set(Window* w, bool b);
void window_rect_set(Window* win, float x, float y, float w, float h);

//Evas_Object* jk_window_new();
Evas_Object* jk_window_new(rust_elm_callback cb, const void* cb_data);
void jk_exit();



#endif
