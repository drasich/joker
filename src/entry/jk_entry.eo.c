EWAPI const Efl_Event_Description _JK_ENTRY_EVENT_CHANGED =
   EFL_EVENT_DESCRIPTION("changed");
EWAPI const Efl_Event_Description _JK_ENTRY_EVENT_CHANGED_END =
   EFL_EVENT_DESCRIPTION("changed,end");
EWAPI const Efl_Event_Description _JK_ENTRY_EVENT_DELAY_CHANGED =
   EFL_EVENT_DESCRIPTION("delay,changed");
EWAPI const Efl_Event_Description _JK_ENTRY_EVENT_SPINNER_DRAG_START =
   EFL_EVENT_DESCRIPTION("spinner,drag,start");
EWAPI const Efl_Event_Description _JK_ENTRY_EVENT_SPINNER_DRAG_STOP =
   EFL_EVENT_DESCRIPTION("spinner,drag,stop");
EWAPI const Efl_Event_Description _JK_ENTRY_EVENT_LANGUAGE_CHANGED =
   EFL_EVENT_DESCRIPTION("language,changed");

Efl_Object *_jk_entry_efl_object_constructor(Eo *obj, Jk_Entry_Data *pd);


void _jk_entry_efl_canvas_group_group_add(Eo *obj, Jk_Entry_Data *pd);


void _jk_entry_efl_canvas_group_group_del(Eo *obj, Jk_Entry_Data *pd);


Eina_Bool _jk_entry_elm_widget_focus_next_manager_is(Eo *obj, Jk_Entry_Data *pd);


Eina_Bool _jk_entry_elm_widget_focus_direction_manager_is(Eo *obj, Jk_Entry_Data *pd);


Eina_Bool _jk_entry_elm_widget_focus_next(Eo *obj, Jk_Entry_Data *pd, Elm_Focus_Direction dir, Efl_Canvas_Object **next, Elm_Widget_Item **next_item);


Eina_Bool _jk_entry_elm_widget_focus_direction(Eo *obj, Jk_Entry_Data *pd, const Efl_Canvas_Object *base, double degree, Efl_Canvas_Object **direction, Elm_Widget_Item **direction_item, double *weight);


Eina_Bool _jk_entry_elm_widget_on_focus(Eo *obj, Jk_Entry_Data *pd, Elm_Widget_Item *item);


Eina_Bool _jk_entry_elm_widget_event(Eo *obj, Jk_Entry_Data *pd, Efl_Canvas_Object *source, Evas_Callback_Type type, void *event_info);


void _jk_entry_elm_layout_sizing_eval(Eo *obj, Jk_Entry_Data *pd);


void _jk_entry_min_max_set(Eo *obj, Jk_Entry_Data *pd, double min, double max);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_min_max_set, EFL_FUNC_CALL(min, max), double min, double max);

void _jk_entry_min_max_get(Eo *obj, Jk_Entry_Data *pd, double *min, double *max);

EOAPI EFL_VOID_FUNC_BODYV_CONST(jk_obj_entry_min_max_get, EFL_FUNC_CALL(min, max), double *min, double *max);

void _jk_entry_step_set(Eo *obj, Jk_Entry_Data *pd, double step);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_step_set, EFL_FUNC_CALL(step), double step);

double _jk_entry_step_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_step_get, double, 0);

void _jk_entry_wrap_set(Eo *obj, Jk_Entry_Data *pd, Eina_Bool wrap);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_wrap_set, EFL_FUNC_CALL(wrap), Eina_Bool wrap);

Eina_Bool _jk_entry_wrap_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_wrap_get, Eina_Bool, 0);

void _jk_entry_interval_set(Eo *obj, Jk_Entry_Data *pd, double interval);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_interval_set, EFL_FUNC_CALL(interval), double interval);

double _jk_entry_interval_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_interval_get, double, 0);

void _jk_entry_round_set(Eo *obj, Jk_Entry_Data *pd, int rnd);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_round_set, EFL_FUNC_CALL(rnd), int rnd);

int _jk_entry_round_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_round_get, int, 0);

void _jk_entry_editable_set(Eo *obj, Jk_Entry_Data *pd, Eina_Bool editable);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_editable_set, EFL_FUNC_CALL(editable), Eina_Bool editable);

Eina_Bool _jk_entry_editable_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_editable_get, Eina_Bool, 0);

void _jk_entry_base_set(Eo *obj, Jk_Entry_Data *pd, double base);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_base_set, EFL_FUNC_CALL(base), double base);

double _jk_entry_base_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_base_get, double, 0);

void _jk_entry_value_set(Eo *obj, Jk_Entry_Data *pd, double val);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_value_set, EFL_FUNC_CALL(val), double val);

double _jk_entry_value_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_value_get, double, 0);

double _jk_entry_value_saved_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_value_saved_get, double, 0);

void _jk_entry_label_format_set(Eo *obj, Jk_Entry_Data *pd, const char *fmt);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_label_format_set, EFL_FUNC_CALL(fmt), const char *fmt);

const char *_jk_entry_label_format_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(jk_obj_entry_label_format_get, const char *, 0);

void _jk_entry_special_value_add(Eo *obj, Jk_Entry_Data *pd, double value, const char *label);

EOAPI EFL_VOID_FUNC_BODYV(jk_obj_entry_special_value_add, EFL_FUNC_CALL(value, label), double value, const char *label);

static Eina_Bool
_jk_entry_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _jk_entry_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_canvas_group_add, _jk_entry_efl_canvas_group_group_add),
      EFL_OBJECT_OP_FUNC(efl_canvas_group_del, _jk_entry_efl_canvas_group_group_del),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_focus_next_manager_is, _jk_entry_elm_widget_focus_next_manager_is),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_focus_direction_manager_is, _jk_entry_elm_widget_focus_direction_manager_is),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_focus_next, _jk_entry_elm_widget_focus_next),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_focus_direction, _jk_entry_elm_widget_focus_direction),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_on_focus, _jk_entry_elm_widget_on_focus),
      EFL_OBJECT_OP_FUNC(elm_obj_widget_event, _jk_entry_elm_widget_event),
      EFL_OBJECT_OP_FUNC(elm_obj_layout_sizing_eval, _jk_entry_elm_layout_sizing_eval),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_min_max_set, _jk_entry_min_max_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_min_max_get, _jk_entry_min_max_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_step_set, _jk_entry_step_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_step_get, _jk_entry_step_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_wrap_set, _jk_entry_wrap_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_wrap_get, _jk_entry_wrap_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_interval_set, _jk_entry_interval_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_interval_get, _jk_entry_interval_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_round_set, _jk_entry_round_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_round_get, _jk_entry_round_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_editable_set, _jk_entry_editable_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_editable_get, _jk_entry_editable_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_base_set, _jk_entry_base_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_base_get, _jk_entry_base_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_value_set, _jk_entry_value_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_value_get, _jk_entry_value_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_value_saved_get, _jk_entry_value_saved_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_label_format_set, _jk_entry_label_format_set),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_label_format_get, _jk_entry_label_format_get),
      EFL_OBJECT_OP_FUNC(jk_obj_entry_special_value_add, _jk_entry_special_value_add)
   );
   return efl_class_functions_set(klass, &ops, NULL);
}

static const Efl_Class_Description _jk_entry_class_desc = {
   EO_VERSION,
   "Jk_Entry",
   EFL_CLASS_TYPE_REGULAR,
   sizeof(Jk_Entry_Data),
   _jk_entry_class_initializer,
   _jk_entry_class_constructor,
   NULL
};

EFL_DEFINE_CLASS(jk_entry_class_get, &_jk_entry_class_desc, ELM_LAYOUT_CLASS, ELM_WIDGET_CLASS, NULL);

EAPI void
jk_entry_min_max_set(Jk_Entry *obj, double min, double max)
{
   jk_obj_entry_min_max_set(obj, min, max);
}

EAPI void
jk_entry_min_max_get(const Jk_Entry *obj, double *min, double *max)
{
   jk_obj_entry_min_max_get(obj, min, max);
}

EAPI void
jk_entry_step_set(Jk_Entry *obj, double step)
{
   jk_obj_entry_step_set(obj, step);
}

EAPI double
jk_entry_step_get(const Jk_Entry *obj)
{
   return jk_obj_entry_step_get(obj);
}

EAPI void
jk_entry_wrap_set(Jk_Entry *obj, Eina_Bool wrap)
{
   jk_obj_entry_wrap_set(obj, wrap);
}

EAPI Eina_Bool
jk_entry_wrap_get(const Jk_Entry *obj)
{
   return jk_obj_entry_wrap_get(obj);
}

EAPI void
jk_entry_interval_set(Jk_Entry *obj, double interval)
{
   jk_obj_entry_interval_set(obj, interval);
}

EAPI double
jk_entry_interval_get(const Jk_Entry *obj)
{
   return jk_obj_entry_interval_get(obj);
}

EAPI void
jk_entry_round_set(Jk_Entry *obj, int rnd)
{
   jk_obj_entry_round_set(obj, rnd);
}

EAPI int
jk_entry_round_get(const Jk_Entry *obj)
{
   return jk_obj_entry_round_get(obj);
}

EAPI void
jk_entry_editable_set(Jk_Entry *obj, Eina_Bool editable)
{
   jk_obj_entry_editable_set(obj, editable);
}

EAPI Eina_Bool
jk_entry_editable_get(const Jk_Entry *obj)
{
   return jk_obj_entry_editable_get(obj);
}

EAPI void
jk_entry_base_set(Jk_Entry *obj, double base)
{
   jk_obj_entry_base_set(obj, base);
}

EAPI double
jk_entry_base_get(const Jk_Entry *obj)
{
   return jk_obj_entry_base_get(obj);
}

EAPI void
jk_entry_value_set(Jk_Entry *obj, double val)
{
   jk_obj_entry_value_set(obj, val);
}

EAPI double
jk_entry_value_get(const Jk_Entry *obj)
{
   return jk_obj_entry_value_get(obj);
}

EAPI double
jk_entry_value_saved_get(const Jk_Entry *obj)
{
   return jk_obj_entry_value_saved_get(obj);
}

EAPI void
jk_entry_label_format_set(Jk_Entry *obj, const char *fmt)
{
   jk_obj_entry_label_format_set(obj, fmt);
}

EAPI const char *
jk_entry_label_format_get(const Jk_Entry *obj)
{
   return jk_obj_entry_label_format_get(obj);
}

EAPI void
jk_entry_special_value_add(Jk_Entry *obj, double value, const char *label)
{
   jk_obj_entry_special_value_add(obj, value, label);
}
