#include "property.h"
#include "Elementary.h"

static void
_entry_changed_cb(void *data, Evas_Object *obj, void *event)
{
  const char* s = elm_object_text_get(obj);
  JkProperty* p = data;

  if (p->changed)
  p->changed(p->data, s);
}

JkProperty*
property_entry_new(Evas_Object* win)
{
  JkProperty* p = calloc(1, sizeof *p);
  Evas_Object *en, *bx, *label;

  bx = elm_box_add(win);
  elm_box_horizontal_set(bx, EINA_TRUE);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

  label = elm_label_add(win);
  char s[256];

  //sprintf(s, "<b> %s </b> : ", name);
  sprintf(s, "<b> %s </b> : ", "thename");

  elm_object_text_set(label, s);
  evas_object_show(label);
  elm_box_pack_end(bx, label);

  en = elm_entry_add(win);
  elm_entry_scrollable_set(en, EINA_TRUE);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
  elm_object_text_set(en, "none");
  //elm_entry_scrollbar_policy_set(en, 
  //      ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
  elm_entry_single_line_set(en, EINA_TRUE);
  //elm_entry_select_all(en);
  evas_object_show(en);
  elm_box_pack_end(bx, en);

  //evas_object_name_set(en, name);

  evas_object_smart_callback_add(en, "changed,user", _entry_changed_cb, p);
  /*
  evas_object_smart_callback_add(en, "activated", _entry_activated_cb, cp);
  evas_object_smart_callback_add(en, "aborted", _entry_aborted_cb, cp);
  evas_object_smart_callback_add(en, "focused", _entry_focused_cb, cp);
  evas_object_smart_callback_add(en, "unfocused", _entry_unfocused_cb, cp);
  evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, cp);
  */

  elm_entry_context_menu_disabled_set(en, EINA_TRUE);
  
  evas_object_show(bx);

  p->en = en;
  p->root = bx;

  return p;
}

void property_register_cb(
      JkProperty* t,
      property_changed changed,
      property_get get
      )
{
  t->changed = changed;
  t->get = get;
}

void property_data_set(
      JkProperty* p,
      const void* data
      )
{
  p->data = data;

  if (p->get){
    const char* name = p->get(data);
    printf("yo my name is %s\n", name);
    elm_object_text_set(p->en, strdup(name));
  }
}



JkPropertySet*
property_set_new(Evas_Object* win)
{
  JkPropertySet* p = calloc(1, sizeof *p);
  Evas_Object *bx;

  bx = elm_box_add(win);
  elm_box_horizontal_set(bx, EINA_FALSE);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

  evas_object_show(bx);
  p->root = bx;
  p->box = bx;

  p->fields = eina_hash_stringshared_new(NULL);

  return p;
}

void
property_set_data_set(JkPropertySet* set, void* data)
{
  set->data = data;
}

void
property_set_string_add(
      JkPropertySet* ps,
      const char* name,
      const char* value
      )
{
  Evas_Object* bx = elm_box_add(ps->box);
  elm_box_horizontal_set(bx, EINA_TRUE);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(bx);

  Evas_Object* label = elm_label_add(ps->box);
  char s[256];
  sprintf(s, "<b> %s </b> : ", name);

  elm_object_text_set(label, s);
  evas_object_show(label);
  elm_box_pack_end(bx, label);
  evas_object_show(label);

  Evas_Object* en = elm_entry_add(ps->box);
  elm_entry_scrollable_set(en, EINA_TRUE);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
  elm_object_text_set(en, value);
  //elm_entry_scrollbar_policy_set(en, 
  //      ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
  elm_entry_single_line_set(en, EINA_TRUE);
  //elm_entry_select_all(en);
  evas_object_show(en);
  elm_box_pack_end(bx, en);

  evas_object_name_set(en, name);

  /*
  evas_object_smart_callback_add(en, "changed,user", _entry_changed_cb, p);
  evas_object_smart_callback_add(en, "activated", _entry_activated_cb, cp);
  evas_object_smart_callback_add(en, "aborted", _entry_aborted_cb, cp);
  evas_object_smart_callback_add(en, "focused", _entry_focused_cb, cp);
  evas_object_smart_callback_add(en, "unfocused", _entry_unfocused_cb, cp);
  evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, cp);
  */

  elm_entry_context_menu_disabled_set(en, EINA_TRUE);

  elm_box_pack_end(ps->box, bx);
}

void
property_set_float_add(JkPropertySet* ps, const char* name, float value)
{
  //TODO
}

void
property_set_clear(JkPropertySet* ps)
{
  elm_box_clear(ps->box);

}

