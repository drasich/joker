#include "property.h"

static char *
gl_text_get_node(
      void *data,
      Evas_Object *obj EINA_UNUSED,
      const char *part EINA_UNUSED)
{
  char* path = data;
  unsigned int num;
  char** ss = eina_str_split_full(path, "/", 0, &num);
  return strdup(ss[num-1]);
}

static void
_entry_changed_cb_list(
      void* data,
      Evas_Object *obj,
      void* event)
{
  PropertyValue* val = data;
  JkPropertyList* pl = val->list;
  //const char* name = evas_object_name_get(obj);
  const char* value = elm_object_text_get(obj);

  if (pl->changed_string) {
    //pl->changed_string(pl->data, val->path, value);
    pl->register_change_string(pl->data, val->path, NULL, value, 0);
  }
}

static void
_entry_focused_cb(
      void* data,
      Evas_Object *obj,
      void* event)
{
  const char* value = elm_object_text_get(obj);
  evas_object_data_set(obj, "saved_text", eina_stringshare_add(value));
  printf("setting saved text to %s \n", value);
}

static void
_entry_activated_cb(
      void* data,
      Evas_Object *obj,
      void* event)
{
  printf("entry activated!!!!!!!!!!!!!!.\n");
  PropertyValue* val = data;
  JkPropertyList* pl = val->list;
  //const char* name = evas_object_name_get(obj);
  const char* value = elm_object_text_get(obj);
  const char* old = evas_object_data_get(obj, "saved_text");

  if (old == NULL) {
    printf("problem with the old value.........\n");
    return;
  }

  evas_object_data_set(obj, "saved_text", eina_stringshare_add(value));

  if (pl->register_change_string) {
    pl->register_change_string(pl->data, val->path, old, value, 1);
  }
}

static void
_spinner_drag_start_cb(void *data, Evas_Object *obj, void *event)
{
  printf("spinner drag start\n");
  double *v = calloc(1, sizeof *v);
  *v = elm_spinner_value_get(obj);
  //TODO alloc the double
  evas_object_data_set(obj, "saved", v);

  /*
  ComponentProperties* cp = data;
  double v =  elm_spinner_value_get(obj);
  eina_value_setup(&cp->saved, EINA_VALUE_TYPE_DOUBLE);
  eina_value_set(&cp->saved, v);

  //TODO I have to know the original quaternion
  Property* p = evas_object_data_get(obj, "property");
  void* thedata = evas_object_data_get(obj, "data");

  Quat q;
  int offset = property_offset_get(p);
  memcpy(&q, thedata + offset, sizeof q);
  cp->quat_saved = q;
  */
}


static void
_spinner_drag_stop_cb(void *data, Evas_Object *obj, void *event)
{
  double *saved = evas_object_data_get(obj,"saved");
  printf("spinner drag stop %f \n", *saved);

  PropertyValue* val = data;
  JkPropertyList* pl = val->list;

  double d = elm_spinner_value_get(obj);

  if (pl->register_change_float) {
    pl->register_change_float(pl->data, val->path, saved, &d, 1);
  }

  free(saved);
  /*
  ComponentProperties* cp = data;
  double v =  elm_spinner_value_get(obj);
  Property* p = evas_object_data_get(obj, "property");
  void* thedata = evas_object_data_get(obj, "data");
  if (p->type == EET_T_DOUBLE){
    double *old = malloc(sizeof *old);
    eina_value_get(&cp->saved, old);
    double *new = malloc(sizeof *new);
    *new = v;
    control_property_change(cp->control, cp->component, thedata, p, old, new);
  }
  else if (p->type == EET_T_FLOAT){
    float *old = malloc(sizeof *old);
    eina_value_get(&cp->saved, old);
    float *new = malloc(sizeof *new);
    *new = v;
    control_property_change(cp->control, cp->component, thedata, p, old, new);
  }
  else if (p->type == PROPERTY_QUAT) {
    Quat *old = malloc(sizeof *old);
    //TODO use eina_value
    //eina_value_get(&cp->saved, old);
    *old = cp->quat_saved;
    Quat *new = malloc(sizeof *new);
    memcpy(new, thedata+p->offset, sizeof*new);
    control_property_change(cp->control, cp->component, thedata, p, old, new);
  }
  else if (p->type == PROPERTY_UNIFORM) {
    //TODO uniform undo/redo
    int offset = property_offset_get(p);
    UniformValue* uv = thedata + offset;
    if (uv->type == UNIFORM_FLOAT) {
      double d;
      eina_value_get(&cp->saved, &d);
      float *old = malloc(sizeof *old);
      *old = d;
      float *new = malloc(sizeof *new);
      *new = v;
      control_property_change(cp->control, cp->component, &uv->value.f, p, old, new);
    }
    else if (uv->type == UNIFORM_VEC3) {
      Vec3 *new = malloc(sizeof *new);
      *new = uv->value.vec3;
      Vec3 *old = malloc(sizeof *old);
      *old = uv->value.vec3;
      double d;
      eina_value_get(&cp->saved, &d);
      const char* pname = evas_object_data_get(obj, "property_name");
      if (!strcmp(pname, "x"))
      old->x = d;
      else if (!strcmp(pname, "y"))
      old->y = d;
      else if (!strcmp(pname, "z"))
      old->z = d;

      if (vec3_equal(*old, *new)) {
        free(old);
        free(new);
      }
      else
      control_property_change(cp->control, cp->component, &uv->value.vec3, p, old, new);
    }
    else if (uv->type == UNIFORM_VEC4) {
      Vec4 *new = malloc(sizeof *new);
      *new = uv->value.vec4;
      Vec4 *old = malloc(sizeof *old);
      *old = uv->value.vec4;
      double d;
      eina_value_get(&cp->saved, &d);
      const char* pname = evas_object_data_get(obj, "property_name");
      if (!strcmp(pname, "x"))
      old->x = d;
      else if (!strcmp(pname, "y"))
      old->y = d;
      else if (!strcmp(pname, "z"))
      old->z = d;
      else if (!strcmp(pname, "w"))
      old->w = d;

      if (vec4_equal(*old, *new)) {
        free(old);
        free(new);
      }
      else
      control_property_change(cp->control, cp->component, &uv->value.vec4, p, old, new);
    }
  }
*/

}

Evas_Object*
gl_content_string_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  Evas_Object *bx, *bt, *ck;

  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);

  Evas_Object* label = elm_label_add(bx);

  PropertyValue* val = data;

  char s[256];
  //sprintf(s, "<b> %s </b> : ", val->path);
  sprintf(s, "%s : ", val->path);

  elm_object_text_set(label, s);
  evas_object_show(label);
  elm_box_pack_end(bx, label);
  evas_object_show(label);

  Evas_Object* en = elm_entry_add(obj);
  elm_entry_scrollable_set(en, EINA_TRUE);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
  const char* value = val->data;
  elm_object_text_set(en, value);
  //elm_entry_scrollbar_policy_set(en, 
  //      ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
  elm_entry_single_line_set(en, EINA_TRUE);
  //elm_entry_select_all(en);
  evas_object_show(en);
  elm_box_pack_end(bx, en);

  evas_object_smart_callback_add(en, "changed,user", _entry_changed_cb_list, val);
  evas_object_smart_callback_add(en, "focused", _entry_focused_cb, val);
  evas_object_smart_callback_add(en, "activated", _entry_activated_cb, val);
  evas_object_smart_callback_add(en, "unfocused", _entry_activated_cb, val);
  //evas_object_smart_callback_add(en, "unfocused", _entry_unfocused_cb, cp);
  //TODO
  /*
  evas_object_smart_callback_add(en, "aborted", _entry_aborted_cb, cp);
  evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, cp);
  */

   return bx;
}

Eina_Bool
gl_state_get(
      void *data EINA_UNUSED,
      Evas_Object *obj EINA_UNUSED,
      const char *part EINA_UNUSED)
{
  return EINA_FALSE;
}

static Eina_Bool _nodes_print(
      const Eina_Hash *hash,
      const void *key,
      void *data,
      void *fdata)
{
  printf("key : '%s'\n", key);
}


static PropertyNode* 
_property_node_find(
      PropertyNode* node,
      char** s)
{
  PropertyNode* result = NULL;
  PropertyNode* root = node;
  int i = 0;
  while (s[i]) {
    /* PropertyNode* next = eina_hash_find(node->nodes, s[i]);
    if (next) {
      node = next;
      i++;
    }
    */
    PropertyNode* next = eina_hash_find(root->nodes, s[i]);
    if (next) {
      root = next;
      result = next;
      i++;
    }
    else {
      if (!s[i +1]) {
        // i is the last string
        //might be a leaf or unfound node
        //leaf => why trying to find a leaf?
        //unfound node => print error
        printf("leaf or unfound node : %s\n", s[i]);
        break;
      }
      else {
        //there still is something
        printf("node find,,, could not find : %s\n", s[i]);
        result = NULL;
        break;
      }
    }
    /*
    result = eina_hash_find(root->nodes, s[i]);
    if (result) {
      printf("I found %s\n", s[i]);
      root = result;
      i++;
    }
    else {
      printf("yooooo could not find %s\n\n", s[i]);
      eina_hash_foreach(root->nodes,_nodes_print, NULL);
      printf("end of listing nodes \n");
      break;
    }
    */
  }

  //return node;
  return result;
}

static Elm_Genlist_Item_Class *class_entry, *class_group, *class_node,*class_float;

static void
_spinner_changed_cb_list(
      void* data,
      Evas_Object *obj,
      void* event)
{
  PropertyValue* val = data;
  JkPropertyList* pl = val->list;
  const char* name = evas_object_name_get(obj);
  double v =  elm_spinner_value_get(obj);
  float f = v;
  memcpy(val->data, &f, sizeof f);

  if (pl->changed_float) {
    pl->changed_float(pl->data, val->path, &v);
  }
}

Evas_Object*
gl_content_float_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  Evas_Object *bx, *bt, *ck;

  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);

  PropertyValue* val = data;

  const char* name;

  Evas_Object* label = elm_label_add(obj);
   {
    unsigned int num;
    char** ss = eina_str_split_full(val->path, "/", 0, &num);
    name = ss[num-1];

    char s[256];
    //sprintf(s, "<b> %s </b> : ", name);
    sprintf(s, "%s : ", name);

    elm_object_text_set(label, s);
    evas_object_show(label);
    elm_box_pack_end(bx, label);
   }

  Evas_Object* sp = elm_spinner_add(obj);
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
  const float* f = val->data;
  elm_spinner_value_set(sp, *f);

  //PropertyNode* node = _property_set_node_find(ps, name);
  //eina_hash_add(node->leafs, eina_stringshare_add(name), sp);

  evas_object_smart_callback_add(sp, "changed", _spinner_changed_cb_list, val);

  evas_object_smart_callback_add(sp, "spinner,drag,start", _spinner_drag_start_cb, val);
  evas_object_smart_callback_add(sp, "spinner,drag,stop", _spinner_drag_stop_cb, val);

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
   //Evas_Object *gl = elm_object_item_widget_get(glit);

   //could be propertyvalue is not node
   char* name = elm_object_item_data_get(glit);
   JkPropertyList* pl = data;

   if (pl->expand) {
     pl->expand(pl->data, name, glit);
   }
}

static void
gl9_con(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_subitems_clear(glit);

   char* name = elm_object_item_data_get(glit);
   JkPropertyList* pl = data;
   //TODO clear the nodes

   if (pl->contract) {
     pl->contract(pl->data, name, glit);
   }
}


static void
_property_value_free_cb(void *data)
{
  PropertyValue* val = data;
  free(val->data);
  free(val);
}

static void
_property_node_clear(void* data)
{
  PropertyNode* node = data;
  printf("node clear, %d, %d \n", 
        eina_hash_population(node->nodes),
        eina_hash_population(node->leafs)
          );
  eina_hash_free(node->nodes);
  eina_hash_free(node->leafs);
  node->leafs = eina_hash_string_superfast_new(_property_value_free_cb);
  node->nodes = eina_hash_string_superfast_new(_property_node_clear);
}

PropertyNode* property_list_node_new()
{
  PropertyNode* node = calloc(1, sizeof *node);
  node->leafs = eina_hash_string_superfast_new(_property_value_free_cb);
  node->nodes = eina_hash_string_superfast_new(_property_node_clear);

  return node;
}

void
property_list_clear(JkPropertyList* pl)
{
  elm_genlist_clear(pl->list);
  _property_node_clear(pl->node);
}

PropertyNode* _property_list_node_find(
      JkPropertyList* pl,
      const char* path)
{
  PropertyNode* node = NULL;
  unsigned int count;
  char** s = eina_str_split_full(path, "/", 0, &count);

  if (strcmp(s[0], "object")) {
    printf("%s, it's not an object? this property is %s\n", __FUNCTION__, path);
  }
  else {
    if (count == 1) {
      node = pl->node;
    }
    else if (count > 1) {
      //node = _property_node_find(pl->node, &s[1]);
      node = _property_node_find(pl->node, s);
    }
  }

  free(s[0]);
  free(s);
  return node;
}


void property_list_node_add(
      JkPropertyList* pl, 
      const char* path)
{
  PropertyNode* node = _property_list_node_find(pl, path);
  if (!node) {
    printf("%s, could not find a root for %s\n", __FUNCTION__, path);
    return;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_list_node_new();
  eina_hash_add(node->nodes, s[num-1], child);

  printf("adding node : %s \n", s[num-1]);
  
  child->item = elm_genlist_item_append(pl->list, class_node,
                           path,//strdup(s[num-1]), 
                           node->item, //git/* parent */, 
                           ELM_GENLIST_ITEM_TREE,
                           NULL,//gl4_sel/* func */,
                           NULL/* func data */);

  printf("added node : parent node %p, child name %s, child node %p, child item %p \n",
        node, s[num-1],child, child->item);
}

void property_list_nodes_remove(
      JkPropertyList* pl, 
      const char* path)
{
  PropertyNode* node = _property_list_node_find(pl, path);
  if (!node) {
    printf("%s, could not find node with name '%s' \n", __FUNCTION__, path);
    return;
  }

  _property_node_clear(node);
}

void property_list_group_add(
      JkPropertyList* pl, 
      const char* path)
{
  PropertyNode* node = _property_list_node_find(pl, path);
  if (!node) {
    printf("%s, could not find a root\n", __FUNCTION__);
    return;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_list_node_new();
  eina_hash_add(node->nodes, s[num-1], child);
  
  child->item = elm_genlist_item_append(pl->list, class_group,
                           strdup(s[num-1]), 
                           node->item, //git/* parent */, 
                           ELM_GENLIST_ITEM_GROUP,
                           NULL, //gl4_sel/* func */,
                           NULL/* func data */);

  //elm_genlist_item_select_mode_set(child->item, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);

  printf("added node : parent node %p, child name %s, child node %p, child item %p \n",
        node, s[num-1],child, child->item);
}

PropertyValue*
property_list_float_add(
      JkPropertyList* pl, 
      const char* path,
      float value)
{
  PropertyNode* node = _property_list_node_find(pl, path);
  if (!node) {
    printf("%s, could not find a root\n", __FUNCTION__);
    return NULL;
  }
  
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = path;
  val->list = pl;
  val->data = calloc(1, sizeof value);
  memcpy(val->data, &value, sizeof value);

  printf("size of value %d \n", sizeof value);

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);

  printf("pl list %p \n", pl->list);
  printf("class float %p \n", class_float);
  printf("node item %p \n", node->item);
  
  val->item = elm_genlist_item_append(pl->list, class_float,
                           val,//strdup(s[num-1]), 
                           node->item, 
                           ELM_GENLIST_ITEM_NONE,
                           NULL, //gl4_sel,
                           NULL);

  eina_hash_add(node->leafs, eina_stringshare_add(path), val);

  return val;
}

void property_list_float_update(
      PropertyValue* val,
      float value)
{
  printf("property list float update %f, item : %p \n", value, val->item);
  memcpy(val->data, &value, sizeof value);
  elm_genlist_item_update(val->item);
}

PropertyValue*
property_list_string_add(
      JkPropertyList* pl, 
      const char* path,
      const char* value)
{
  PropertyNode* node = _property_list_node_find(pl, path);
  if (!node) {
    printf("%s, could not find a root\n", __FUNCTION__);
    return NULL;
  }
  
  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);

  PropertyValue *val = calloc(1, sizeof *val);
  val->path = path;//s[num-1];
  val->list = pl;
  val->data = strdup(value);
  
  val->item = elm_genlist_item_append(pl->list, class_entry,
                           val,
                           node->item, 
                           ELM_GENLIST_ITEM_NONE,
                           NULL,
                           NULL);

  eina_hash_add(node->leafs, eina_stringshare_add(path), val);

  return val;
}

void property_list_string_update(
      PropertyValue* val,
      const char* value)
{
  if (val->data) free(val->data);

  val->data = strdup(value);
  elm_genlist_item_update(val->item);
}

void jk_property_list_register_cb(
      JkPropertyList* pl,
      void * data,
      property_set_changed changed_float,
      property_set_changed changed_string,
      property_register_change register_change_string,
      property_register_change register_change_float,
      property_tree_object_cb expand,
      property_tree_object_cb contract
      )
{
  pl->data = data;
  pl->changed_float = changed_float;
  pl->changed_string = changed_string;
  pl->register_change_string = register_change_string;
  pl->register_change_float = register_change_float;
  pl->expand = expand;
  pl->contract = contract;
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
  class_entry->func.text_get = NULL;
  class_entry->func.content_get = gl_content_string_get;
  class_entry->func.state_get = gl_state_get;
  class_entry->func.del = NULL;

  class_float = elm_genlist_item_class_new();
  class_float->item_style = "full";//"default";
  class_float->func.text_get = NULL;
  class_float->func.content_get = gl_content_float_get;
  class_float->func.state_get = gl_state_get;
  class_float->func.del = NULL;

  class_group = elm_genlist_item_class_new();
  class_group->item_style = "group_index";
  class_group->func.text_get = gl_text_get_node;
  class_group->func.content_get = NULL;
  class_group->func.state_get = NULL;
  class_group->func.del = NULL;

  class_node = elm_genlist_item_class_new();
  class_node->item_style = "default";
  class_node->func.text_get = gl_text_get_node;
  class_node->func.content_get = NULL;
  class_node->func.state_get = NULL;
  class_node->func.del = NULL;

  //elm_genlist_item_class_free(class_entry);
  //elm_genlist_item_class_free(class_group);
  //elm_genlist_item_class_free(class_node);

  evas_object_smart_callback_add(gl, "expand,request", gl9_exp_req, NULL);
  evas_object_smart_callback_add(gl, "contract,request", gl9_con_req, NULL);
  evas_object_smart_callback_add(gl, "expanded", gl9_exp, p);
  evas_object_smart_callback_add(gl, "contracted", gl9_con, p);

  p->list = gl;

  p->node = property_list_node_new();

  return p;
}
