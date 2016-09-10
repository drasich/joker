#ifndef _JK_ENTRY_EO_H_
#define _JK_ENTRY_EO_H_

#ifndef _JK_ENTRY_EO_CLASS_TYPE
#define _JK_ENTRY_EO_CLASS_TYPE

typedef Eo Jk_Entry;

#endif

#ifndef _JK_ENTRY_EO_TYPES
#define _JK_ENTRY_EO_TYPES


#endif
#define JK_ENTRY_CLASS jk_entry_class_get()

EWAPI const Eo_Class *jk_entry_class_get(void);

EOAPI void jk_obj_entry_min_max_set(Eo *obj, double min, double max);

EOAPI void jk_obj_entry_min_max_get(const Eo *obj, double *min, double *max);

EOAPI void jk_obj_entry_step_set(Eo *obj, double step);

EOAPI double jk_obj_entry_step_get(const Eo *obj);

EOAPI void jk_obj_entry_wrap_set(Eo *obj, Eina_Bool wrap);

EOAPI Eina_Bool jk_obj_entry_wrap_get(const Eo *obj);

EOAPI void jk_obj_entry_interval_set(Eo *obj, double interval);

EOAPI double jk_obj_entry_interval_get(const Eo *obj);

EOAPI void jk_obj_entry_round_set(Eo *obj, int rnd);

EOAPI int jk_obj_entry_round_get(const Eo *obj);

EOAPI void jk_obj_entry_editable_set(Eo *obj, Eina_Bool editable);

EOAPI Eina_Bool jk_obj_entry_editable_get(const Eo *obj);

EOAPI void jk_obj_entry_base_set(Eo *obj, double base);

EOAPI double jk_obj_entry_base_get(const Eo *obj);

EOAPI void jk_obj_entry_value_set(Eo *obj, double val);

EOAPI double jk_obj_entry_value_get(const Eo *obj);

EOAPI double jk_obj_entry_value_saved_get(const Eo *obj);

EOAPI void jk_obj_entry_label_format_set(Eo *obj, const char *fmt);

EOAPI const char *jk_obj_entry_label_format_get(const Eo *obj);

EOAPI void jk_obj_entry_special_value_add(Eo *obj, double value, const char *label);

EOAPI extern const Eo_Event_Description _JK_ENTRY_EVENT_CHANGED;
EOAPI extern const Eo_Event_Description _JK_ENTRY_EVENT_CHANGED_END;
EOAPI extern const Eo_Event_Description _JK_ENTRY_EVENT_DELAY_CHANGED;
EOAPI extern const Eo_Event_Description _JK_ENTRY_EVENT_SPINNER_DRAG_START;
EOAPI extern const Eo_Event_Description _JK_ENTRY_EVENT_SPINNER_DRAG_STOP;
EOAPI extern const Eo_Event_Description _JK_ENTRY_EVENT_LANGUAGE_CHANGED;

/**
 * No description
 */
#define JK_ENTRY_EVENT_CHANGED (&(_JK_ENTRY_EVENT_CHANGED))

/**
 * No description
 */
#define JK_ENTRY_EVENT_CHANGED_END (&(_JK_ENTRY_EVENT_CHANGED_END))

/**
 * No description
 */
#define JK_ENTRY_EVENT_DELAY_CHANGED (&(_JK_ENTRY_EVENT_DELAY_CHANGED))

/**
 * No description
 */
#define JK_ENTRY_EVENT_SPINNER_DRAG_START (&(_JK_ENTRY_EVENT_SPINNER_DRAG_START))

/**
 * No description
 */
#define JK_ENTRY_EVENT_SPINNER_DRAG_STOP (&(_JK_ENTRY_EVENT_SPINNER_DRAG_STOP))

/**
 * No description
 */
#define JK_ENTRY_EVENT_LANGUAGE_CHANGED (&(_JK_ENTRY_EVENT_LANGUAGE_CHANGED))

#endif
