#include "Eo.h"
EOAPI const Efl_Event_Description _JK_SPINNER_EVENT_CHANGED =
   EFL_EVENT_DESCRIPTION("changed");
EOAPI const Efl_Event_Description _JK_SPINNER_EVENT_DELAY_CHANGED =
   EFL_EVENT_DESCRIPTION("delay,changed");
EOAPI const Efl_Event_Description _JK_SPINNER_EVENT_SPINNER_DRAG_START =
   EFL_EVENT_DESCRIPTION("spinner,drag,start");
EOAPI const Efl_Event_Description _JK_SPINNER_EVENT_SPINNER_DRAG_STOP =
   EFL_EVENT_DESCRIPTION("spinner,drag,stop");

void _jk_spinner_wrap_set(Eo *obj, Jk_Spinner_Data *pd, Eina_Bool wrap);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_spinner_wrap_set, EFL_FUNC_CALL(wrap), Eina_Bool wrap);

Eina_Bool _jk_spinner_wrap_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_spinner_wrap_get, Eina_Bool, 0);

void _jk_spinner_round_set(Eo *obj, Jk_Spinner_Data *pd, int rnd);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_spinner_round_set, EFL_FUNC_CALL(rnd), int rnd);

int _jk_spinner_round_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_spinner_round_get, int, 0);

void _jk_spinner_editable_set(Eo *obj, Jk_Spinner_Data *pd, Eina_Bool editable);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_spinner_editable_set, EFL_FUNC_CALL(editable), Eina_Bool editable);

Eina_Bool _jk_spinner_editable_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_spinner_editable_get, Eina_Bool, 0);

void _jk_spinner_base_set(Eo *obj, Jk_Spinner_Data *pd, double base);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_spinner_base_set, EFL_FUNC_CALL(base), double base);

double _jk_spinner_base_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_spinner_base_get, double, 0);

void _jk_spinner_label_format_set(Eo *obj, Jk_Spinner_Data *pd, const char *fmt);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_spinner_label_format_set, EFL_FUNC_CALL(fmt), const char *fmt);

const char * _jk_spinner_label_format_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_spinner_label_format_get, const char *, 0);

void _jk_spinner_special_value_add(Eo *obj, Jk_Spinner_Data *pd, double value, const char *label);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_spinner_special_value_add, EFL_FUNC_CALL(value, label), double value, const char *label);

Efl_Object * _jk_spinner_efl_object_constructor(Eo *obj, Jk_Spinner_Data *pd);


void _jk_spinner_efl_canvas_group_group_add(Eo *obj, Jk_Spinner_Data *pd);


void _jk_spinner_efl_canvas_group_group_del(Eo *obj, Jk_Spinner_Data *pd);


Elm_Theme_Apply _jk_spinner_elm_widget_theme_apply(Eo *obj, Jk_Spinner_Data *pd);


Eina_Bool _jk_spinner_elm_widget_focus_next_manager_is(Eo *obj, Jk_Spinner_Data *pd);


Eina_Bool _jk_spinner_elm_widget_focus_direction_manager_is(Eo *obj, Jk_Spinner_Data *pd);


void _jk_spinner_elm_widget_access(Eo *obj, Jk_Spinner_Data *pd, Eina_Bool acs);


Eina_Bool _jk_spinner_elm_widget_focus_next(Eo *obj, Jk_Spinner_Data *pd, Elm_Focus_Direction dir, Efl_Canvas_Object **next, Elm_Widget_Item **next_item);


Eina_Bool _jk_spinner_elm_widget_focus_direction(Eo *obj, Jk_Spinner_Data *pd, const Efl_Canvas_Object *base, double degree, Efl_Canvas_Object **direction, Elm_Widget_Item **direction_item, double *weight);


Eina_Bool _jk_spinner_elm_widget_on_focus(Eo *obj, Jk_Spinner_Data *pd, Elm_Widget_Item *item);


Eina_Bool _jk_spinner_elm_widget_event(Eo *obj, Jk_Spinner_Data *pd, Efl_Canvas_Object *source, Evas_Callback_Type type, void *event_info);


void _jk_spinner_elm_layout_sizing_eval(Eo *obj, Jk_Spinner_Data *pd);


void _jk_spinner_efl_ui_spin_min_max_set(Eo *obj, Jk_Spinner_Data *pd, double min, double max);


void _jk_spinner_efl_ui_spin_min_max_get(Eo *obj, Jk_Spinner_Data *pd, double *min, double *max);


void _jk_spinner_efl_ui_spin_step_set(Eo *obj, Jk_Spinner_Data *pd, double step);


double _jk_spinner_efl_ui_spin_step_get(Eo *obj, Jk_Spinner_Data *pd);


void _jk_spinner_efl_ui_spin_value_set(Eo *obj, Jk_Spinner_Data *pd, double val);


double _jk_spinner_efl_ui_spin_value_get(Eo *obj, Jk_Spinner_Data *pd);


void _jk_spinner_efl_ui_spin_interval_set(Eo *obj, Jk_Spinner_Data *pd, double interval);


double _jk_spinner_efl_ui_spin_interval_get(Eo *obj, Jk_Spinner_Data *pd);


char * _jk_spinner_elm_interface_atspi_accessible_name_get(Eo *obj, Jk_Spinner_Data *pd);


void _jk_spinner_elm_interface_atspi_value_value_and_text_get(Eo *obj, Jk_Spinner_Data *pd, double *value, const char **text);


Eina_Bool _jk_spinner_elm_interface_atspi_value_value_and_text_set(Eo *obj, Jk_Spinner_Data *pd, double value, const char *text);


void _jk_spinner_elm_interface_atspi_value_range_get(Eo *obj, Jk_Spinner_Data *pd, double *lower_limit, double *upper_limit, const char **description);


double _jk_spinner_elm_interface_atspi_value_increment_get(Eo *obj, Jk_Spinner_Data *pd);


const Elm_Atspi_Action * _jk_spinner_elm_interface_atspi_widget_action_elm_actions_get(Eo *obj, Jk_Spinner_Data *pd);


static Eina_Bool
_jk_spinner_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _jk_spinner_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_canvas_group_add, _jk_spinner_efl_canvas_group_group_add),
      EFL_OBJECT_OP_FUNC(efl_canvas_group_del, _jk_spinner_efl_canvas_group_group_del),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_theme_apply, _jk_spinner_elm_widget_theme_apply),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_focus_next_manager_is, _jk_spinner_elm_widget_focus_next_manager_is),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_focus_direction_manager_is, _jk_spinner_elm_widget_focus_direction_manager_is),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_access, _jk_spinner_elm_widget_access),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_focus_next, _jk_spinner_elm_widget_focus_next),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_focus_direction, _jk_spinner_elm_widget_focus_direction),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_on_focus, _jk_spinner_elm_widget_on_focus),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_event, _jk_spinner_elm_widget_event),
      EFL_OBJECT_OP_FUNC(elm_obj_layout_sizing_eval, _jk_spinner_elm_layout_sizing_eval),
      EFL_OBJECT_OP_FUNC(efl_ui_spin_min_max_set, _jk_spinner_efl_ui_spin_min_max_set),
      EFL_OBJECT_OP_FUNC(efl_ui_spin_min_max_get, _jk_spinner_efl_ui_spin_min_max_get),
      EFL_OBJECT_OP_FUNC(efl_ui_spin_step_set, _jk_spinner_efl_ui_spin_step_set),
      EFL_OBJECT_OP_FUNC(efl_ui_spin_step_get, _jk_spinner_efl_ui_spin_step_get),
      EFL_OBJECT_OP_FUNC(efl_ui_spin_value_set, _jk_spinner_efl_ui_spin_value_set),
      EFL_OBJECT_OP_FUNC(efl_ui_spin_value_get, _jk_spinner_efl_ui_spin_value_get),
      EFL_OBJECT_OP_FUNC(efl_ui_spin_interval_set, _jk_spinner_efl_ui_spin_interval_set),
      EFL_OBJECT_OP_FUNC(efl_ui_spin_interval_get, _jk_spinner_efl_ui_spin_interval_get),
      EFL_OBJECT_OP_FUNC(elm_interface_atspi_accessible_name_get, _jk_spinner_elm_interface_atspi_accessible_name_get),
      EFL_OBJECT_OP_FUNC(elm_interface_atspi_value_and_text_get, _jk_spinner_elm_interface_atspi_value_value_and_text_get),
      EFL_OBJECT_OP_FUNC(elm_interface_atspi_value_and_text_set, _jk_spinner_elm_interface_atspi_value_value_and_text_set),
      EFL_OBJECT_OP_FUNC(elm_interface_atspi_value_range_get, _jk_spinner_elm_interface_atspi_value_range_get),
      EFL_OBJECT_OP_FUNC(elm_interface_atspi_value_increment_get, _jk_spinner_elm_interface_atspi_value_increment_get),
      EFL_OBJECT_OP_FUNC(elm_interface_atspi_widget_action_elm_actions_get, _jk_spinner_elm_interface_atspi_widget_action_elm_actions_get),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_wrap_set, _jk_spinner_wrap_set),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_wrap_get, _jk_spinner_wrap_get),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_round_set, _jk_spinner_round_set),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_round_get, _jk_spinner_round_get),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_editable_set, _jk_spinner_editable_set),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_editable_get, _jk_spinner_editable_get),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_base_set, _jk_spinner_base_set),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_base_get, _jk_spinner_base_get),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_label_format_set, _jk_spinner_label_format_set),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_label_format_get, _jk_spinner_label_format_get),
      EFL_OBJECT_OP_FUNC(jk_obj_spinner_special_value_add, _jk_spinner_special_value_add)
   );

   return efl_class_functions_set(klass, &ops, NULL);
}

static const Efl_Class_Description _jk_spinner_class_desc = {
     EO_VERSION,
     "Jk_Spinner",
     EFL_CLASS_TYPE_REGULAR,
     sizeof(Jk_Spinner_Data),
     _jk_spinner_class_initializer,
     _jk_spinner_class_constructor,
     NULL
};

//EFL_DEFINE_CLASS(jk_spinner_class_get, &_jk_spinner_class_desc, ELM_LAYOUT_CLASS, EFL_UI_SPIN_INTERFACE, ELM_INTERFACE_ATSPI_VALUE_INTERFACE, ELM_INTERFACE_ATSPI_WIDGET_ACTION_MIXIN, NULL);

const Efl_Class * 
jk_spinner_class_get(void) 
{ 
   const Efl_Class *_tmp_parent_class; 
   static const Efl_Class * volatile _my_class = NULL; 
   static unsigned int _my_init_generation = 1; 
   if (EINA_UNLIKELY(_efl_object_init_generation != _my_init_generation)) 
     { 
        _my_class = NULL; /* It's freed in efl_object_shutdown(). */ 
     } 
   if (EINA_LIKELY(!!_my_class)) return _my_class; 
   
   eina_lock_take(&_efl_class_creation_lock); 
   if (!!_my_class) 
     { 
        eina_lock_release(&_efl_class_creation_lock); 
        return _my_class; 
     } 
   _tmp_parent_class = ELM_LAYOUT_CLASS;; 
   _my_class = efl_class_new(&_jk_spinner_class_desc, _tmp_parent_class, EFL_UI_SPIN_INTERFACE, ELM_INTERFACE_ATSPI_VALUE_INTERFACE, ELM_INTERFACE_ATSPI_WIDGET_ACTION_MIXIN, NULL);
   _my_init_generation = _efl_object_init_generation; 
   eina_lock_release(&_efl_class_creation_lock); 
   
   return _my_class; 
}



EAPI void
jk_spinner_wrap_set(Jk_Spinner *obj, Eina_Bool wrap)
{
   jk_obj_spinner_wrap_set((Jk_Spinner *)obj, wrap);
}

EAPI Eina_Bool
jk_spinner_wrap_get(const Jk_Spinner *obj)
{
   return jk_obj_spinner_wrap_get((Jk_Spinner *)obj);
}

EAPI void
jk_spinner_round_set(Jk_Spinner *obj, int rnd)
{
   jk_obj_spinner_round_set((Jk_Spinner *)obj, rnd);
}

EAPI int
jk_spinner_round_get(const Jk_Spinner *obj)
{
   return jk_obj_spinner_round_get((Jk_Spinner *)obj);
}

EAPI void
jk_spinner_editable_set(Jk_Spinner *obj, Eina_Bool editable)
{
   jk_obj_spinner_editable_set((Jk_Spinner *)obj, editable);
}

EAPI Eina_Bool
jk_spinner_editable_get(const Jk_Spinner *obj)
{
   return jk_obj_spinner_editable_get((Jk_Spinner *)obj);
}

EAPI void
jk_spinner_base_set(Jk_Spinner *obj, double base)
{
   jk_obj_spinner_base_set((Jk_Spinner *)obj, base);
}

EAPI double
jk_spinner_base_get(const Jk_Spinner *obj)
{
   return jk_obj_spinner_base_get((Jk_Spinner *)obj);
}

EAPI void
jk_spinner_label_format_set(Jk_Spinner *obj, const char *fmt)
{
   jk_obj_spinner_label_format_set((Jk_Spinner *)obj, fmt);
}

EAPI const char *
jk_spinner_label_format_get(const Jk_Spinner *obj)
{
   return jk_obj_spinner_label_format_get((Jk_Spinner *)obj);
}

EAPI void
jk_spinner_special_value_add(Jk_Spinner *obj, double value, const char *label)
{
   jk_obj_spinner_special_value_add((Jk_Spinner *)obj, value, label);
}
