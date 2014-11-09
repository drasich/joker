#include "property.h"
#include "Elementary.h"
static Elm_Genlist_Item_Class *class_entry, *class_group, *class_node;

static void
_entry_changed_cb(void *data, Evas_Object *obj, void *event)
{
  const char* s = elm_object_text_get(obj);
  JkProperty* p = data;

  if (p->changed)
  p->changed(p->data, s);
}

static void
_entry_changed_cb_ps(void *data, Evas_Object *obj, void *event)
{
  const char* s = elm_object_text_get(obj);
  JkPropertySet* ps = data;

  const char* name = evas_object_name_get(obj);
  if (ps->changed_string) {
    ps->changed_string(ps->data, name, s);
  }
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

  p->node = property_node_new();

  return p;
}

void
property_set_data_set(JkPropertySet* set, void* data)
{
  set->data = data;
}

PropertyNode* _property_node_find(
      PropertyNode* node,
      const char* path)
{
  char** s = eina_str_split(path, "/", 0);

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

PropertyNode* _property_set_node_find(
      JkPropertySet* ps,
      const char* path)
{
  return _property_node_find(ps->node, path);
}


Evas_Object* _property_leaf_find(
      JkPropertySet* ps,
      const char* path)
{
  PropertyNode* node = _property_set_node_find(ps, path);

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

  evas_object_smart_callback_add(en, "changed,user", _entry_changed_cb_ps, ps);
  /*
  evas_object_smart_callback_add(en, "activated", _entry_activated_cb, cp);
  evas_object_smart_callback_add(en, "aborted", _entry_aborted_cb, cp);
  evas_object_smart_callback_add(en, "focused", _entry_focused_cb, cp);
  evas_object_smart_callback_add(en, "unfocused", _entry_unfocused_cb, cp);
  evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, cp);
  */

  elm_entry_context_menu_disabled_set(en, EINA_TRUE);

  elm_box_pack_end(ps->box, bx);

  PropertyNode* node = _property_set_node_find(ps, name);
  eina_hash_add(node->leafs, eina_stringshare_add(name), en);
}

static void
_spinner_changed_cb(void* data, Evas_Object *obj, void* event)
{
  JkPropertySet* ps = data;
  const char* name = evas_object_name_get(obj);
  double v =  elm_spinner_value_get(obj);
  if (ps->changed_float) {
    ps->changed_float(ps->data, name, &v);
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

  PropertyNode* node = _property_set_node_find(ps, name);
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
      property_set_changed changed_float,
      property_set_changed changed_string
      )
{
  ps->data = data;
  ps->changed_float = changed_float;
  ps->changed_string = changed_string;
}

void property_set_node_add(
      JkPropertySet* ps, 
      const char* path)
{
  PropertyNode* node = _property_set_node_find(ps, path);
  if (!node) {
    printf("$s, could not find a root\n", __FUNCTION__);
    return;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_node_new();
  eina_hash_add(node->nodes, s[num-1], child);
  
  Evas_Object* label = elm_label_add(ps->box);
  char ls[256];
  sprintf(ls, "<b> %s </b> : ", s[num-1]);

  elm_object_text_set(label, ls);
  evas_object_show(label);
  elm_box_pack_end(ps->box, label);
  evas_object_show(label);
}

static void
gl4_sel(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   int depth = elm_genlist_item_expanded_depth_get(glit);
   printf("expanded depth for selected item is %d", depth);
}

static char *
gl_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   char buf[256];
   snprintf(buf, sizeof(buf), "Item # %i", (int)(uintptr_t)data);
   return strdup(buf);
}

static char *
gl_text_get_node(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
  char* t = data;
  printf("+++++++++++++++++++the data text is %s \n", t);
   char buf[256];
   snprintf(buf, sizeof(buf), "node '%s'", (const char*)data);
   return strdup(buf);
   //return strdup("node");
   //return strdup(*data);
}


Evas_Object *gl_content_get(void *data EINA_UNUSED, Evas_Object *obj, const char *part)
{
   char buf[PATH_MAX];
   Evas_Object *ic = elm_icon_add(obj);
   if (!strcmp(part, "elm.swallow.end"))
     snprintf(buf, sizeof(buf), "%s/images/bubble.png", elm_app_data_dir_get());
   else
     snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
   elm_image_file_set(ic, buf, NULL);
   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

Eina_Bool gl_state_get(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   return EINA_FALSE;
}

char *gl8_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   char buf[256];
   snprintf(buf, sizeof(buf), "Group Index # %i (Item # %i)", (int)((uintptr_t)data / 10), (int)(uintptr_t)data);
   return strdup(buf);
}

Evas_Object *gl_content_full_get(
      void *data EINA_UNUSED,
      Evas_Object *obj,
      const char *part)
{
   //Evas_Object *fr, *bx, *ic, *bt, *ck;
   Evas_Object *bx, *ic, *bt, *ck;

   if (strcmp(part, "elm.swallow.content") != 0) return NULL;

   /*
   fr = elm_frame_add(obj);
   elm_layout_text_set(fr, NULL, "A Frame");
   */

   //bx = elm_box_add(fr);
   bx = elm_box_add(obj);
   elm_box_horizontal_set(bx, EINA_TRUE);

   //unsigned int num;
   //char** ss = eina_str_split_full(name, "/", 0, &num);

   Evas_Object* label = elm_label_add(bx);
   //char s[256];
   //sprintf(s, "<b> %s </b> : ", ss[num-1]);//name);

   elm_object_text_set(label, "position:"); //s);
   evas_object_show(label);
   elm_box_pack_end(bx, label);
   evas_object_show(label);

   /*
   ic = elm_icon_add(bx);
   elm_icon_standard_set(ic, "home");
   evas_object_size_hint_min_set(ic, 32 * elm_config_scale_get(),
                                 32 * elm_config_scale_get());
   evas_object_size_hint_align_set(ic, 0.5, EVAS_HINT_FILL);
   evas_object_show(ic);
   elm_box_pack_end(bx, ic);
   */

   /*
   bt = elm_button_add(bx);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   //evas_object_smart_callback_add(bt, "clicked", on_bt_clicked, NULL);
   elm_layout_text_set(bt, NULL, "Click Me");
   evas_object_show(bt);
   elm_box_pack_end(bx, bt);
   */

   /*
   ck = elm_check_add(bx);
   evas_object_size_hint_align_set(ck, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   //evas_object_smart_callback_add(ck, "changed", on_ck_changed, NULL);
   elm_layout_text_set(ck, NULL, "some checkbox");
   evas_object_show(ck);
   elm_box_pack_end(bx, ck);
   */

   //elm_layout_content_set(fr, NULL, bx);
   //evas_object_size_hint_min_set(bt, 200 * elm_config_scale_get(),
    //     200 * elm_config_scale_get());

  Evas_Object* en = elm_entry_add(obj);
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


   //return fr;
   return bx;
}

static void
gl9_exp_req(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_TRUE);
}

static void
gl9_con_req(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_FALSE);
}

static void
gl9_exp(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   Evas_Object *gl = elm_object_item_widget_get(glit);
   int val = (int)(uintptr_t) elm_object_item_data_get(glit);
   val *= 10;
   elm_genlist_item_append(gl, class_entry,
                           (void *)(uintptr_t) (val + 1)/* item data */,
                           glit/* parent */,
                           ELM_GENLIST_ITEM_NONE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, class_entry,
                           (void *)(uintptr_t) (val + 2)/* item data */,
                           glit/* parent */,
                           ELM_GENLIST_ITEM_NONE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, class_node,
                           (void *)(uintptr_t) (val + 3)/* item data */,
                           glit/* parent */,
                           ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                           NULL/* func data */);
}

static void
gl9_con(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_subitems_clear(glit);
}

JkPropertyList*
property_list_new(Evas_Object* win)
{
  JkPropertyList* p = calloc(1, sizeof *p);

  Evas_Object *bx = elm_box_add(win);
  p->root = bx;
  //p->box = bx;
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(bx);

  Evas_Object* gl = elm_genlist_add(win);
  //evas_object_smart_callback_add(gl, "clicked,double", _gl_double_clicked, NULL);
  evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_NONE);
  elm_genlist_tree_effect_enabled_set(gl, EINA_TRUE);
  evas_object_show(gl);
  //elm_box_pack_end(bx, gl);
  p->root = gl;

  //Elm_Genlist_Item_Class *class_entry, *class_group, *class_node;
  class_entry = elm_genlist_item_class_new();
  class_entry->item_style = "full";//"default";
  class_entry->func.text_get = gl_text_get;
  //class_entry->func.content_get = gl_content_get;
  class_entry->func.content_get = gl_content_full_get;
  class_entry->func.state_get = gl_state_get;
  class_entry->func.del = NULL;

  class_group = elm_genlist_item_class_new();
  class_group->item_style = "group_index";
  class_group->func.text_get = gl8_text_get;
  class_group->func.content_get = NULL;
  class_group->func.state_get = NULL;
  class_group->func.del = NULL;

  class_node = elm_genlist_item_class_new();
  class_node->item_style = "default";
  class_node->func.text_get = gl_text_get_node;
  class_node->func.content_get = NULL;
  class_node->func.state_get = NULL;
  class_node->func.del = NULL;

  /*
  Elm_Object_Item* git;

   git = elm_genlist_item_append(gl, class_group,
                                 (void *)0,
                                 NULL,
                                 ELM_GENLIST_ITEM_GROUP,
                                 gl4_sel,
                                 NULL);
   elm_genlist_item_select_mode_set(git, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);

   elm_genlist_item_append(gl, class_node,
                           (void *)1,
                           git, 
                           ELM_GENLIST_ITEM_TREE,
                           gl4_sel,
                           NULL);
   elm_genlist_item_append(gl, class_entry,
                           (void *)2,
                           git,
                           ELM_GENLIST_ITEM_NONE,
                           gl4_sel,
                           NULL);
   elm_genlist_item_append(gl, class_node,
                           (void *)3,
                           git,
                           ELM_GENLIST_ITEM_TREE,
                           gl4_sel,
                           NULL);
   git = elm_genlist_item_append(gl, class_group,
                                 (void *)4,
                                 NULL,
                                 ELM_GENLIST_ITEM_GROUP, gl4_sel,
                                 NULL);
   elm_genlist_item_select_mode_set(git, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);

   elm_genlist_item_append(gl, class_node,
                           (void *)5,
                           git,
                           ELM_GENLIST_ITEM_TREE,
                           gl4_sel,
                           NULL);
   elm_genlist_item_append(gl, class_entry,
                           (void *)6,
                           git,
                           ELM_GENLIST_ITEM_NONE,
                           gl4_sel,
                           NULL);
   elm_genlist_item_append(gl, class_node,
                           (void *)7,
                           git,
                           ELM_GENLIST_ITEM_TREE,
                           gl4_sel,
                           NULL);
   */


  //elm_genlist_item_class_free(class_entry);
  //elm_genlist_item_class_free(class_group);
  //elm_genlist_item_class_free(class_node);

  evas_object_smart_callback_add(gl, "expand,request", gl9_exp_req, NULL);
  evas_object_smart_callback_add(gl, "contract,request", gl9_con_req, NULL);
  evas_object_smart_callback_add(gl, "expanded", gl9_exp, NULL);
  evas_object_smart_callback_add(gl, "contracted", gl9_con, NULL);

  p->list = gl;

  p->node = property_node_new();

  return p;

}

void
property_list_clear(JkPropertyList* pl)
{
  elm_genlist_clear(pl->list);
}

PropertyNode* _property_list_node_find(
      JkPropertyList* pl,
      const char* path)
{
  return _property_node_find(pl->node, path);
}


void property_list_node_add(
      JkPropertyList* pl, 
      const char* path)
{
  PropertyNode* node = _property_list_node_find(pl, path);
  if (!node) {
    printf("$s, could not find a root\n", __FUNCTION__);
    return;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_node_new();
  eina_hash_add(node->nodes, s[num-1], child);
  
  child->item = elm_genlist_item_append(pl->list, class_node,
                           strdup(s[num-1]), 
                           node->item, //git/* parent */, 
                           ELM_GENLIST_ITEM_TREE,
                           gl4_sel/* func */,
                           NULL/* func data */);
}

