EOAPI const Eo_Event_Description _JK_ENTRY_EVENT_CHANGED =
   EO_EVENT_DESCRIPTION("changed", "");
EOAPI const Eo_Event_Description _JK_ENTRY_EVENT_DELAY_CHANGED =
   EO_EVENT_DESCRIPTION("delay,changed", "");
EOAPI const Eo_Event_Description _JK_ENTRY_EVENT_SPINNER_DRAG_START =
   EO_EVENT_DESCRIPTION("spinner,drag,start", "");
EOAPI const Eo_Event_Description _JK_ENTRY_EVENT_SPINNER_DRAG_STOP =
   EO_EVENT_DESCRIPTION("spinner,drag,stop", "");
EOAPI const Eo_Event_Description _JK_ENTRY_EVENT_LANGUAGE_CHANGED =
   EO_EVENT_DESCRIPTION("language,changed", "");

void _jk_entry_min_max_set(Eo *obj, Jk_Entry_Data *pd, double min, double max);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_min_max_set, EO_FUNC_CALL(min, max), double min, double max);

void _jk_entry_min_max_get(Eo *obj, Jk_Entry_Data *pd, double *min, double *max);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_min_max_get, EO_FUNC_CALL(min, max), double *min, double *max);

void _jk_entry_step_set(Eo *obj, Jk_Entry_Data *pd, double step);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_step_set, EO_FUNC_CALL(step), double step);

double _jk_entry_step_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EO_FUNC_BODY(jk_entry_step_get, double, 0);

void _jk_entry_wrap_set(Eo *obj, Jk_Entry_Data *pd, Eina_Bool wrap);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_wrap_set, EO_FUNC_CALL(wrap), Eina_Bool wrap);

Eina_Bool _jk_entry_wrap_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EO_FUNC_BODY(jk_entry_wrap_get, Eina_Bool, 0);

void _jk_entry_interval_set(Eo *obj, Jk_Entry_Data *pd, double interval);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_interval_set, EO_FUNC_CALL(interval), double interval);

double _jk_entry_interval_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EO_FUNC_BODY(jk_entry_interval_get, double, 0);

void _jk_entry_round_set(Eo *obj, Jk_Entry_Data *pd, int rnd);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_round_set, EO_FUNC_CALL(rnd), int rnd);

int _jk_entry_round_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EO_FUNC_BODY(jk_entry_round_get, int, 0);

void _jk_entry_editable_set(Eo *obj, Jk_Entry_Data *pd, Eina_Bool editable);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_editable_set, EO_FUNC_CALL(editable), Eina_Bool editable);

Eina_Bool _jk_entry_editable_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EO_FUNC_BODY(jk_entry_editable_get, Eina_Bool, 0);

void _jk_entry_base_set(Eo *obj, Jk_Entry_Data *pd, double base);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_base_set, EO_FUNC_CALL(base), double base);

double _jk_entry_base_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EO_FUNC_BODY(jk_entry_base_get, double, 0);

void _jk_entry_value_set(Eo *obj, Jk_Entry_Data *pd, double val);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_value_set, EO_FUNC_CALL(val), double val);

double _jk_entry_value_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EO_FUNC_BODY(jk_entry_value_get, double, 0);

void _jk_entry_label_format_set(Eo *obj, Jk_Entry_Data *pd, const char *fmt);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_label_format_set, EO_FUNC_CALL(fmt), const char *fmt);

const char * _jk_entry_label_format_get(Eo *obj, Jk_Entry_Data *pd);

EOAPI EO_FUNC_BODY(jk_entry_label_format_get, const char *, 0);

void _jk_entry_special_value_add(Eo *obj, Jk_Entry_Data *pd, double value, const char *label);

EOAPI EO_VOID_FUNC_BODYV(jk_entry_special_value_add, EO_FUNC_CALL(value, label), double value, const char *label);

Eo_Base * _jk_entry_eo_base_constructor(Eo *obj, Jk_Entry_Data *pd);


void _jk_entry_evas_object_smart_add(Eo *obj, Jk_Entry_Data *pd);


void _jk_entry_evas_object_smart_del(Eo *obj, Jk_Entry_Data *pd);


void _jk_entry_evas_object_smart_move(Eo *obj, Jk_Entry_Data *pd, Evas_Coord x, Evas_Coord y);


void _jk_entry_evas_object_smart_resize(Eo *obj, Jk_Entry_Data *pd, Evas_Coord w, Evas_Coord h);


Eina_Bool _jk_entry_elm_widget_focus_next_manager_is(Eo *obj, Jk_Entry_Data *pd);


Eina_Bool _jk_entry_elm_widget_focus_direction_manager_is(Eo *obj, Jk_Entry_Data *pd);


Eina_Bool _jk_entry_elm_widget_focus_next(Eo *obj, Jk_Entry_Data *pd, Elm_Focus_Direction dir, Evas_Object **next);


Eina_Bool _jk_entry_elm_widget_focus_direction(Eo *obj, Jk_Entry_Data *pd, const Evas_Object *base, double degree, Evas_Object **direction, double *weight);


Eina_Bool _jk_entry_elm_widget_on_focus(Eo *obj, Jk_Entry_Data *pd);


Eina_Bool _jk_entry_elm_widget_event(Eo *obj, Jk_Entry_Data *pd, Evas_Object *source, Evas_Callback_Type type, void *event_info);


void _jk_entry_elm_layout_sizing_eval(Eo *obj, Jk_Entry_Data *pd);


static Eo_Op_Description _jk_entry_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(eo_constructor, _jk_entry_eo_base_constructor),
     EO_OP_FUNC_OVERRIDE(evas_obj_smart_add, _jk_entry_evas_object_smart_add),
     EO_OP_FUNC_OVERRIDE(evas_obj_smart_del, _jk_entry_evas_object_smart_del),
     EO_OP_FUNC_OVERRIDE(evas_obj_smart_move, _jk_entry_evas_object_smart_move),
     EO_OP_FUNC_OVERRIDE(evas_obj_smart_resize, _jk_entry_evas_object_smart_resize),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_focus_next_manager_is, _jk_entry_elm_widget_focus_next_manager_is),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_focus_direction_manager_is, _jk_entry_elm_widget_focus_direction_manager_is),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_focus_next, _jk_entry_elm_widget_focus_next),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_focus_direction, _jk_entry_elm_widget_focus_direction),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_on_focus, _jk_entry_elm_widget_on_focus),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_event, _jk_entry_elm_widget_event),
     EO_OP_FUNC_OVERRIDE(elm_obj_layout_sizing_eval, _jk_entry_elm_layout_sizing_eval),
     EO_OP_FUNC(jk_entry_min_max_set, _jk_entry_min_max_set, ""),
     EO_OP_FUNC(jk_entry_min_max_get, _jk_entry_min_max_get, ""),
     EO_OP_FUNC(jk_entry_step_set, _jk_entry_step_set, ""),
     EO_OP_FUNC(jk_entry_step_get, _jk_entry_step_get, ""),
     EO_OP_FUNC(jk_entry_wrap_set, _jk_entry_wrap_set, ""),
     EO_OP_FUNC(jk_entry_wrap_get, _jk_entry_wrap_get, ""),
     EO_OP_FUNC(jk_entry_interval_set, _jk_entry_interval_set, ""),
     EO_OP_FUNC(jk_entry_interval_get, _jk_entry_interval_get, ""),
     EO_OP_FUNC(jk_entry_round_set, _jk_entry_round_set, ""),
     EO_OP_FUNC(jk_entry_round_get, _jk_entry_round_get, ""),
     EO_OP_FUNC(jk_entry_editable_set, _jk_entry_editable_set, ""),
     EO_OP_FUNC(jk_entry_editable_get, _jk_entry_editable_get, ""),
     EO_OP_FUNC(jk_entry_base_set, _jk_entry_base_set, ""),
     EO_OP_FUNC(jk_entry_base_get, _jk_entry_base_get, ""),
     EO_OP_FUNC(jk_entry_value_set, _jk_entry_value_set, ""),
     EO_OP_FUNC(jk_entry_value_get, _jk_entry_value_get, ""),
     EO_OP_FUNC(jk_entry_label_format_set, _jk_entry_label_format_set, ""),
     EO_OP_FUNC(jk_entry_label_format_get, _jk_entry_label_format_get, ""),
     EO_OP_FUNC(jk_entry_special_value_add, _jk_entry_special_value_add, ""),
     EO_OP_SENTINEL
};

static const Eo_Event_Description *_jk_entry_event_desc[] = {
     JK_ENTRY_EVENT_CHANGED,
     JK_ENTRY_EVENT_DELAY_CHANGED,
     JK_ENTRY_EVENT_SPINNER_DRAG_START,
     JK_ENTRY_EVENT_SPINNER_DRAG_STOP,
     JK_ENTRY_EVENT_LANGUAGE_CHANGED,
     NULL
};

static const Eo_Class_Description _jk_entry_class_desc = {
     EO_VERSION,
     "Jk_Entry",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_jk_entry_op_desc),
     _jk_entry_event_desc,
     sizeof(Jk_Entry_Data),
     _jk_entry_class_constructor,
     NULL
};

EO_DEFINE_CLASS(jk_entry_class_get, &_jk_entry_class_desc, ELM_LAYOUT_CLASS, NULL);