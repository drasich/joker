#include "property.h"
#include "Elementary.h"

Evas_Object* 
//_property_add_entry(ComponentProperties* cp, const Property* p, void* data, Evas_Object* box)
_property_add_entry(Evas_Object* win, void* data, const char* name)
{
  Evas_Object *en, *bx2, *label;

  bx2 = elm_box_add(win);
  elm_box_horizontal_set(bx2, EINA_TRUE);
  evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

  label = elm_label_add(win);
  char s[256];

  sprintf(s, "<b> %s </b> : ", name);

  elm_object_text_set(label, s);
  evas_object_show(label);
  elm_box_pack_end(bx2, label);

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
  elm_box_pack_end(bx2, en);

  evas_object_name_set(en, name);

  //evas_object_data_set(en, "property", p);
  evas_object_data_set(en, "data", data );
  //cp->entries = eina_list_append(cp->entries, en);

  /*
  evas_object_smart_callback_add(en, "changed,user", _entry_changed_cb, cp);
  evas_object_smart_callback_add(en, "activated", _entry_activated_cb, cp);
  evas_object_smart_callback_add(en, "aborted", _entry_aborted_cb, cp);
  evas_object_smart_callback_add(en, "focused", _entry_focused_cb, cp);
  evas_object_smart_callback_add(en, "unfocused", _entry_unfocused_cb, cp);
  evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, cp);
  */

  elm_entry_context_menu_disabled_set(en, EINA_TRUE);
  
  //elm_box_pack_end(box, bx2);
  evas_object_show(bx2);

  //property_holder_object_add(data + p->offset, p, en);

  //return en;
  return en;
}


