//#define EFL_BETA_API_SUPPORT
#include <Elementary.h>
#include <Eo.h>
#include "elm_widget.h"
#include "jk_entry.eo.h"
//#include <Ecore_Evas.h>
//
#undef MY_CLASS

#define MY_CLASS JK_ENTRY_CLASS
#define MY_CLASS_NAME_LEGACY "jk_entry"

#ifndef CRI
#define CRI(...) EINA_LOG_DOM_CRIT(1, __VA_ARGS__)
#endif

#define JK_ENTRY_DATA_GET(o, sd) \
 Jk_Entry_Data * sd = eo_data_scope_get(o, JK_ENTRY_CLASS)

/*
#define ELM_SPINNER_DATA_GET_OR_RETURN(o, ptr)       \
ELM_SPINNER_DATA_GET(o, ptr);                      \
if (EINA_UNLIKELY(!ptr))                           \
{                                                \
CRI("No widget data for object %p (%s)",      \
o, evas_object_type_get(o));              \
return;                                       \
}

#define ELM_SPINNER_DATA_GET_OR_RETURN_VAL(o, ptr, val) \
ELM_SPINNER_DATA_GET(o, ptr);                         \
if (EINA_UNLIKELY(!ptr))                              \
{                                                   \
CRI("No widget data for object %p (%s)",         \
o, evas_object_type_get(o));                 \
return val;                                      \
}

#define ELM_SPINNER_CHECK(obj)                              \
if (EINA_UNLIKELY(!eo_isa((obj), ELM_SPINNER_CLASS))) \
return
*/


enum _State
{
  STATE_SHOW,
  STATE_MOUSE_DOWN,
  STATE_MOVE,
  STATE_ENTRY,
  STATE_AFTER_MOVE,
};


typedef struct
{
  Eo* rect;
  Eo* entry;
  int state;
  Evas_Coord startx, starty;
  Eina_Bool want_select;
  double value;
  double value_saved;
  char* value_str;
  char* value_saved_str;
  int diff;

} Jk_Entry_Data;

static char *user_style =
//"DEFAULT='font_size=8 color=#F00 align=center'"
"DEFAULT='align=center'"
"em='+ backing=on backing_color=#FFF'"
"grn='+ color=#0F0'"
"ul='+ underline=on underline_color=#AAA'";


EOLIAN static Eo*
_jk_entry_eo_base_constructor(Eo *obj, Jk_Entry_Data *pd EINA_UNUSED)
{
  //obj = eo_do_super_ret(obj, JK_ENTRY_CLASS, obj, eo_constructor());
  obj = eo_constructor(eo_super(obj, JK_ENTRY_CLASS));
  efl_canvas_object_type_set(obj, MY_CLASS_NAME_LEGACY);
  return obj;
}

void _value_set(Jk_Entry_Data* pd, double val)
{
  pd->value = val;

  int size = 128;
  if (!pd->value_str) {
    // "value is null so create
    pd->value_str = calloc(1, size);
  }

  snprintf(pd->value_str, size, "%.3f", val);
  elm_object_text_set(pd->entry, pd->value_str);
}


static void
_ondown(
      void *data EINA_UNUSED,
      Evas_Object *o EINA_UNUSED,
      const char  *emission,
      const char  *source)

{
  //_sig_print(emission, source);
  Jk_Entry_Data* pd = data;
  printf(" on down : %s, %s, %s \n", emission, source, elm_object_text_get(pd->entry));
  pd->state = STATE_MOUSE_DOWN;
  pd->diff = 0;
  pd->value_saved = pd->value;

  if (pd->value_saved_str) free(pd->value_saved_str);
  pd->value_saved_str = strdup(pd->value_str);

  Evas* e = evas_object_evas_get(o);
  evas_pointer_output_xy_get(e, &pd->startx, &pd->starty);
  elm_object_scroll_hold_push(o);
}

static void
_onmove(
      void *data EINA_UNUSED,
      Evas_Object *o EINA_UNUSED,
      const char  *emission,
      const char  *source)

{
  Eo* parent = data;
  JK_ENTRY_DATA_GET(parent, pd);

  Evas* e = evas_object_evas_get(o);
  Evas_Coord mx, my;
  evas_pointer_output_xy_get(e, &mx, &my);
  if (pd->state == STATE_MOUSE_DOWN){
    if (mx != pd->startx || my != pd->starty) {
      pd->state = STATE_MOVE;
    }
  }
  if (pd->state == STATE_MOVE) {
    pd->diff += mx - pd->startx;
    //printf(" on move : %s, %s, %d, %d, diff : %d \n", emission, source, pd->startx, mx, pd->diff);
    _value_set(pd, pd->value_saved + 0.5f * pd->diff);
    //eo_do(parent, eo_event_callback_call(JK_ENTRY_EVENT_CHANGED, NULL));
    eo_event_callback_call(parent, JK_ENTRY_EVENT_CHANGED, NULL);
    //efl_event_callback_legacy_call(parent, JK_ENTRY_EVENT_CHANGED, NULL);
    Ecore_Evas *ee = ecore_evas_ecore_evas_get(e);
    ecore_evas_pointer_warp(ee, pd->startx, my);
  }
}

static void
_onup(
      void *data EINA_UNUSED,
      Evas_Object *o EINA_UNUSED,
      const char  *emission,
      const char  *source)

{
  Eo* parent = data;
  JK_ENTRY_DATA_GET(parent, pd);
  printf(" on up : %s, %s \n", emission, source);
  elm_object_scroll_hold_pop(o);
  if (pd->state == STATE_MOVE) {
    pd->state = STATE_AFTER_MOVE;
  }
  else {
    pd->state = STATE_SHOW;
  }
  //eo_do(parent, eo_event_callback_call(JK_ENTRY_EVENT_CHANGED_END, NULL));
  eo_event_callback_call(parent, JK_ENTRY_EVENT_CHANGED_END, NULL);
}

static void
_show_entry(Eo* o, Jk_Entry_Data* pd, Eina_Bool b)
{
  if (pd->state == STATE_ENTRY ||
        pd->state == STATE_MOVE) {
    return;
  }

  pd->state = STATE_ENTRY;
  printf("SHOW ENTRY \n");
  elm_layout_signal_emit(o, "visible,0", "bg");
  elm_entry_editable_set(pd->entry, EINA_TRUE);
  pd->value_saved = pd->value;

  if (pd->value_saved_str) free(pd->value_saved_str);
  pd->value_saved_str = strdup(pd->value_str);

  elm_entry_text_style_user_push(pd->entry, user_style);
  elm_entry_select_all(pd->entry);
  //elm_object_focus_set(pd->entry, EINA_TRUE);
  pd->want_select = EINA_TRUE;

}

static void
_onclicked(
      void *data EINA_UNUSED,
      Evas_Object *o EINA_UNUSED,
      const char  *emission,
      const char  *source)

{
  Jk_Entry_Data* pd = data;
  printf(" 00000 on clicked : %s, %s, %s, state : %d \n", emission, source, elm_object_text_get(pd->entry), pd->state);

  if (pd->state == STATE_AFTER_MOVE)
  {
    pd->state = STATE_SHOW;
    return;
  }

  if (!(pd->state == STATE_MOUSE_DOWN || pd->state == STATE_SHOW)) {
    return;
  }


  //_sig_print(emission, source);
  printf(" on clicked : %s, %s, %s \n", emission, source, elm_object_text_get(pd->entry));
  _show_entry(o, pd, EINA_TRUE);
}

static void
_entry_activated(
      void* data,
      Evas_Object *o,
      void* event)
{
  Eo* parent = data;
  JK_ENTRY_DATA_GET(parent, pd);

  pd->state = STATE_SHOW;

  //printf("leaving entry \n");

  Eo* smart = evas_object_data_get(o, "smart");

  elm_layout_signal_emit(smart, "visible,1", "bg");
  elm_entry_editable_set(o, EINA_FALSE);

  elm_entry_text_style_user_push(o, user_style);
  pd->want_select = EINA_FALSE;

  const char* str = elm_object_text_get(o);
  if (!str) return;
  if (pd->value_saved_str && !strcmp(pd->value_saved_str, str)) return;
  char* end;
  double n = strtod(str, &end);

  printf("entry activated : %f, %f, %f \n", pd->value_saved, pd->value, n);

  if (n == pd->value_saved) return;

  pd->value = n;

  printf("wrote %s, %f,, ENTRY ACTIVATED will send changed signal \n ", str, pd->value);
  //eo_do(parent, eo_event_callback_call(JK_ENTRY_EVENT_CHANGED_END, NULL));
   eo_event_callback_call(parent, JK_ENTRY_EVENT_CHANGED_END, NULL);
}

static void
_entry_unfocused(
      void* data,
      Evas_Object *o,
      void* event)
{
  Eo* parent = data;
  JK_ENTRY_DATA_GET(parent, pd);

  const char* name = evas_object_name_get(o);
  //printf("entry unfocused ::: %s  \n", name);
  pd->state = STATE_SHOW;

  Eo* smart = evas_object_data_get(o, "smart");

  elm_layout_signal_emit(smart, "visible,1", "bg");
  elm_entry_editable_set(o, EINA_FALSE);

  elm_entry_text_style_user_push(o, user_style);
  pd->want_select = EINA_FALSE;

  const char* str = elm_object_text_get(o);
  if (!str) return;
  printf("entry unfocuseddddddd STR : %s, %s, %s \n", pd->value_saved_str, pd->value_str, str);
  if (pd->value_saved_str && !strcmp(pd->value_saved_str, str)) return;
  char* end;
  double n = strtod(str, &end);

  printf("entry unfocuseddddddd : %f, %f, %f \n", pd->value_saved, pd->value, n);

  if (n == pd->value_saved) return;

  pd->value = n;

  printf("wrote %s, %f,, ENTRY UNFOCUSED will send changed signal \n ", str, pd->value);
  //eo_do(parent, eo_event_callback_call(JK_ENTRY_EVENT_CHANGED_END, NULL));
  eo_event_callback_call(parent, JK_ENTRY_EVENT_CHANGED_END, NULL);
}

static void
_entry_changed(
      void* data,
      Evas_Object *o,
      void* event)
{
  Eo* parent = data;
  JK_ENTRY_DATA_GET(parent, pd);

  const char* str = elm_object_text_get(o);
  if (!str) return;
  char* end;
  double n = strtod(str, &end);

  //printf("entry changed : %f, %f, %f \n", pd->value_saved, pd->value, n);

  if (n == pd->value) return;

  pd->value = n;

  //printf("wrote %s, %f,, ENTRY CHANGED will send changed signal \n ", str, pd->value);
  //eo_do(parent, eo_event_callback_call(JK_ENTRY_EVENT_CHANGED, NULL));
  eo_event_callback_call(parent, JK_ENTRY_EVENT_CHANGED, NULL);
}


static void
_entry_cleared(
      void* data,
      Evas_Object *o,
      void* event)
{
  const char* name = evas_object_name_get(o);
  printf("entry cleared ::: %s  \n", name);

  //Eo* smart = evas_object_data_get(o, "smart");
  Jk_Entry_Data* pd = data;
  //if ( pd->state == STATE_ENTRY && pd->want_select) {
  if (pd->want_select) {
    printf("entry cleared but select all ::: %s  \n", name);
    pd->want_select = EINA_FALSE;
    //elm_entry_select_all(o);
  }
  else {
    printf("entry cleared but do nothing ::: %s  \n", name);
  }
}


static void
_select_all(
      void* data,
      Evas_Object *o,
      void* event)
{
  const char* name = evas_object_name_get(o);
  printf("focused, select all ::: %s  \n", name);
  elm_entry_select_all(o);
}

static void
_print_signal(
      void* data,
      Evas_Object *o,
      void* event)
{
  const char* name = evas_object_name_get(o);
  printf("signal from  %s :::::  %s \n", name,  data);
}

//static int test = 1;

static void
_onfocused(
      void* data,
      Evas_Object *o,
      void* event)
{
  const char* t = elm_object_text_get(o);
   printf("JKJKJKJKJon focused from : %s ###### \n", t);
   elm_entry_select_all(o);
}

static void
_drag_cb(void *data,
         Evas_Object *_obj EINA_UNUSED,
         const char *emission EINA_UNUSED,
         const char *source EINA_UNUSED)
{
  // printf("drag cb \n");
  /*
  int x, y;
  evas_object_geometry_get(obj, &x, &y, NULL, NULL);
  printf("drag cb %d, %d \n", x, y);
  */

  Eo* obj = data;
  ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd);

  double pos;
  //eo_do((Eo *)wd->resize_obj,
   //     edje_obj_part_drag_value_get("bg", &pos, NULL));

  edje_obj_part_drag_value_get((Eo*) wd->resize_obj,"bg", &pos, NULL);

  //printf("drag cb pos %f \n", pos);
}

static void
_drag_start_cb(void *data,
         Evas_Object *obj EINA_UNUSED,
         const char *emission EINA_UNUSED,
         const char *source EINA_UNUSED)
{
  int x, y;
  evas_object_geometry_get(obj, &x, &y, NULL, NULL);
  printf("drag start cb %d, %d \n", x, y);
  Eo* parent = data;
  JK_ENTRY_DATA_GET(parent, pd);
  pd->value_saved = pd->value;

  if (pd->value_saved_str) free(pd->value_saved_str);
  pd->value_saved_str = strdup(pd->value_str);
}

static void
_drag_stop_cb(void *data,
         Evas_Object *_obj EINA_UNUSED,
         const char *emission EINA_UNUSED,
         const char *source EINA_UNUSED)
{
   printf("drag stop cb \n");
}

EOLIAN static void
//_jk_entry_evas_object_smart_add(Eo *obj, Jk_Entry_Data *pd)
_jk_entry_efl_canvas_group_group_add(Eo *obj, Jk_Entry_Data *pd)
{
  ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd);
  //JK_ENTRY_DATA_GET(obj, ed);

  //eo_do_super(obj, JK_ENTRY_CLASS, evas_obj_smart_add());
  efl_canvas_group_add(eo_super(obj, JK_ENTRY_CLASS));
  elm_widget_sub_object_parent_add(obj);

  /*
     pd->rect = evas_object_rectangle_add(evas_object_evas_get(obj));
  //evas_object_color_set(pd->rect, rand() % 255, rand() % 255, rand() % 255, 255/2);
  evas_object_show(pd->rect);
  evas_object_color_set(pd->rect, rand() % 255, rand() % 255, rand() % 255, 255/2);
  int r,g,b,a;
  evas_object_color_get(pd->rect, &r, &g, &b, &a);
  printf("color before : %d, %d, %d, %d \n", r, g, b, a);
  // evas_object_smart_member_add(pd->rect, obj);
  //elm_layout_content_set(obj, "elm.swallow.content", pd->rect);
  evas_object_color_get(pd->rect, &r, &g, &b, &a);
  printf("color after : %d, %d, %d, %d \n", r, g, b, a);
  evas_object_color_set(pd->rect, rand() % 255, rand() % 255, rand() % 255, 255/2);

  elm_widget_sub_object_add(obj, pd->rect);

  evas_object_color_get(pd->rect, &r, &g, &b, &a);
  printf("color after 222: %d, %d, %d, %d \n", r, g, b, a);

*/


  elm_layout_file_set(obj, "edc/entry.edj", "main");

  Evas_Object* en = elm_entry_add(obj);
  elm_entry_single_line_set(en, EINA_TRUE);
  elm_entry_editable_set(en, EINA_FALSE);
  pd->entry = en;

  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
  //evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
  //evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_object_text_set(en, "<align=center>hello</align>");
  //elm_entry_text_style_user_push(en, "DEFAULT='align=center'");
  //elm_entry_text_style_user_push(en, "DEFAULT='color=#0f0'");
  elm_entry_text_style_user_push(en, user_style);
  evas_object_data_set(obj, "realentry", en);

  const char* cur_style = elm_entry_text_style_user_peek(en);

  /*
  if (cur_style)
  printf("Current style user: %s\n", cur_style);
  else
  printf("Style user stack is empty.\n");
  */

  const char* yep = "aaa";
  /*
  elm_object_text_set(en, "aaa");
  if (test == 1)
  yep = "xxx";
  if (test == 2)
  yep = "yyy";
  if (test == 3)
  yep = "zzz";
  test++;
  */

  elm_object_text_set(en, yep);
  evas_object_name_set(en, yep);

  //elm_entry_scrollable_set(en, EINA_TRUE);
  //elm_entry_scrollbar_policy_set(en,
  //      ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);

  //evas_object_smart_member_add(rect, en);
  elm_layout_content_set(obj, "content", en);
  elm_widget_sub_object_add(obj, en);
  evas_object_show(en);


  elm_widget_can_focus_set(obj, EINA_TRUE);
  elm_layout_sizing_eval(obj);
  evas_object_data_set(en, "smart", obj);

  evas_object_smart_callback_add(en, "activated", _entry_activated, obj);
  evas_object_smart_callback_add(en, "unfocused", _entry_unfocused, obj);
  evas_object_smart_callback_add(en, "changed,user", _entry_changed, obj);
  //evas_object_smart_callback_add(en, "focused", _select_all, pd);
  //evas_object_smart_callback_add(en, "selection,changed", _print_signal, "selection changed");
  evas_object_smart_callback_add(en, "selection,cleared", _entry_cleared, pd);
  //evas_object_smart_callback_add(en, "selection,start", _print_signal, "selection start");
  //evas_object_smart_callback_add(en, "clicked", _print_signal, "clicked");
  //evas_object_smart_callback_add(en, "cursor,changed", _print_signal, "cursor,changed");
  //evas_object_smart_callback_add(en, "cursor,changed,manual", _print_signal, "cursor,changed,manual");

  elm_layout_signal_callback_add(obj, "mouse,down,1", "bg",_ondown, pd);
  elm_layout_signal_callback_add(obj, "mouse,move", "bg", _onmove, obj);
  elm_layout_signal_callback_add(obj, "mouse,up,1", "bg", _onup, obj);
  elm_layout_signal_callback_add(obj, "mouse,clicked,1", "bg", _onclicked, pd);

  elm_layout_signal_callback_add(obj, "drag", "*", _drag_cb, obj);
  elm_layout_signal_callback_add(obj, "drag,start", "*", _drag_start_cb, obj);
  elm_layout_signal_callback_add(obj, "drag,stop", "*", _drag_stop_cb, obj);
  elm_layout_signal_callback_add(obj, "drag,step", "*", _drag_stop_cb, obj);
  elm_layout_signal_callback_add(obj, "drag,page", "*", _drag_stop_cb, obj);

}

EOLIAN static void
//_jk_entry_evas_object_smart_del(Eo *obj, Jk_Entry_Data *pd)
_jk_entry_efl_canvas_group_group_del(Eo *obj, Jk_Entry_Data *pd)
{
  //eo_do_super(obj, MY_CLASS, evas_obj_smart_del());
  //evas_obj_smart_del(eo_super(obj), MY_CLASS);
  efl_canvas_group_del(eo_super(obj, MY_CLASS));
  if (pd->value_saved_str) free(pd->value_saved_str);
  if (pd->value_str) free(pd->value_str);
}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_focus_next_manager_is(Eo *obj, Jk_Entry_Data *pd)
{
  printf("focus next manager is %s \n", __FUNCTION__);
  return EINA_FALSE;
}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_focus_direction_manager_is(Eo *obj, Jk_Entry_Data *pd)
{
  printf("jkjkjkjkjkjk %s \n", __FUNCTION__);
  return EINA_FALSE;
}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_focus_next(
      Eo *obj,
      Jk_Entry_Data *pd,
      Elm_Focus_Direction dir, Evas_Object **next, Elm_Object_Item **next_item)
{
  printf("jkjk %s \n", __FUNCTION__);
  return EINA_FALSE;
}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_focus_direction(Eo *obj, Jk_Entry_Data *pd, const Evas_Object *base, double degree, Evas_Object **direction, Elm_Object_Item **direction_item, double *weight)
{
  printf("jkjk %s \n", __FUNCTION__);
  return EINA_FALSE;
}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_on_focus(Eo *obj, Jk_Entry_Data *pd, Elm_Object_Item* item)
{
  printf("jk entry on focus\n");
  Eina_Bool int_ret = EINA_FALSE;
  //eo_do_super(obj, MY_CLASS, int_ret = elm_obj_widget_on_focus(NULL));
  int_ret = elm_obj_widget_on_focus(eo_super(obj, MY_CLASS),NULL);
  if (!int_ret) return EINA_FALSE;

  return EINA_TRUE;
}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_event(Eo *obj, Jk_Entry_Data *pd, Evas_Object *source, Evas_Callback_Type type, void *event_info)
{
  printf("jkjkjkjkjkjk %s \n", __FUNCTION__);
  return EINA_FALSE;
}

EOLIAN static void
_jk_entry_elm_layout_sizing_eval(Eo *obj, Jk_Entry_Data *pd)
{
  Evas_Coord minw = -1, minh = -1;
  ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd);

  elm_coords_finger_size_adjust(1, &minw, 1, &minh);
  //printf("finger size adjust : %d, %d \n", minw, minh);
  edje_object_size_min_restricted_calc
   (wd->resize_obj, &minw, &minh, minw, minh);
  //printf("after calc : %d, %d \n", minw, minh);
  elm_coords_finger_size_adjust(1, &minw, 1, &minh);
  //printf("after calc, then adjust : %d, %d \n", minw, minh);
  evas_object_size_hint_min_set(obj, minw, minh);
  evas_object_size_hint_max_set(obj, -1, -1);
}

EOLIAN static void
_jk_entry_min_max_set(Eo *obj, Jk_Entry_Data *pd, double min, double max)
{

}

EOLIAN static void
_jk_entry_min_max_get(Eo *obj, Jk_Entry_Data *pd, double *min, double *max)
{

}

EOLIAN static void
_jk_entry_step_set(Eo *obj, Jk_Entry_Data *pd, double step)
{

}

EOLIAN static double
_jk_entry_step_get(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static void
_jk_entry_wrap_set(Eo *obj, Jk_Entry_Data *pd, Eina_Bool wrap)
{

}

EOLIAN static Eina_Bool
_jk_entry_wrap_get(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static void
_jk_entry_interval_set(Eo *obj, Jk_Entry_Data *pd, double interval)
{

}

EOLIAN static double
_jk_entry_interval_get(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static void
_jk_entry_round_set(Eo *obj, Jk_Entry_Data *pd, int rnd)
{

}

EOLIAN static int
_jk_entry_round_get(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static void
_jk_entry_editable_set(Eo *obj, Jk_Entry_Data *pd, Eina_Bool editable)
{

}

EOLIAN static Eina_Bool
_jk_entry_editable_get(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static void
_jk_entry_base_set(Eo *obj, Jk_Entry_Data *pd, double base)
{

}

EOLIAN static double
_jk_entry_base_get(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static void
_jk_entry_value_set(Eo *obj, Jk_Entry_Data *pd, double val)
{
  _value_set(pd, val);
}

EOLIAN static double
_jk_entry_value_get(Eo *obj, Jk_Entry_Data *pd)
{
  printf("value get : %f \n", pd->value);
  return pd->value;
}

EOLIAN static void
_jk_entry_label_format_set(Eo *obj, Jk_Entry_Data *pd, const char *fmt)
{

}

EOLIAN static const char *
_jk_entry_label_format_get(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static void
_jk_entry_special_value_add(Eo *obj, Jk_Entry_Data *pd, double value, const char *label)
{

}

EOLIAN static void
_jk_entry_class_constructor(Eo_Class *klass)
{
   evas_smart_legacy_type_register(MY_CLASS_NAME_LEGACY, klass);
}

EOLIAN static void
_jk_entry_evas_object_smart_move(Eo *obj, Jk_Entry_Data *pd, Evas_Coord x, Evas_Coord y)
{
  //eo_do_super(obj, MY_CLASS, evas_obj_smart_move(x, y));
  efl_canvas_group_move(eo_super(obj, MY_CLASS), x, y);

  //evas_object_move(pd->rect, x, y);
}

EOLIAN static void
_jk_entry_evas_object_smart_resize(Eo *obj, Jk_Entry_Data *pd, Evas_Coord w, Evas_Coord h)
{
  //eo_do_super(obj, MY_CLASS, evas_obj_smart_resize(w, h));
  efl_canvas_group_resize(eo_super(obj, MY_CLASS), w, h);

  //evas_object_resize(pd->rect, w, h);
}

EOLIAN static double
_jk_entry_value_saved_get(Eo *obj, Jk_Entry_Data *pd)
{
  return pd->value_saved;
}

/*
EOLIAN static Efl_Object *
_jk_entry_efl_object_constructor(Eo *obj, Jk_Entry_Data *pd)
{

  obj = efl_constructor(efl_super(obj, JK_ENTRY_CLASS));
  return obj;

}
*/

Evas_Object*
jk_entry_add(Evas_Object *parent)
{
   EINA_SAFETY_ON_NULL_RETURN_VAL(parent, NULL);
   Evas_Object *obj = eo_add(MY_CLASS, parent);
   return obj;
}


#include "jk_entry.eo.c"
