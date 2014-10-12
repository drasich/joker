#include "property.h"
#include "Elementary.h"

static void
_entry_changed_cb(void *data, Evas_Object *obj, void *event)
{
  const char* s = elm_object_text_get(obj);
  Property* p = data;

  if (p->changed)
  p->changed(p, s);
}

Property*
property_entry_new(Evas_Object* win)
{
  Property* p = calloc(1, sizeof *p);
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
      Property* t,
      property_changed changed)
{
  t->changed = changed;
}


