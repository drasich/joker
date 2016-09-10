EOAPI const Eo_Event_Description _JK_SPINNER_EVENT_CHANGED =
   EO_EVENT_DESCRIPTION("changed");
EOAPI const Eo_Event_Description _JK_SPINNER_EVENT_DELAY_CHANGED =
   EO_EVENT_DESCRIPTION("delay,changed");
EOAPI const Eo_Event_Description _JK_SPINNER_EVENT_SPINNER_DRAG_START =
   EO_EVENT_DESCRIPTION("spinner,drag,start");
EOAPI const Eo_Event_Description _JK_SPINNER_EVENT_SPINNER_DRAG_STOP =
   EO_EVENT_DESCRIPTION("spinner,drag,stop");

void _jk_spinner_wrap_set(Eo *obj, Jk_Spinner_Data *pd, Eina_Bool wrap);

EOAPI EO_VOID_FUNC_BODYV(jk_obj_spinner_wrap_set, EO_FUNC_CALL(wrap), Eina_Bool wrap);

Eina_Bool _jk_spinner_wrap_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EO_FUNC_BODY_CONST(jk_obj_spinner_wrap_get, Eina_Bool, 0);

void _jk_spinner_round_set(Eo *obj, Jk_Spinner_Data *pd, int rnd);

EOAPI EO_VOID_FUNC_BODYV(jk_obj_spinner_round_set, EO_FUNC_CALL(rnd), int rnd);

int _jk_spinner_round_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EO_FUNC_BODY_CONST(jk_obj_spinner_round_get, int, 0);

void _jk_spinner_editable_set(Eo *obj, Jk_Spinner_Data *pd, Eina_Bool editable);

EOAPI EO_VOID_FUNC_BODYV(jk_obj_spinner_editable_set, EO_FUNC_CALL(editable), Eina_Bool editable);

Eina_Bool _jk_spinner_editable_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EO_FUNC_BODY_CONST(jk_obj_spinner_editable_get, Eina_Bool, 0);

void _jk_spinner_base_set(Eo *obj, Jk_Spinner_Data *pd, double base);

EOAPI EO_VOID_FUNC_BODYV(jk_obj_spinner_base_set, EO_FUNC_CALL(base), double base);

double _jk_spinner_base_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EO_FUNC_BODY_CONST(jk_obj_spinner_base_get, double, 0);

void _jk_spinner_label_format_set(Eo *obj, Jk_Spinner_Data *pd, const char *fmt);

EOAPI EO_VOID_FUNC_BODYV(jk_obj_spinner_label_format_set, EO_FUNC_CALL(fmt), const char *fmt);

const char * _jk_spinner_label_format_get(Eo *obj, Jk_Spinner_Data *pd);

EOAPI EO_FUNC_BODY_CONST(jk_obj_spinner_label_format_get, const char *, 0);

void _jk_spinner_special_value_add(Eo *obj, Jk_Spinner_Data *pd, double value, const char *label);

EOAPI EO_VOID_FUNC_BODYV(jk_obj_spinner_special_value_add, EO_FUNC_CALL(value, label), double value, const char *label);

Eo_Base * _jk_spinner_eo_base_constructor(Eo *obj, Jk_Spinner_Data *pd);


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


static const Eo_Op_Description _jk_spinner_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(eo_constructor, _jk_spinner_eo_base_constructor),
     EO_OP_FUNC_OVERRIDE(efl_canvas_group_add, _jk_spinner_efl_canvas_group_group_add),
     EO_OP_FUNC_OVERRIDE(efl_canvas_group_del, _jk_spinner_efl_canvas_group_group_del),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_theme_apply, _jk_spinner_elm_widget_theme_apply),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_focus_next_manager_is, _jk_spinner_elm_widget_focus_next_manager_is),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_focus_direction_manager_is, _jk_spinner_elm_widget_focus_direction_manager_is),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_access, _jk_spinner_elm_widget_access),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_focus_next, _jk_spinner_elm_widget_focus_next),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_focus_direction, _jk_spinner_elm_widget_focus_direction),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_on_focus, _jk_spinner_elm_widget_on_focus),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_event, _jk_spinner_elm_widget_event),
     EO_OP_FUNC_OVERRIDE(elm_obj_layout_sizing_eval, _jk_spinner_elm_layout_sizing_eval),
     EO_OP_FUNC_OVERRIDE(efl_ui_spin_min_max_set, _jk_spinner_efl_ui_spin_min_max_set),
     EO_OP_FUNC_OVERRIDE(efl_ui_spin_min_max_get, _jk_spinner_efl_ui_spin_min_max_get),
     EO_OP_FUNC_OVERRIDE(efl_ui_spin_step_set, _jk_spinner_efl_ui_spin_step_set),
     EO_OP_FUNC_OVERRIDE(efl_ui_spin_step_get, _jk_spinner_efl_ui_spin_step_get),
     EO_OP_FUNC_OVERRIDE(efl_ui_spin_value_set, _jk_spinner_efl_ui_spin_value_set),
     EO_OP_FUNC_OVERRIDE(efl_ui_spin_value_get, _jk_spinner_efl_ui_spin_value_get),
     EO_OP_FUNC_OVERRIDE(efl_ui_spin_interval_set, _jk_spinner_efl_ui_spin_interval_set),
     EO_OP_FUNC_OVERRIDE(efl_ui_spin_interval_get, _jk_spinner_efl_ui_spin_interval_get),
     EO_OP_FUNC_OVERRIDE(elm_interface_atspi_accessible_name_get, _jk_spinner_elm_interface_atspi_accessible_name_get),
     EO_OP_FUNC_OVERRIDE(elm_interface_atspi_value_and_text_get, _jk_spinner_elm_interface_atspi_value_value_and_text_get),
     EO_OP_FUNC_OVERRIDE(elm_interface_atspi_value_and_text_set, _jk_spinner_elm_interface_atspi_value_value_and_text_set),
     EO_OP_FUNC_OVERRIDE(elm_interface_atspi_value_range_get, _jk_spinner_elm_interface_atspi_value_range_get),
     EO_OP_FUNC_OVERRIDE(elm_interface_atspi_value_increment_get, _jk_spinner_elm_interface_atspi_value_increment_get),
     EO_OP_FUNC_OVERRIDE(elm_interface_atspi_widget_action_elm_actions_get, _jk_spinner_elm_interface_atspi_widget_action_elm_actions_get),
     EO_OP_FUNC(jk_obj_spinner_wrap_set, _jk_spinner_wrap_set),
     EO_OP_FUNC(jk_obj_spinner_wrap_get, _jk_spinner_wrap_get),
     EO_OP_FUNC(jk_obj_spinner_round_set, _jk_spinner_round_set),
     EO_OP_FUNC(jk_obj_spinner_round_get, _jk_spinner_round_get),
     EO_OP_FUNC(jk_obj_spinner_editable_set, _jk_spinner_editable_set),
     EO_OP_FUNC(jk_obj_spinner_editable_get, _jk_spinner_editable_get),
     EO_OP_FUNC(jk_obj_spinner_base_set, _jk_spinner_base_set),
     EO_OP_FUNC(jk_obj_spinner_base_get, _jk_spinner_base_get),
     EO_OP_FUNC(jk_obj_spinner_label_format_set, _jk_spinner_label_format_set),
     EO_OP_FUNC(jk_obj_spinner_label_format_get, _jk_spinner_label_format_get),
     EO_OP_FUNC(jk_obj_spinner_special_value_add, _jk_spinner_special_value_add),
};

static const Eo_Event_Description *_jk_spinner_event_desc[] = {
     JK_SPINNER_EVENT_CHANGED,
     JK_SPINNER_EVENT_DELAY_CHANGED,
     JK_SPINNER_EVENT_SPINNER_DRAG_START,
     JK_SPINNER_EVENT_SPINNER_DRAG_STOP,
     NULL
};

static const Eo_Class_Description _jk_spinner_class_desc = {
     EO_VERSION,
     "Jk_Spinner",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_jk_spinner_op_desc),
     _jk_spinner_event_desc,
     sizeof(Jk_Spinner_Data),
     _jk_spinner_class_constructor,
     NULL
};

//EO_DEFINE_CLASS(jk_spinner_class_get, &_jk_spinner_class_desc, ELM_LAYOUT_CLASS, EFL_UI_SPIN_INTERFACE, ELM_INTERFACE_ATSPI_VALUE_INTERFACE, ELM_INTERFACE_ATSPI_WIDGET_ACTION_MIXIN, NULL);


const Eo_Class *
       jk_spinner_class_get(void)
{
  const Eo_Class *_tmp_parent_class;
  static volatile unsigned char lk_init = 0;
  static Eina_Spinlock _my_lock;
  static const Eo_Class * volatile _my_class = NULL;
  static unsigned int _my_init_generation = 1;
  if (EINA_UNLIKELY(_eo_init_generation != _my_init_generation))
   {
    _my_class = NULL; /* It's freed in eo_shutdown(). */
    lk_init = 0;
   }
  if (EINA_LIKELY(!!_my_class)) return _my_class;

  eina_spinlock_take(&_eo_class_creation_lock);
  if (!lk_init)
  eina_spinlock_new(&_my_lock);
  if (lk_init < 2) eina_spinlock_take(&_my_lock);
  if (!lk_init)
  lk_init = 1;
  else
   {
    if (lk_init < 2) eina_spinlock_release(&_my_lock);
    eina_spinlock_release(&_eo_class_creation_lock);
    return _my_class;
   }
  eina_spinlock_release(&_eo_class_creation_lock);
  _tmp_parent_class = ELM_LAYOUT_CLASS;
  _my_class = eo_class_new(&_jk_spinner_class_desc, _tmp_parent_class, EFL_UI_SPIN_INTERFACE, ELM_INTERFACE_ATSPI_VALUE_INTERFACE, ELM_INTERFACE_ATSPI_WIDGET_ACTION_MIXIN, NULL);
  _my_init_generation = _eo_init_generation;
  eina_spinlock_release(&_my_lock);

  eina_spinlock_take(&_eo_class_creation_lock);
  eina_spinlock_free(&_my_lock);
  lk_init = 2;
  eina_spinlock_release(&_eo_class_creation_lock);
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
