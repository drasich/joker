#include "action.h"
#include "tree.h"
#include "common.h"
#define __UNUSED__

//TODO remove this fn
void _add_buttons(Evas_Object* win, Evas_Object* box);

static JkAction* widget_action_new(Evas_Object* win)
{
  JkAction *a = calloc(1, sizeof *a);
  a->win = win;

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

Evas_Object*
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

  btn_cb_set(bt, fn ,data);

  return bt;
}

Evas_Object*
action_button_new1(
      JkAction* action,
      const char* name)
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


  return bt;
}

//TODO move the local/global check and remove this function.
void _add_buttons(Evas_Object* win, Evas_Object* box)
{
  Evas_Object* tg = elm_check_add(win);
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

void
action_show(
      JkAction* action,
      bool b)
{
  object_show(action->win, b);
}


JkAction*
window_action_new(Window* w)
{
  Eo* win = w->win;

  Eo* tb = elm_table_add(win);
  evas_object_size_hint_weight_set(tb, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //evas_object_size_hint_align_set(tb, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_win_resize_object_add(win, tb);
  evas_object_show(tb);

  Eo* panel = elm_panel_add(win);
  elm_panel_orient_set(panel, ELM_PANEL_ORIENT_BOTTOM);
  //evas_object_size_hint_weight_set(panel, 0, EVAS_HINT_EXPAND);
  evas_object_size_hint_weight_set(panel, 0, 0);
  evas_object_size_hint_align_set(panel, 0.5, 0);
  //elm_box_pack_end(tb, panel);
  elm_table_pack(tb, panel,0, 4, 4, 1);
  evas_object_show(panel);

  JkAction* a = widget_action_new(panel);
  evas_object_size_hint_weight_set(a->root, EVAS_HINT_EXPAND, 0);
  elm_object_content_set(panel, a->root);

  return a;
}


JkAction*
window_action_new_up(Window* w)
{
  Eo* win = w->win;

  Eo* tb = elm_box_add(win);
  evas_object_size_hint_weight_set(tb, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, tb);
  evas_object_show(tb);

  Eo* panel = elm_panel_add(win);
  elm_panel_orient_set(panel, ELM_PANEL_ORIENT_TOP);
  evas_object_size_hint_weight_set(panel, 0, 0);
  evas_object_size_hint_align_set(panel, 0.5, 0);
  elm_box_pack_end(tb, panel);
  evas_object_show(panel);

  JkAction* a = widget_action_new(panel);
  evas_object_size_hint_weight_set(a->root, EVAS_HINT_EXPAND, 0);
  elm_object_content_set(panel, a->root);

  return a;
}



void
action_menu_new(
      JkAction* action,
      const char* name)
{
  //TODO
}

void
action_menu_add(
      JkAction* action,
      const char* menu_name,
      const char* name,
      button_callback fn,
      void* data)
{
  //TODO
}

JkLabel* action_label_new(
      const JkAction* action,
      const char* name)
{
  Evas_Object* win = action->root;
  Evas_Object* box = action->box;

  Evas_Object* l = elm_label_add(win);
  elm_object_text_set(l, name);
  evas_object_show(l);
  elm_box_pack_end(box, l);
  return l;
}

void jk_label_set(
      const JkLabel* label,
      const char* name)
{
  elm_object_text_set(label, name);
}

static Evas_Object *create_edje(Evas* e)
{
  Evas_Object *edje;

  edje = edje_object_add(e);
  if (!edje) {
    EINA_LOG_CRIT("could not create edje object!");
    return NULL;
   }

  if (!edje_object_file_set(edje, "edc/entry_min.edj", "main")) {
    int err = edje_object_load_error_get(edje);
    const char *errmsg = edje_load_error_str(err);
    EINA_LOG_ERR("could not load 'my_group' from .edj file : %s",
          errmsg);

    evas_object_del(edje);
    return NULL;
   }

  return edje;
}

static void
_entry_focused_cb(
      void* data,
      Evas_Object *obj,
      void* event)
{
  const char* value = elm_object_text_get(obj);
  evas_object_data_set(obj, "saved_text", eina_stringshare_add(value));
  printf("setting saved text to %s \n", value);
}

static void
_entry_register_change_cb(
      void* data,
      Evas_Object *obj,
      void* event)
{
  printf("entry activated or unfocused!!!!!!!!!!!!!!.\n");
  //const char* name = evas_object_name_get(obj);
  const char* value = elm_object_text_get(obj);
  const char* old = evas_object_data_get(obj, "saved_text");

  printf("before old value......... ::: %s\n", old);

  if (old == NULL) {
    printf("problem with the old value.........\n");
    return;
  }

  evas_object_data_set(obj, "saved_text", eina_stringshare_add(value));

  printf("after old value......... ::: %s\n", old);

  EntryCallbackData* ecd = data;

  if (ecd->fn) {
    ecd->fn(ecd->data, value);
  }
}




JkEntry* action_entry_new(
      JkAction* action,
      const char* name,
      void* data,
      entry_callback fn)
{
  Evas_Object* win = action->root;
  Evas_Object* box = action->box;

	Eo* ly = elm_layout_add(win);
  elm_layout_file_set(ly, "edc/entry_min.edj", "main");
  evas_object_show(ly);

  Evas_Object* en = elm_entry_add(win);
  elm_object_part_content_set(ly, "entry", en);
  elm_entry_single_line_set(en, EINA_TRUE);
  elm_entry_scrollable_set(en, EINA_TRUE);
  elm_object_text_set(en, name);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_pack_end(box, ly);
  evas_object_show(en);

  //TODO
  EntryCallbackData* ecd = calloc(1, sizeof *ecd);
  ecd->data = data;
  ecd->fn = fn;
  //evas_object_smart_callback_add(bt, "clicked", _button_callback, bcd);

  //evas_object_smart_callback_add(en, "changed,user", _entry_changed_cb_list, val);
  evas_object_smart_callback_add(en, "focused", _entry_focused_cb, NULL);
  //evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, NULL);
  //evas_object_smart_callback_add(en, "press", _entry_press_cb, NULL);
  evas_object_smart_callback_add(en, "activated", _entry_register_change_cb, ecd);
  evas_object_smart_callback_add(en, "unfocused", _entry_register_change_cb, ecd);

  return en;
}

