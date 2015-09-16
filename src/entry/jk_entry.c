//#define EFL_BETA_API_SUPPORT
#include <Elementary.h>
#include <Eo.h>
#include "elm_widget.h"
#include "jk_entry.eo.h"

#define MY_CLASS JK_ENTRY_CLASS

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




typedef struct
{
	Eo* rect;

} Jk_Entry_Data;

EOLIAN static Eo_Base *
_jk_entry_eo_base_constructor(Eo *obj, Jk_Entry_Data *pd EINA_UNUSED)
{
	obj = eo_do_super_ret(obj, JK_ENTRY_CLASS, obj, eo_constructor());

   return obj;
}

EOLIAN static void
_jk_entry_evas_object_smart_add(Eo *obj, Jk_Entry_Data *pd)
{
   ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd);
   JK_ENTRY_DATA_GET(obj, ed);

   eo_do_super(obj, JK_ENTRY_CLASS, evas_obj_smart_add());
   elm_widget_sub_object_parent_add(obj);

  elm_layout_file_set(obj, "edc/entry.edj", "main");


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


 Evas_Object* en = elm_entry_add(obj);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
  //evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_object_text_set(en, "yoshyosh");

  //elm_entry_scrollable_set(en, EINA_TRUE);
  //elm_entry_scrollbar_policy_set(en,
  //      ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
  elm_entry_single_line_set(en, EINA_TRUE);

   //evas_object_smart_member_add(rect, en);
  elm_layout_content_set(obj, "content", en);
   elm_widget_sub_object_add(obj, en);
   evas_object_show(en);


   elm_widget_can_focus_set(obj, EINA_TRUE);
   elm_layout_sizing_eval(obj);

}

EOLIAN static void
_jk_entry_evas_object_smart_del(Eo *obj, Jk_Entry_Data *pd)
{
   eo_do_super(obj, MY_CLASS, evas_obj_smart_del());
}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_focus_next_manager_is(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_focus_direction_manager_is(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_focus_next(Eo *obj, Jk_Entry_Data *pd, Elm_Focus_Direction dir, Evas_Object **next)
{

}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_focus_direction(Eo *obj, Jk_Entry_Data *pd, const Evas_Object *base, double degree, Evas_Object **direction, double *weight)
{

}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_on_focus(Eo *obj, Jk_Entry_Data *pd)
{

}

EOLIAN static Eina_Bool
_jk_entry_elm_widget_event(Eo *obj, Jk_Entry_Data *pd, Evas_Object *source, Evas_Callback_Type type, void *event_info)
{

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

}

EOLIAN static double
_jk_entry_value_get(Eo *obj, Jk_Entry_Data *pd)
{

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

}

EOLIAN static void
_jk_entry_evas_object_smart_move(Eo *obj, Jk_Entry_Data *pd, Evas_Coord x, Evas_Coord y)
{
    eo_do_super(obj, MY_CLASS, evas_obj_smart_move(x, y));

   //evas_object_move(pd->rect, x, y);
}

EOLIAN static void
_jk_entry_evas_object_smart_resize(Eo *obj, Jk_Entry_Data *pd, Evas_Coord w, Evas_Coord h)
{
	  eo_do_super(obj, MY_CLASS, evas_obj_smart_resize(w, h));

   //evas_object_resize(pd->rect, w, h);
}

#include "jk_entry.eo.c"
