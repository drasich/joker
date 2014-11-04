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

PropertyNode* property_node_new()
{
  PropertyNode* node = calloc(1, sizeof *node);
  node->leafs = eina_hash_stringshared_new(NULL);
  node->nodes = eina_hash_stringshared_new(NULL);

  return node;
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

  //p->fields = eina_hash_stringshared_new(NULL);
  p->node = property_node_new();

  return p;
}

void
property_set_data_set(JkPropertySet* set, void* data)
{
  set->data = data;
}

PropertyNode* _property_node_find(
      JkPropertySet* ps,
      const char* path)
{
  char** s = eina_str_split(path, "/", 0);

  PropertyNode* node = ps->node;

  int i = 0;
  while (s[i]) {
    printf("%s\n", s[i]);

    if (s[i+1]) {
      PropertyNode* next = eina_hash_find(node->nodes, s[i]);
      if (next) {
        node = next;
        i++;
      }
      else {
        break;
      }
    }
    else {
      break;
    }
  }

   free(s[0]);
   free(s);

   return node;
}

Evas_Object* _property_leaf_find(
      JkPropertySet* ps,
      const char* path)
{
  PropertyNode* node = _property_node_find(ps, path);

  if (node) {
    return eina_hash_find(node->leafs, path);
  }

  return NULL;
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

  unsigned int num;
  char** ss = eina_str_split_full(name, "/", 0, &num);

  Evas_Object* label = elm_label_add(ps->box);
  char s[256];
  sprintf(s, "<b> %s </b> : ", ss[num-1]);//name);

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

  PropertyNode* node = _property_node_find(ps, name);
  eina_hash_add(node->leafs, eina_stringshare_add(name), en);
}

static void
_spinner_changed_cb(void* data, Evas_Object *obj, void* event)
{
  JkPropertySet* ps = data;
  const char* name = evas_object_name_get(obj);
  double v =  elm_spinner_value_get(obj);
  if (ps->changed) {
    ps->changed(ps->data, name, &v);
  }

}

void
property_set_float_add(
      JkPropertySet* ps, 
      const char* name,
      float value)
{
  //TODO
  Evas_Object* bx = elm_box_add(ps->box);
  elm_box_horizontal_set(bx, EINA_TRUE);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(bx);

  Evas_Object* label = elm_label_add(ps->box);
   {
    unsigned int num;
    char** ss = eina_str_split_full(name, "/", 0, &num);

  char s[256];
  sprintf(s, "<b> %s </b> : ", ss[num-1]);//name);

  elm_object_text_set(label, s);
  evas_object_show(label);
  elm_box_pack_end(bx, label);
  evas_object_show(label);
   }

  Evas_Object* sp = elm_spinner_add(ps->box);
  evas_object_name_set(sp, name);

  evas_object_size_hint_weight_set(sp, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(sp, EVAS_HINT_FILL, 0.5);
  evas_object_size_hint_min_set(sp,1,1);
  //elm_spinner_value_set(en, atof(value));
  evas_object_show(sp);
  //elm_box_pack_end(cp->box, en);
  elm_box_pack_end(bx, sp);

  elm_spinner_step_set(sp, 0.1);
  elm_spinner_min_max_set(sp, -DBL_MAX, DBL_MAX);
  //elm_object_style_set (en, "vertical");
  elm_spinner_editable_set(sp, EINA_TRUE);

  char ff[50];
    //sprintf(ff, "%s : %s", name, "%.3f");
    sprintf(ff, "%s", "%.3f");

  elm_spinner_label_format_set(sp, ff);
  elm_spinner_value_set(sp,value);

  elm_box_pack_end(ps->box, bx);

  PropertyNode* node = _property_node_find(ps, name);
  eina_hash_add(node->leafs, eina_stringshare_add(name), sp);

  evas_object_smart_callback_add(sp, "changed", _spinner_changed_cb, ps );
}

void
property_set_clear(JkPropertySet* ps)
{
  elm_box_clear(ps->box);

}

void property_set_string_update(
      JkPropertySet* set,
      const char* path,
      const char* value)
{
  Evas_Object* o = _property_leaf_find(set, path);

  if (o) {
    elm_object_text_set(o, value);
  }
  else {
    printf("could not find string property with path '%s'\n", path);
  }
}

void property_set_float_update(JkPropertySet* set, const char* path, float value)
{
  Evas_Object* o = _property_leaf_find(set, path);

  if (o) {
    elm_spinner_value_set(o, value);
  }
  else {
    printf("could not find float property with path '%s'\n", path);
  }

}

void jk_property_set_register_cb(
      JkPropertySet* ps,
      void * data,
      property_set_changed changed
      )
{
  ps->data = data;
  ps->changed = changed;
}

void property_set_node_add(
      JkPropertySet* ps, 
      const char* path)
{
  PropertyNode* node = _property_node_find(ps, path);
  if (node) {
    unsigned int num;
    char** s = eina_str_split_full(path, "/", 0, &num);
    PropertyNode* child = property_node_new();
    eina_hash_add(node->nodes, s[num-1], child);
  }

}

