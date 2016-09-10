#ifndef _JK_ENTRY_EO_LEGACY_H_
#define _JK_ENTRY_EO_LEGACY_H_

#ifndef _JK_ENTRY_EO_CLASS_TYPE
#define _JK_ENTRY_EO_CLASS_TYPE

typedef Eo Jk_Entry;

#endif

#ifndef _JK_ENTRY_EO_TYPES
#define _JK_ENTRY_EO_TYPES


#endif
EAPI void jk_entry_min_max_set(Jk_Entry *obj, double min, double max);
EAPI void jk_entry_min_max_get(const Jk_Entry *obj, double *min, double *max);
EAPI void jk_entry_step_set(Jk_Entry *obj, double step);
EAPI double jk_entry_step_get(const Jk_Entry *obj);
EAPI void jk_entry_wrap_set(Jk_Entry *obj, Eina_Bool wrap);
EAPI Eina_Bool jk_entry_wrap_get(const Jk_Entry *obj);
EAPI void jk_entry_interval_set(Jk_Entry *obj, double interval);
EAPI double jk_entry_interval_get(const Jk_Entry *obj);
EAPI void jk_entry_round_set(Jk_Entry *obj, int rnd);
EAPI int jk_entry_round_get(const Jk_Entry *obj);
EAPI void jk_entry_editable_set(Jk_Entry *obj, Eina_Bool editable);
EAPI Eina_Bool jk_entry_editable_get(const Jk_Entry *obj);
EAPI void jk_entry_base_set(Jk_Entry *obj, double base);
EAPI double jk_entry_base_get(const Jk_Entry *obj);
EAPI void jk_entry_value_set(Jk_Entry *obj, double val);
EAPI double jk_entry_value_get(const Jk_Entry *obj);
EAPI double jk_entry_value_saved_get(const Jk_Entry *obj);
EAPI void jk_entry_label_format_set(Jk_Entry *obj, const char *fmt);
EAPI const char *jk_entry_label_format_get(const Jk_Entry *obj);
EAPI void jk_entry_special_value_add(Jk_Entry *obj, double value, const char *label);

#endif
