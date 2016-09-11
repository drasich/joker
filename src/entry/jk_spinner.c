//#define EFL_BETA_API_SUPPORT
#define ELM_INTERFACE_ATSPI_ACCESSIBLE_PROTECTED
#define ELM_INTERFACE_ATSPI_VALUE_PROTECTED
#define ELM_INTERFACE_ATSPI_WIDGET_ACTION_PROTECTED

#ifndef CRI
#define CRI(...) EINA_LOG_DOM_CRIT(1, __VA_ARGS__)
#endif

#include <Elementary.h>
#include <elm_widget.h>
#include <Eo.h>

#include "jk_spinner.eo.h"

#define MY_CLASS JK_SPINNER_CLASS
#define MY_CLASS_NAME "Jk_Spinner"
#define MY_CLASS_NAME_LEGACY "jk_spinner"

typedef struct
{

} Jk_Spinner_Data;

#define JK_SPINNER_DATA_GET(o, sd) \
  Jk_Spinner_Data * sd = efl_data_scope_get(o, JK_SPINNER_CLASS)

#define JK_SPINNER_DATA_GET_OR_RETURN(o, ptr)       \
  JK_SPINNER_DATA_GET(o, ptr);                      \
  if (EINA_UNLIKELY(!ptr))                           \
    {                                                \
       CRI("No widget data for object %p (%s)",      \
           o, evas_object_type_get(o));              \
       return;                                       \
    }

#define JK_SPINNER_DATA_GET_OR_RETURN_VAL(o, ptr, val) \
  JK_SPINNER_DATA_GET(o, ptr);                         \
  if (EINA_UNLIKELY(!ptr))                              \
    {                                                   \
       CRI("No widget data for object %p (%s)",         \
           o, evas_object_type_get(o));                 \
       return val;                                      \
    }

#define JK_SPINNER_CHECK(obj)                              \
  if (EINA_UNLIKELY(!efl_isa((obj), JK_SPINNER_CLASS))) \
    return


static char *user_style =
//"DEFAULT='font_size=8 color=#F00 align=center'"
"DEFAULT='align=center'"
"em='+ backing=on backing_color=#FFF'"
"grn='+ color=#0F0'"
"ul='+ underline=on underline_color=#AAA'";


EOLIAN static Efl_Object *
_jk_spinner_efl_object_constructor(Eo *obj, Jk_Spinner_Data *pd)
{
   obj = efl_constructor(efl_super(obj, MY_CLASS));
   efl_canvas_object_type_set(obj, MY_CLASS_NAME_LEGACY);
   //evas_object_smart_callbacks_descriptions_set(obj, _smart_callbacks);
   elm_interface_atspi_accessible_role_set(obj, ELM_ATSPI_ROLE_SPIN_BUTTON);
   return obj;
}

EOLIAN static void
_jk_spinner_efl_canvas_group_group_add(Eo *obj, Jk_Spinner_Data *priv)
{
  printf("jk spinner group group add \n");
  ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd);
  JK_SPINNER_DATA_GET(obj, sd);


  efl_canvas_group_add(efl_super(obj, JK_SPINNER_CLASS));
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
  //pd->entry = en;

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

  /*
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
  */
}

EOLIAN static void
_jk_spinner_efl_canvas_group_group_del(Eo *obj, Jk_Spinner_Data *pd)
{
   efl_canvas_group_del(efl_super(obj, MY_CLASS));
}

EOLIAN static Elm_Theme_Apply
_jk_spinner_elm_widget_theme_apply(Eo *obj, Jk_Spinner_Data *pd)
{
  printf("theme apply!!!!!!!!!!!!!!! \n");

}

EOLIAN static Eina_Bool
_jk_spinner_elm_widget_focus_next_manager_is(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static Eina_Bool
_jk_spinner_elm_widget_focus_direction_manager_is(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_elm_widget_access(Eo *obj, Jk_Spinner_Data *pd, Eina_Bool acs)
{

}

EOLIAN static Eina_Bool
_jk_spinner_elm_widget_focus_next(Eo *obj, Jk_Spinner_Data *pd, Elm_Focus_Direction dir, Efl_Canvas_Object **next, Elm_Widget_Item **next_item)
{

}

EOLIAN static Eina_Bool
_jk_spinner_elm_widget_focus_direction(Eo *obj, Jk_Spinner_Data *pd, const Efl_Canvas_Object *base, double degree, Efl_Canvas_Object **direction, Elm_Widget_Item **direction_item, double *weight)
{

}

EOLIAN static Eina_Bool
_jk_spinner_elm_widget_on_focus(Eo *obj, Jk_Spinner_Data *pd, Elm_Widget_Item *item)
{

}

EOLIAN static Eina_Bool
_jk_spinner_elm_widget_event(Eo *obj, Jk_Spinner_Data *pd, Efl_Canvas_Object *source, Evas_Callback_Type type, void *event_info)
{

}

EOLIAN static void
_jk_spinner_elm_layout_sizing_eval(Eo *obj, Jk_Spinner_Data *pd)
{
   Evas_Coord minw = -1, minh = -1;
   ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd);

   elm_coords_finger_size_adjust(1, &minw, 1, &minh);
   edje_object_size_min_restricted_calc
     (wd->resize_obj, &minw, &minh, minw, minh);
   elm_coords_finger_size_adjust(1, &minw, 1, &minh);
   evas_object_size_hint_min_set(obj, minw, minh);
   evas_object_size_hint_max_set(obj, -1, -1);
}

EOLIAN static void
_jk_spinner_efl_ui_spin_min_max_set(Eo *obj, Jk_Spinner_Data *pd, double min, double max)
{

}

EOLIAN static void
_jk_spinner_efl_ui_spin_min_max_get(Eo *obj, Jk_Spinner_Data *pd, double *min, double *max)
{

}

EOLIAN static void
_jk_spinner_efl_ui_spin_step_set(Eo *obj, Jk_Spinner_Data *pd, double step)
{

}

EOLIAN static double
_jk_spinner_efl_ui_spin_step_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_efl_ui_spin_value_set(Eo *obj, Jk_Spinner_Data *pd, double val)
{

}

EOLIAN static double
_jk_spinner_efl_ui_spin_value_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_efl_ui_spin_interval_set(Eo *obj, Jk_Spinner_Data *pd, double interval)
{

}

EOLIAN static double
_jk_spinner_efl_ui_spin_interval_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static char *
_jk_spinner_elm_interface_atspi_accessible_name_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_elm_interface_atspi_value_value_and_text_get(Eo *obj, Jk_Spinner_Data *pd, double *value, const char **text)
{

}

EOLIAN static Eina_Bool
_jk_spinner_elm_interface_atspi_value_value_and_text_set(Eo *obj, Jk_Spinner_Data *pd, double value, const char *text)
{

}

EOLIAN static void
_jk_spinner_elm_interface_atspi_value_range_get(Eo *obj, Jk_Spinner_Data *pd, double *lower_limit, double *upper_limit, const char **description)
{

}

EOLIAN static double
_jk_spinner_elm_interface_atspi_value_increment_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static const Elm_Atspi_Action *
_jk_spinner_elm_interface_atspi_widget_action_elm_actions_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_wrap_set(Eo *obj, Jk_Spinner_Data *pd, Eina_Bool wrap)
{

}

EOLIAN static Eina_Bool
_jk_spinner_wrap_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_round_set(Eo *obj, Jk_Spinner_Data *pd, int rnd)
{

}

EOLIAN static int
_jk_spinner_round_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_editable_set(Eo *obj, Jk_Spinner_Data *pd, Eina_Bool editable)
{

}

EOLIAN static Eina_Bool
_jk_spinner_editable_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_base_set(Eo *obj, Jk_Spinner_Data *pd, double base)
{

}

EOLIAN static double
_jk_spinner_base_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_label_format_set(Eo *obj, Jk_Spinner_Data *pd, const char *fmt)
{

}

EOLIAN static const char *
_jk_spinner_label_format_get(Eo *obj, Jk_Spinner_Data *pd)
{

}

EOLIAN static void
_jk_spinner_special_value_add(Eo *obj, Jk_Spinner_Data *pd, double value, const char *label)
{

}

EOLIAN static void
_jk_spinner_class_constructor(Efl_Class *klass)
{
   evas_smart_legacy_type_register(MY_CLASS_NAME_LEGACY, klass);
}

EAPI Evas_Object *
//Evas_Object *
jk_spinner_add(Evas_Object *parent)
{
   EINA_SAFETY_ON_NULL_RETURN_VAL(parent, NULL);
   Evas_Object *obj = efl_add(MY_CLASS, parent);
   printf("jk_spinner_add ::::::::::::::::::::: :obj : %p \n", obj);
   return obj;
}


#include "jk_spinner.eo.c"
