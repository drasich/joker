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

EAPI const Eo_Class *jk_entry_class_get(void) EINA_CONST;

EOAPI void  jk_entry_min_max_set(double min, double max);

EOAPI void  jk_entry_min_max_get(double *min, double *max);

EOAPI void  jk_entry_step_set(double step);

EOAPI double  jk_entry_step_get(void);

EOAPI void  jk_entry_wrap_set(Eina_Bool wrap);

EOAPI Eina_Bool  jk_entry_wrap_get(void);

EOAPI void  jk_entry_interval_set(double interval);

EOAPI double  jk_entry_interval_get(void);

EOAPI void  jk_entry_round_set(int rnd);

EOAPI int  jk_entry_round_get(void);

EOAPI void  jk_entry_editable_set(Eina_Bool editable);

EOAPI Eina_Bool  jk_entry_editable_get(void);

EOAPI void  jk_entry_base_set(double base);

EOAPI double  jk_entry_base_get(void);

EOAPI void  jk_entry_value_set(double val);

EOAPI double  jk_entry_value_get(void);

EOAPI double  jk_entry_value_saved_get(void);

EOAPI void  jk_entry_label_format_set(const char *fmt);

EOAPI const char * jk_entry_label_format_get(void);

EOAPI void  jk_entry_special_value_add(double value, const char *label);

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
