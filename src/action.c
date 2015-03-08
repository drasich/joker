#include "action.h"
#include "tree.h"
#define __UNUSED__

void _add_buttons(Evas_Object* win, Evas_Object* box);


JkAction* widget_action_new(Evas_Object* win)
{
  printf("tree widget new !!win: %p \n",win);
  JkAction *a = calloc(1, sizeof *a);

  Evas_Object *bx, *frame;

  bx = elm_box_add(win);
  a->box = bx;
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(bx);
  a->root = bx;

  elm_box_horizontal_set(bx, EINA_TRUE);
  //evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(bx);

  _add_buttons(win, bx);

  return a;
}

static void
_button_callback(
      void *data,
      Evas_Object *obj,
      void *event_info)
{
  ButtonCallbackData* bcd = data;
  bcd->fn(bcd->data);
}

void
action_button_new(
      JkAction* action,
      const char* name,
      void* data,
      button_callback fn)
{
  Evas_Object* win = action->root;
  Evas_Object* box = action->box;

  Evas_Object* bt = elm_button_add(win);
  elm_object_focus_allow_set(bt, 0);

  elm_object_text_set(bt, name);
  evas_object_show(bt);
  elm_box_pack_end(box, bt);

  int r,g,b,a;
  evas_object_color_get(bt, &r,&g,&b,&a);
  float f = 0.7f;
  r *= f;
  g *= f;
  b *= f;
  a *= f;

  evas_object_color_set(bt, r,g,b,a);
  //evas_object_resize(bt, 100, 25);
  //evas_object_move(bt, 15, 15);
  //evas_object_data_set(bt, "view", v);

  ButtonCallbackData* bcd = calloc(1, sizeof *bcd);
  bcd->data = data;
  bcd->fn = fn;
  evas_object_smart_callback_add(bt, "clicked", _button_callback, bcd);
}

void _add_buttons(Evas_Object* win, Evas_Object* box)
{
  Evas_Object* fs_bt, *ic, *bt;
  int r,g,b,a;

  ic = elm_icon_add(win);
  elm_icon_standard_set(ic, "file");
  evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);

  bt = elm_button_add(win);
  elm_object_focus_allow_set(bt, 0);

  elm_object_text_set(bt, "Add empty");
  evas_object_show(bt);
  elm_box_pack_end(box, bt);

  evas_object_color_get(bt, &r,&g,&b,&a);
  float f = 0.7f;
  r *= f;
  g *= f;
  b *= f;
  a *= f;

  evas_object_color_set(bt, r,g,b,a);
  evas_object_resize(bt, 100, 25);
  evas_object_move(bt, 15, 15);
  //evas_object_data_set(bt, "view", v);
  //evas_object_smart_callback_add(bt, "clicked", _new_empty, v);

  /////////////////////////////////////////////////////////

  bt = elm_button_add(win);
  elm_object_focus_allow_set(bt, 0);
  elm_object_text_set(bt, "Add prefab");
  evas_object_show(bt);
  elm_box_pack_end(box, bt);

  evas_object_color_set(bt, r,g,b,a);
  //evas_object_data_set(bt, "view", v);
  //evas_object_smart_callback_add(bt, "clicked", _new_object_prefab, v);

  /////////////////////////////////////////////////////////

  bt = elm_button_add(win);
  elm_object_focus_allow_set(bt, 0);

  elm_object_text_set(bt, "play");
  elm_box_pack_end(box, bt);
  evas_object_show(bt);

  evas_object_color_set(bt, r,g,b,a);
  evas_object_resize(bt, 50, 25);
  evas_object_move(bt, 155, 15);
  //evas_object_data_set(bt, "view", v);
  //evas_object_smart_callback_add(bt, "clicked", _play, v);

  ///////////////////////////

  bt = elm_button_add(win);
  elm_object_focus_allow_set(bt, 0);

  elm_object_text_set(bt, "pause");
  elm_box_pack_end(box, bt);
  evas_object_show(bt);

  evas_object_color_set(bt, r,g,b,a);
  evas_object_resize(bt, 50, 25);
  evas_object_move(bt, 205, 15);
  //evas_object_data_set(bt, "view", v);
  //evas_object_smart_callback_add(bt, "clicked", _pause, v);

  ////////////////////////////////
  bt = elm_button_add(win);
  elm_object_focus_allow_set(bt, 0);

  elm_object_text_set(bt, "add component");
  elm_box_pack_end(box, bt);
  evas_object_show(bt);

  evas_object_color_set(bt, r,g,b,a);
  evas_object_resize(bt, 100, 25);
  evas_object_move(bt, 275, 15);
  //evas_object_data_set(bt, "view", v);
  //evas_object_smart_callback_add(bt, "clicked", _addcomponent, v);

  ////////////////////////////////
  bt = elm_button_add(win);
  elm_object_focus_allow_set(bt, 0);

  elm_object_text_set(bt, "reload");
  elm_box_pack_end(box, bt);
  evas_object_show(bt);

  evas_object_color_set(bt, r,g,b,a);
  evas_object_resize(bt, 50, 25);
  evas_object_move(bt, 405, 15);
  //evas_object_data_set(bt, "view", v);
  //evas_object_smart_callback_add(bt, "clicked", _reload, v);

  //////////////////////////////////////

  bt = elm_button_add(win);
  elm_object_focus_allow_set(bt, 0);

  elm_object_text_set(bt, "save");
  elm_box_pack_end(box, bt);
  evas_object_show(bt);

  evas_object_color_set(bt, r,g,b,a);
  //evas_object_resize(bt, 50, 25);
  //evas_object_move(bt, 405, 15);
  //evas_object_data_set(bt, "view", v);
  //evas_object_smart_callback_add(bt, "clicked", _save, v);



  ////////////


  Evas_Object* tg = elm_check_add(win);
  evas_object_color_set(tg, r,g,b,a);
  //evas_object_move(tg, 15, 45);
  //evas_object_resize(tg, 200, 25);
  elm_object_style_set(tg, "toggle");
  elm_object_text_set(tg, "Dragger");
  elm_object_part_text_set(tg, "on", "Local");
  elm_object_part_text_set(tg, "off", "Global");
  //elm_box_pack_end(bx, tg);
  elm_box_pack_end(box, tg);
  evas_object_show(tg);
  //evas_object_smart_callback_add(tg, "changed", _dragger_global_local_changed_cb, v);



}

