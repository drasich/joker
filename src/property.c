#include "property.h"
#include "Elementary.h"
#include "panel.h"

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

static Eina_Bool _nodes_print(
      const Eina_Hash *hash,
      const void *key,
      void *data,
      void *fdata)
{
  printf("key : '%s'\n", key);
}

Eo* jk_property_panel_new(Window* w, int x, int y, int width, int height)
{
  Evas_Object* panel = layout_panel_add(w->win, "property");
  evas_object_move(panel, x, y);
  evas_object_show(panel);

  evas_object_resize(panel, width, height);

  return panel;
}

void jk_property_cb_register(
      JkPropertyCb* cb,
      property_changed2 changed_float,
      property_changed2 changed_string,
      property_changed2 changed_enum,
      property_register_change register_change_string,
      property_register_change register_change_float,
      property_register_change register_change_enum,
      property_register_change register_change_option,
      property_tree_object_cb expand,
      property_tree_object_cb contract,
      property_register_change vec_add,
      property_register_change vec_del
      )
{
  cb->changed_float = changed_float;
  cb->changed_string = changed_string;
  cb->changed_enum = changed_enum;
  cb->register_change_string = register_change_string;
  cb->register_change_float = register_change_float;
  cb->register_change_enum = register_change_enum;
  cb->register_change_option = register_change_option;
  cb->expand = expand;
  cb->contract = contract;

  cb->vec_add = vec_add;
  cb->vec_del = vec_del;
}

Eo* _node_create(PropertyValue* val, Evas_Object* o)
{
  Eo* bx = elm_box_add(o);
  elm_box_horizontal_set(bx, EINA_FALSE);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx, 0, 0.5);

  Eo* bx_child = elm_box_add(o);
  elm_box_horizontal_set(bx_child, EINA_FALSE);
  evas_object_size_hint_weight_set(bx_child, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx_child, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx_child, 0, 0.5);
  val->child = bx_child;

  Eo* bx_label = elm_box_add(o);
  elm_box_horizontal_set(bx_label, EINA_TRUE);
  evas_object_size_hint_weight_set(bx_label, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx_label, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_align_set(bx_label, 0, 0.5);


  Evas_Object* label = elm_label_add(o);

  unsigned int num;
  char** ss = eina_str_split_full(val->path, "/", 0, &num);
  const char* name = ss[num-1];

  char s[256];
  if (val->added_name){
    sprintf(s, "<b>%s</b> : %s", name, val->added_name);
  }
  else {
    sprintf(s, "<b>%s</b>", name);
  }
  //if (val->item && elm_genlist_item_expanded_get(val->item))
  //sprintf(s, "%s : ", name);
  //else
  //sprintf(s, "%s", name);

  elm_object_text_set(label, s);
  elm_box_pack_end(bx, bx_label);
  elm_box_pack_end(bx_label, label);
  evas_object_show(label);
  evas_object_show(bx);
  elm_box_pack_end(bx, bx_child);
  evas_object_show(bx_child);
  evas_object_show(bx_label);

  free(ss[0]);
  free(ss);
  return bx;
}

PropertyValue* property_node_add(const char* path)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);
  val->create_child = _node_create;

  return val;
}

