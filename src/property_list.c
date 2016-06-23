#include "property.h"
#include <string.h>
#include <stdbool.h>
#include "common.h"
//#include "entry.h"
#include "entry/jk_entry.eo.h"

static Elm_Genlist_Item_Class 
                              *class_group,
                              *class_node,
                              *class_enum,
                              *class_option,
                              *class_item,
                              *class_vec,
                              *class_vec_node;

static PropertyNode*
_property_node_find(
      PropertyNode* node,
      char** s)
{
  PropertyNode* result = NULL;
  PropertyNode* root = node;
  int i = 0;
  while (s[i]) {
    PropertyNode* next = eina_hash_find(root->nodes, s[i]);
    if (next) {
      root = next;
      result = next;
      i++;
    }
    else {
      //eina_hash_foreach(root->nodes,_nodes_print, NULL);
      result = NULL;
      break;
    }
  }

  return result;
}


PropertyNode* _property_list_node_find(
      JkPropertyList* pl,
      const char* path)
{
  PropertyNode* node = NULL;

  if (path) {
    unsigned int count;
    char** s = eina_str_split_full(path, "/", 0, &count);

    node = _property_node_find(pl->node, s);
    if (!node && pl->node_first_group) {
      node = _property_node_find(pl->node_first_group, s);
    }

    free(s[0]);
    free(s);
  }

  if (node) {
    return node;
  }
  else if (pl->node_first_group) {
    return pl->node_first_group;
  }
  else {
    return pl->node;
  }
}

static const char*
get_parent_node_string(const char* path)
{
  char *c = strrchr(path,'/');

  if (!c) return NULL;

  size_t size = c - path + 1;
  if (size < 1) {
    return "error_string";
  }

  char* ret = calloc(1, size);
  strncpy(ret, path, size -1);
  ret[size -1] = '\0';
  return ret;
}

PropertyNode* _property_list_node_find_parent(
      JkPropertyList* pl,
      const char* path)
{
  const char* parent = get_parent_node_string(path);
  return _property_list_node_find(pl, parent);
}


static char *
gl_text_get_node(
      void *data,
      Evas_Object *obj EINA_UNUSED,
      const char *part EINA_UNUSED)
{
  //char* path = data;
  PropertyValue* val = data;
  const char* path = val->path;
  unsigned int num;
  char** ss = eina_str_split_full(path, "/", 0, &num);
  return strdup(ss[num-1]);
}

static char *
gl_text_get_group(
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
  JkPropertyCb* cbs = val->cbs;
  //const char* name = evas_object_name_get(obj);
  const char* value = elm_object_text_get(obj);

  if (cbs->register_change_string) {
    //pl->changed_string(pl->data, val->path, value);
    cbs->register_change_string(cbs->data, val->path, NULL, value, 0);
  }
}

struct _EntryState{
  Eina_Bool was_focused;
  Eina_Bool pressed;
};

static void
_entry_focused_cb(
      void* data,
      Evas_Object *obj,
      void* event)
{
  const char* value = elm_object_text_get(obj);
  evas_object_data_set(obj, "saved_text", eina_stringshare_add(value));

   struct _EntryState *es = evas_object_data_get(obj, "state");

  if (!es->pressed) {
    elm_entry_select_all(obj);
  }

  es->pressed = EINA_FALSE;
}

static Eina_Bool s_mouse_move = EINA_FALSE;

static void
_mouse_move(void *data, Evas* e, Eo* o, void* event)
{
    s_mouse_move = EINA_TRUE;
}

static void
_entry_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
   const char* name = elm_object_text_get(obj);

   struct _EntryState *es = evas_object_data_get(obj, "state");

   if (!es->was_focused && !s_mouse_move){
     elm_entry_select_all(obj);
   }

   es->pressed = EINA_FALSE;
   evas_object_event_callback_del(obj, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move);
}

static void
_entry_press_cb(void *data, Evas_Object *obj, void *event_info)
{
   const char* name = elm_object_text_get(obj);
   struct _EntryState *es = evas_object_data_get(obj, "state");

   Eina_Bool isfoc = elm_object_focus_get(obj);
   es->was_focused = isfoc;
   es->pressed = EINA_TRUE;

   s_mouse_move = EINA_FALSE;
   evas_object_event_callback_add(obj, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move, NULL);
}

static void
_entry_register_change_cb(
      void* data,
      Evas_Object *obj,
      void* event)
{
  PropertyValue* val = data;
  JkPropertyCb* cbs = val->cbs;
  //const char* name = evas_object_name_get(obj);
  const char* value = elm_object_text_get(obj);
  const char* old = evas_object_data_get(obj, "saved_text");

  if (old == NULL) {
    printf("problem with the old value.........\n");
    return;
  }

  evas_object_data_set(obj, "saved_text", eina_stringshare_add(value));

  if (cbs->register_change_string) {
    cbs->register_change_string(cbs->data, val->path, old, value, 1);
  }
}

static void
_spinner_drag_start_cb(void *data, Evas_Object *obj, void *event)
{
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

  PropertyValue* val = data;
  JkPropertyCb* cbs = val->cbs;

  double d = elm_spinner_value_get(obj);

  if (cbs->register_change_float) {
    cbs->register_change_float(cbs->data, val->path, saved, &d, 1);
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

Eo* entry_new(PropertyValue* val, Eo* obj)
{
  Eo* bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(bx);

  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);

  Evas_Object* label = elm_label_add(bx);

   {
    unsigned int num;
    char** ss = eina_str_split_full(val->path, "/", 0, &num);
    const char* name = ss[num-1];

    char s[256];
    //sprintf(s, "<b> %s </b> : ", name);
    sprintf(s, "%s : ", name);

    elm_object_text_set(label, s);
    evas_object_show(label);
    elm_box_pack_end(bx, label);

    free(ss[0]);
    free(ss);
   }

  Evas_Object* en = elm_entry_add(obj);
  elm_entry_scrollable_set(en, EINA_TRUE);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
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
  evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, NULL);
  evas_object_smart_callback_add(en, "press", _entry_press_cb, NULL);
  evas_object_smart_callback_add(en, "activated", _entry_register_change_cb, val);
  evas_object_smart_callback_add(en, "unfocused", _entry_register_change_cb, val);

  struct _EntryState *es = calloc(1, sizeof *es);
  evas_object_data_set(en, "state", es);

  //evas_object_smart_callback_add(en, "unfocused", _entry_unfocused_cb, cp);
  //TODO
  /*
  evas_object_smart_callback_add(en, "aborted", _entry_aborted_cb, cp);
  evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, cp);
  */

   return bx;
}


Evas_Object*
gl_content_string_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  Eo* bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);

  PropertyValue* val = data;
  Eo* en = entry_new(val, obj);
  elm_box_pack_end(bx, en);
  return bx;
}

Evas_Object*
gl_content_item_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  Eo* bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);

  PropertyValue* val = data;
  elm_box_pack_end(bx, val->create_child(val, obj));
  return bx;
}

struct _BtCb
{
  property_register_change cb;
  void* data;
};

static void _bt_cb(void* data)
{
  struct _BtCb *btcb = data;
  PropertyValue* val = btcb->data;
  btcb->cb(
        val->cbs->data,
        val->path,
        NULL,
        NULL,
        0);

  elm_genlist_item_update(val->item);

  Elm_Object_Item* parent = val->item;

  if ( elm_genlist_item_type_get(val->item) != ELM_GENLIST_ITEM_TREE)
  parent = elm_genlist_item_parent_get(val->item);

  elm_genlist_item_update(parent);

  if ( elm_genlist_item_type_get(parent) == ELM_GENLIST_ITEM_TREE &&
        elm_genlist_item_expanded_get(parent)) {
    //because tree anim takes time we have to do this
    elm_genlist_item_subitems_clear(parent);
    elm_genlist_item_expanded_set(parent, EINA_FALSE);
    elm_genlist_item_expanded_set(parent, EINA_TRUE);
  }
  else {
    printf("TODO remove and recreate....\n");
    //TODO recreate none -> tree
    // AND tree -> none
  }
}

Evas_Object*
gl_content_vec_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  Eo* bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  //elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);
  elm_box_align_set(bx, 0, 0.5f);

  PropertyValue* val = data;
  elm_box_pack_end(bx, val->create_child(val, obj));

  Eo* bt = elm_button_add(obj);
  elm_object_text_set(bt, "+");
  evas_object_show(bt);
  elm_box_pack_end(bx, bt);
  struct _BtCb *btcb = calloc(1, sizeof *btcb);
  btcb->cb = val->cbs->vec_add;
  btcb->data = val;
  btn_cb_set(bt, _bt_cb, btcb);

  bt = elm_button_add(obj);
  elm_object_text_set(bt, "-");
  evas_object_show(bt);
  elm_box_pack_end(bx, bt);
  btcb = calloc(1, sizeof *btcb);
  btcb->cb = val->cbs->vec_del;
  btcb->data = val;
  btn_cb_set(bt, _bt_cb, btcb);

  return bx;
}

Evas_Object*
gl_content_vec_node_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  Evas_Object *bx, *ck;

  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);
  elm_box_align_set(bx, 0, 1);
  //elm_box_align_set(bx, 0, 0.5f);
  elm_box_padding_set(bx, 4, 0);

  Evas_Object* label = elm_label_add(bx);

  PropertyValue* val = data;

   {
    unsigned int num;
    char** ss = eina_str_split_full(val->path, "/", 0, &num);
    const char* name = ss[num-1];

    char s[256];
    sprintf(s, "<b>%s</b>, len : %d", name, val->len);
    //if (val->item && elm_genlist_item_expanded_get(val->item))
    //sprintf(s, "%s : ", name);
    //else
    //sprintf(s, "%s", name);

    elm_object_text_set(label, s);
    elm_box_pack_end(bx, label);
    evas_object_show(label);

    free(ss[0]);
    free(ss);
   }

  Eo* bt = elm_button_add(obj);
  elm_object_text_set(bt, "+");
  evas_object_show(bt);
  elm_box_pack_end(bx, bt);
  struct _BtCb *btcb = calloc(1, sizeof *btcb);
  btcb->cb = val->cbs->vec_add;
  btcb->data = val;
  btn_cb_set(bt, _bt_cb, btcb);

   return bx;
}




static void
_hoversel_selected_cb(
      void *data,
      Evas_Object *obj,
      void *event_info)
{
  const char* old = elm_object_text_get(obj);
  const char *txt = elm_object_item_text_get(event_info);

  elm_object_text_set(obj, txt);

  PropertyValue* val = data;
  JkPropertyCb* cbs = val->cbs;
  ////const char* name = evas_object_name_get(obj);
  //const char* value = elm_object_text_get(obj);

  //WARNING... done in update
  //val->data = (char*) strdup(txt);

  //TODO
  if (cbs->register_change_enum) {
    //pl->changed_string(pl->data, val->path, value);
    cbs->register_change_enum(cbs->data, val->path, old, txt, 1);
  }

  if ( elm_genlist_item_type_get(val->item) == ELM_GENLIST_ITEM_TREE &&
        elm_genlist_item_expanded_get(val->item)) {
    //because tree anim takes time we have to do this
    elm_genlist_item_subitems_clear(val->item);
    elm_genlist_item_expanded_set(val->item, EINA_FALSE);
    elm_genlist_item_expanded_set(val->item, EINA_TRUE);
  }
}

static void
_update_option_item(
      PropertyValue* val,
      Elm_Genlist_Item_Type t
      )
{
  JkPropertyCb* cbs = val->cbs;

  char* old;
  char* new;
  if (t == ELM_GENLIST_ITEM_TREE)
   {
    old = strdup("None");
    new = strdup("Some");
  }
  else {
    old = strdup("Some");
    new = strdup("None");
  }

  Elm_Object_Item* old_item = val->item;

  printf("TODOOOOOOOOOOOOO, put in comment for now \n\n");
  /*

  PropertyNode* parent = _property_list_node_find_parent(pl, val->path);
  if (!parent) {
    printf("nodeeeeeeeeeee cannot find parent \n");
    return;
  }

  PropertyNode* option_node = _property_list_node_find(pl, val->path);
  if (!option_node) {
    printf("nodeeeeeeeeeee cannot find option node \n");
    return;
  }

  if (t == ELM_GENLIST_ITEM_NONE) {
    char* name = (char*) val->path;
    if (pl->cbs->contract) {
      pl->cbs->contract(pl->data, name, old_item);
    }
  }

  if (val->data) free(val->data);

  val->data = new;

  val->item = elm_genlist_item_insert_after(pl->list, class_option,
        val,
        parent->item,
        old_item,
        t,
        NULL,
        NULL);


  option_node->item = val->item;

  elm_object_item_del(old_item);

  if ( elm_genlist_item_type_get(val->item) == ELM_GENLIST_ITEM_TREE) {
    //because tree anim takes time we have to do this
    //elm_genlist_item_subitems_clear(val->item);
    //elm_genlist_item_expanded_set(val->item, EINA_FALSE);
    elm_genlist_item_expanded_set(val->item, EINA_TRUE);
  }
  */

}

static void
_on_button_option_clicked(
      void *data,
      Evas_Object *obj,
      void *event_info)
{
  PropertyValue* val = data;
  JkPropertyCb* cbs = val->cbs;

  Elm_Genlist_Item_Type t;
  const char* old = val->data;
  char* new;
  if (!strcmp(old, "None")) {
    new = strdup("Some");
    t = ELM_GENLIST_ITEM_TREE;
  }
  else {
    new = strdup("None");
    t = ELM_GENLIST_ITEM_NONE;
  }

  if (cbs->register_change_option) {
    cbs->register_change_option(cbs->data, val->path, old, new, 1);
    _update_option_item(val,t);
  }
}

Evas_Object*
gl_content_node_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  Evas_Object *bx, *bt, *ck;

  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);
  elm_box_align_set(bx, 0, 1);
  //elm_box_align_set(bx, 0, 0.5f);
  elm_box_padding_set(bx, 4, 0);

  Evas_Object* label = elm_label_add(bx);

  PropertyValue* val = data;

   {
    unsigned int num;
    char** ss = eina_str_split_full(val->path, "/", 0, &num);
    const char* name = ss[num-1];

    char s[256];
    sprintf(s, "<b>%s</b>", name);
    //if (val->item && elm_genlist_item_expanded_get(val->item))
    //sprintf(s, "%s : ", name);
    //else
    //sprintf(s, "%s", name);

    elm_object_text_set(label, s);
    elm_box_pack_end(bx, label);
    evas_object_show(label);

    free(ss[0]);
    free(ss);
   }

   return bx;
}

Eo* _node_create(PropertyValue* val, Evas_Object* o)
{
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
  //elm_box_pack_end(bx, label);
  evas_object_show(label);

  free(ss[0]);
  free(ss);
  return label;
}

static Eo* _enum_create(PropertyValue* val, Evas_Object* obj)
{
  Eo* bx = elm_box_add(obj);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_TRUE);
  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);
  elm_box_align_set(bx, 0, 1);
  //elm_box_align_set(bx, 0, 0.5f);
  elm_box_padding_set(bx, 4, 0);

  Evas_Object* label = elm_label_add(bx);

   {
    unsigned int num;
    char** ss = eina_str_split_full(val->path, "/", 0, &num);
    const char* name = ss[num-1];

    char s[256];
    sprintf(s, "<b>%s</b> : ", name);

    elm_object_text_set(label, s);
    evas_object_show(label);
    elm_box_pack_end(bx, label);

    free(ss[0]);
    free(ss);
   }

   {

  const char* value = val->data;
  Evas_Object* hoversel = elm_hoversel_add(obj);
  elm_hoversel_hover_parent_set(hoversel, obj);
  elm_object_text_set(hoversel, value);

  unsigned int num;
  char** s = eina_str_split_full(val->user_data, "/", 0, &num);
  int i;
  for (i = 0; i < num; ++i) {
    elm_hoversel_item_add(hoversel, strdup(s[i]), NULL, ELM_ICON_NONE, NULL, NULL);
  }

  free(s[0]);
  free(s);

  //evas_object_smart_callback_add(hoversel, "clicked",
   //                               _hoversel_clicked_cb, NULL);
   evas_object_smart_callback_add(hoversel, "selected",
                                  _hoversel_selected_cb, val);
   //evas_object_smart_callback_add(hoversel, "dismissed",
    //                              _hoversel_dismissed_cb, NULL);
  elm_box_pack_end(bx, hoversel);

  evas_object_show(hoversel);
   }

   return bx;
}


Eo*
gl_content_node_get2(
      void* data,
      Eo* obj,
      const char *part)
{
  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  Eo* bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

  elm_box_align_set(bx, 0, 0.5f);

  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);

  PropertyValue* val = data;
  if (val->create_child) {
    elm_box_pack_end(bx, val->create_child(val, obj));
  }
  else {
    Evas_Object* label = _node_create(val, bx);
    elm_box_pack_end(bx, label);
  }

  return bx;
}


Evas_Object*
gl_content_enum_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  Evas_Object *bx, *bt, *ck;

  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);
  elm_box_align_set(bx, 0, 1);
  //elm_box_align_set(bx, 0, 0.5f);
  elm_box_padding_set(bx, 4, 0);

  Evas_Object* label = elm_label_add(bx);

  PropertyValue* val = data;

   {
    unsigned int num;
    char** ss = eina_str_split_full(val->path, "/", 0, &num);
    const char* name = ss[num-1];

    char s[256];
    //sprintf(s, "<b> %s </b> : ", name);
    //if (val->item && elm_genlist_item_expanded_get(val->item))
    sprintf(s, "<b>%s</b> : ", name);
    //else
    //sprintf(s, "<b>%s</b>", name);

    elm_object_text_set(label, s);
    evas_object_show(label);
    elm_box_pack_end(bx, label);

    free(ss[0]);
    free(ss);
   }

  //if (val->item && elm_genlist_item_expanded_get(val->item))
   {

  const char* value = val->data;
  Evas_Object* hoversel = elm_hoversel_add(obj);
  elm_hoversel_hover_parent_set(hoversel, obj);
  elm_object_text_set(hoversel, value);

  unsigned int num;
  char** s = eina_str_split_full(val->user_data, "/", 0, &num);
  int i;
  for (i = 0; i < num; ++i) {
    elm_hoversel_item_add(hoversel, s[i], NULL, ELM_ICON_NONE, NULL, NULL);
  }

  free(s[0]);
  free(s);

  //evas_object_smart_callback_add(hoversel, "clicked",
   //                               _hoversel_clicked_cb, NULL);
   evas_object_smart_callback_add(hoversel, "selected",
                                  _hoversel_selected_cb, val);
   //evas_object_smart_callback_add(hoversel, "dismissed",
    //                              _hoversel_dismissed_cb, NULL);
  elm_box_pack_end(bx, hoversel);

  evas_object_show(hoversel);
   }

   return bx;
}

Eo*
gl_content_enum_get2(
      void* data,
      Eo* obj,
      const char *part)
{
  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  Eo* bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

  elm_box_align_set(bx, 0, 0.5f);

  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);

  PropertyValue* val = data;
  if (val->create_child) {
    elm_box_pack_end(bx, val->create_child(val, obj));
  }
  else {
    Evas_Object* label = _enum_create(val, bx);
    elm_box_pack_end(bx, label);
  }

  return bx;
}



Evas_Object*
gl_content_option_get(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  Evas_Object *bx, *bt, *ck;

  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_align_set(bx, 0, 1);
  elm_box_padding_set(bx, 4, 0);

  Evas_Object* label = elm_label_add(bx);

  PropertyValue* val = data;

   {
    unsigned int num;
    char** ss = eina_str_split_full(val->path, "/", 0, &num);
    const char* name = ss[num-1];

    char s[256];
    //sprintf(s, "<b> %s </b> : ", name);
    if (val->item && elm_genlist_item_expanded_get(val->item))
    sprintf(s, "%s : ", name);
    else
    sprintf(s, "%s", name);

    elm_object_text_set(label, s);
    evas_object_show(label);
    elm_box_pack_end(bx, label);

    free(ss[0]);
    free(ss);
   }

   {
    Evas_Object* btn = elm_button_add(obj);
    const char* value = val->data;

    if (!strcmp(value, "None")) {
      elm_object_text_set(btn, "Add");
    }
    else {
      elm_object_text_set(btn, "Remove");
    }

    evas_object_smart_callback_add(btn, "clicked",
          _on_button_option_clicked, val);
    elm_box_pack_end(bx, btn);

    evas_object_show(btn);
   }

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

static void
_spinner_changed_cb_list(
      void* data,
      Evas_Object *obj,
      void* event)
{
  PropertyValue* val = data;
  JkPropertyCb* cbs = val->cbs;
  const char* name = evas_object_name_get(obj);
  double v = elm_spinner_value_get(obj);
  float f = v;
  memcpy(val->data, &f, sizeof f);

  if (cbs->changed_float) {
    cbs->changed_float(cbs->data, val->path, &v);
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
  elm_box_padding_set(bx, 4, 0);

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

    free(ss[0]);
    free(ss);
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
_jk_entry_changed_cb_list(
      void* data,
      Evas_Object *obj,
      void* event)
{
  PropertyValue* val = data;
  JkPropertyCb* cbs = val->cbs;
  const char* name = evas_object_name_get(obj);
  double v;
  eo_do(obj, v = jk_entry_value_get());
  float f = v;
  memcpy(val->data, &f, sizeof f);

  if (cbs->changed_float) {
    cbs->changed_float(cbs->data, val->path, &v);
  }
}

static void
_jk_entry_changed_end_cb_list(
      void* data,
      Evas_Object *obj,
      void* event)
{
  PropertyValue* val = data;
  JkPropertyCb* cbs = val->cbs;
  const char* name = evas_object_name_get(obj);
  double v;
  eo_do(obj, v = jk_entry_value_get());
  float f = v;
  memcpy(val->data, &f, sizeof f);

  double vs;
  eo_do(obj, vs = jk_entry_value_saved_get());

  if (cbs->register_change_float) {
    cbs->register_change_float(cbs->data, val->path, &vs, &v, 1);
  }
}

Eo* float_new(PropertyValue* val, Eo* obj)
{
  Evas_Object *bx;

  bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);

  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);

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

    free(ss[0]);
    free(ss);
   }

  /*
  Eo* l = elm_layout_add(obj);
  elm_layout_file_set(l, "edc/entry.edj", "main");
  evas_object_size_hint_weight_set(l, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(l, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(l);
   elm_box_pack_end(bx, l);
   return bx;
   */

   //Evas_Object* en = smart_entry_add(evas_object_evas_get(obj));
   //Evas_Object* en = smart_entry_add(obj);
   //chris
   Evas_Object *en = eo_add(JK_ENTRY_CLASS, obj);

  //evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(en);
   elm_box_pack_end(bx, en);

  /*
     Eo* rect = evas_object_rectangle_add(evas_object_evas_get(obj));
  evas_object_show(rect);
  evas_object_color_set(rect, rand() % 255, rand() % 255, rand() % 255, 255/2);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);

   elm_box_pack_end(bx, rect);
   */
  evas_object_smart_callback_add(en, "changed,end", _jk_entry_changed_end_cb_list, val);
  evas_object_smart_callback_add(en, "changed", _jk_entry_changed_cb_list, val);

  const float* f = val->data;
  eo_do(en, jk_entry_value_set(*f));

  evas_object_show(bx);
  return bx;
}


Evas_Object*
gl_content_float_get_test(
      void *data,
      Evas_Object *obj,
      const char *part)
{
  Evas_Object *bx, *bt, *ck;

  if (strcmp(part, "elm.swallow.content") != 0) return NULL;

  bx = elm_box_add(obj);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);

  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);

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

    free(ss[0]);
    free(ss);
   }

  /*
  Eo* l = elm_layout_add(obj);
  elm_layout_file_set(l, "edc/entry.edj", "main");
  evas_object_size_hint_weight_set(l, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(l, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(l);
   elm_box_pack_end(bx, l);
   return bx;
   */

   //Evas_Object* en = smart_entry_add(evas_object_evas_get(obj));
   //Evas_Object* en = smart_entry_add(obj);
   //chris
   Evas_Object *en = eo_add(JK_ENTRY_CLASS, obj);

  //evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(en);
   elm_box_pack_end(bx, en);

  /*
     Eo* rect = evas_object_rectangle_add(evas_object_evas_get(obj));
  evas_object_show(rect);
  evas_object_color_set(rect, rand() % 255, rand() % 255, rand() % 255, 255/2);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);

   elm_box_pack_end(bx, rect);
   */
  evas_object_smart_callback_add(en, "changed,end", _jk_entry_changed_end_cb_list, val);
  evas_object_smart_callback_add(en, "changed", _jk_entry_changed_cb_list, val);

  const float* f = val->data;
  eo_do(en, jk_entry_value_set(*f));

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

  PropertyValue* val = elm_object_item_data_get(glit);
  JkPropertyCb* cbs = data;

  if (cbs->expand) {
    cbs->expand(cbs->data, (void*) val->path, glit);
  }

  elm_genlist_item_update(val->item);
}

static void
gl9_con(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_subitems_clear(glit);

   PropertyValue* val = elm_object_item_data_get(glit);
   char* name = (char*) val->path;
   JkPropertyCb* cbs = data;
   //TODO clear the nodes

   if (cbs->contract) {
     cbs->contract(cbs->data, name, glit);
   }

   elm_genlist_item_update(val->item);
}


static void
_property_value_free_cb(void *data)
{
  PropertyValue* val = data;
  free(val->data);
  free(val);
}

void
_property_node_clear(void* data)
{
  PropertyNode* node = data;
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
  pl->node_first_group = NULL;
}

PropertyValue* property_list_node_add(
      const char* path,
      const char* added_name)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);//s[num-1];
  val->create_child = _node_create;
  if (added_name) {
    val->added_name = strdup(added_name);
  }

  return val;
}

PropertyValue* property_list_single_node_add(
      JkPropertyList* pl,
      PropertyValue* val)
{
  const char* path = val->path;
  PropertyNode* node = _property_list_node_find_parent(pl, path);
  if (!node) {
    printf("%s, could not find a root for %s\n", __FUNCTION__, path);
    return NULL;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_list_node_new();
  eina_hash_add(node->nodes, strdup(s[num-1]), child);

  val->cbs = pl->cbs;
  child->item = elm_genlist_item_append(pl->list, class_node,
                           val,
                           node->item,
                           ELM_GENLIST_ITEM_TREE,
                           NULL,
                           NULL);

  val->item = child->item;

  free(s[0]);
  free(s);

  return val;
}


PropertyValue* property_list_vec_add(
      JkPropertyList* pl,
      const char* path,
      int len
      )
{
  PropertyNode* node = _property_list_node_find_parent(pl, path);
  if (!node) {
    printf("%s, could not find a root for %s\n", __FUNCTION__, path);
    return NULL;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_list_node_new();
  eina_hash_add(node->nodes, strdup(s[num-1]), child);

  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);//s[num-1];
  val->cbs = pl->cbs;
  val->len = len;
  //val->data = strdup(value);
  //val->user_data = possible_values;

  child->item = elm_genlist_item_append(pl->list, class_vec_node,
                           val, //path,//strdup(s[num-1]),
                           node->item, //git/* parent */,
                           ELM_GENLIST_ITEM_TREE,
                           NULL,//gl4_sel/* func */,
                           NULL/* func data */);

  val->item = child->item;

  free(s[0]);
  free(s);

  return val;
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
    node = pl->node;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_list_node_new();
  eina_hash_add(node->nodes, strdup(s[num-1]), child);
  if (!pl->node_first_group) pl->node_first_group = child;

  child->item = elm_genlist_item_append(pl->list, class_group,
                           strdup(s[num-1]),
                           node->item, //git/* parent */,
                           ELM_GENLIST_ITEM_GROUP,
                           NULL, //gl4_sel/* func */,
                           NULL/* func data */);

  //elm_genlist_item_select_mode_set(child->item, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);


  free(s[0]);
  free(s);
}

PropertyValue*
property_list_float_add(
      const char* path,
      float value)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);
  //val->list = pl;
  val->data = calloc(1, sizeof value);
  memcpy(val->data, &value, sizeof value);

  val->create_child = float_new;

  return val;
}

void property_list_float_update(
      PropertyValue* val,
      float value)
{
  memcpy(val->data, &value, sizeof value);
  elm_genlist_item_update(val->item);
}

PropertyValue*
property_list_string_add(
      const char* path,
      const char* value)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);
  val->data = strdup(value);

  val->create_child = entry_new;

  return val;
}

PropertyValue*
property_list_single_item_add(
      JkPropertyList* pl,
      PropertyValue* val)
{
  const char* path = val->path;

  PropertyNode* node = _property_list_node_find_parent(pl, path);
  if (!node) {
    printf("%s, could not find a root\n", __FUNCTION__);
    return NULL;
  }

  val->cbs = pl->cbs;
  val->item = elm_genlist_item_append(pl->list, class_item,
                           val,
                           node->item,
                           ELM_GENLIST_ITEM_NONE,
                           NULL,
                           NULL);

  eina_hash_add(node->leafs, eina_stringshare_add(path), val);

  return val;

}

PropertyValue*
property_list_single_vec_add(
      JkPropertyList* pl,
      PropertyValue* val,
      bool is_node
      )
{
  const char* path = val->path;

  PropertyNode* node = _property_list_node_find_parent(pl, path);
  if (!node) {
    printf("%s, could not find a root\n", __FUNCTION__);
    return NULL;
  }

  val->cbs = pl->cbs;
  val->item = elm_genlist_item_append(pl->list, class_vec,
        val,
        node->item,
        is_node? ELM_GENLIST_ITEM_TREE : ELM_GENLIST_ITEM_NONE,
        NULL,
        NULL);


  if (is_node) {
    unsigned int num;
    char** s = eina_str_split_full(path, "/", 0, &num);
    PropertyNode* child = property_list_node_new();
    eina_hash_add(node->nodes, strdup(s[num-1]), child);

    child->item = val->item;

    free(s[0]);
    free(s);
  }
  else {
    eina_hash_add(node->leafs, eina_stringshare_add(path), val);
  }

  return val;
}

/*
PropertyValue*
property_list_node_vec_add(
      JkPropertyList* pl,
      PropertyValue* val)
{
  PropertyNode* node = _property_list_node_find_parent(pl, path);
  if (!node) {
    printf("%s, could not find a root for %s\n", __FUNCTION__, path);
    return NULL;
  }

  val->item = elm_genlist_item_append(pl->list, class_vec,
                           val,
                           node->item,
                           ELM_GENLIST_ITEM_TREE,
                           NULL,
                           NULL);

  eina_hash_add(node->leafs, eina_stringshare_add(path), val);

  return val;
}
*/



void property_list_string_update(
      PropertyValue* val,
      const char* value)
{
  if (val->data) free(val->data);

  val->data = strdup(value);
  elm_genlist_item_update(val->item);
}

void property_list_vec_update(
      PropertyValue* val,
      int len)
{
  val->len = len;
  elm_genlist_item_update(val->item);
}


void jk_property_list_register_cb(
      JkPropertyList* pl,
      void * data,
      panel_geom_cb move
      )
{
  pl->cbs->data = data;
  pl->move = move;
}

JkPropertyList*
property_list_new(Evas_Object* win)
{
  JkPropertyList* p = calloc(1, sizeof *p);
  p->cbs = calloc(1, sizeof *p->cbs);
  p->win = win;

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
  //elm_genlist_tree_effect_enabled_set(gl, EINA_TRUE);
  evas_object_show(gl);
  //elm_box_pack_end(bx, gl);
  p->root = gl;
  elm_genlist_focus_on_selection_set(gl, EINA_FALSE);
  //elm_config_focus_autoscroll_mode_set(ELM_FOCUS_AUTOSCROLL_MODE_NONE);
  //elm_config_focus_autoscroll_mode_set(ELM_FOCUS_AUTOSCROLL_MODE_SHOW);
  elm_config_focus_autoscroll_mode_set(ELM_FOCUS_AUTOSCROLL_MODE_BRING_IN);

  class_item = elm_genlist_item_class_new();
  class_item->item_style = "full";//"default";
  class_item->func.text_get = NULL;
  class_item->func.content_get = gl_content_item_get;
  class_item->func.state_get = gl_state_get;
  class_item->func.del = NULL;

  class_vec = elm_genlist_item_class_new();
  class_vec->item_style = "full";//"default";
  class_vec->func.text_get = NULL;
  class_vec->func.content_get = gl_content_vec_get;
  class_vec->func.state_get = gl_state_get;
  class_vec->func.del = NULL;

  class_vec_node = elm_genlist_item_class_new();
  class_vec_node->item_style = "full";//"default";
  class_vec_node->func.text_get = NULL;//gl_text_get_node;
  class_vec_node->func.content_get = gl_content_vec_node_get;// NULL;
  class_vec_node->func.state_get = gl_state_get;
  class_vec_node->func.del = NULL;

  class_group = elm_genlist_item_class_new();
  class_group->item_style = "group_index";
  class_group->func.text_get = gl_text_get_group;
  class_group->func.content_get = NULL;
  class_group->func.state_get = NULL;
  class_group->func.del = NULL;

  class_node = elm_genlist_item_class_new();
  class_node->item_style = "full";//"default";
  class_node->func.text_get = NULL;//gl_text_get_node;
  class_node->func.content_get = gl_content_node_get2;// NULL;
  class_node->func.state_get = gl_state_get;
  class_node->func.del = NULL;

  class_enum = elm_genlist_item_class_new();
  class_enum->item_style = "full";//"default";
  class_enum->func.text_get = NULL;//gl_text_get_node;
  class_enum->func.content_get = gl_content_enum_get2;
  class_enum->func.state_get = gl_state_get;
  class_enum->func.del = NULL;

  class_option = elm_genlist_item_class_new();
  class_option->item_style = "full";//"default";
  class_option->func.text_get = NULL;//gl_text_get_node;
  class_option->func.content_get = gl_content_option_get;
  class_option->func.state_get = gl_state_get;
  class_option->func.del = NULL;

  //elm_genlist_item_class_free(class_group);
  //elm_genlist_item_class_free(class_node);

  evas_object_smart_callback_add(gl, "expand,request", gl9_exp_req, NULL);
  evas_object_smart_callback_add(gl, "contract,request", gl9_con_req, NULL);
  evas_object_smart_callback_add(gl, "expanded", gl9_exp, p->cbs);
  evas_object_smart_callback_add(gl, "contracted", gl9_con, p->cbs);

  p->list = gl;

  p->node = property_list_node_new();

  return p;
}

PropertyValue* property_list_enum_add(
      //const char* path,
      //const char* added_name)
      const char* path,
      char* possible_values,
      const char* value)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);//s[num-1];
  val->data = strdup(value);
  val->user_data = strdup(possible_values);
  val->create_child = _enum_create;

  //eina_hash_add(node->leafs, eina_stringshare_add(path), val);

  return val;
}

void property_list_enum_update(
      PropertyValue* val,
      const char* value)
{
  if (!strcmp(value, val->data)) {
    return;
  }

  if (val->data) free(val->data);

  bool was_expanded =
   elm_genlist_item_type_get(val->item) == ELM_GENLIST_ITEM_TREE &&
   elm_genlist_item_expanded_get(val->item);

  if (was_expanded) {
    elm_genlist_item_expanded_set(val->item, EINA_FALSE);
    elm_genlist_item_subitems_clear(val->item);
  }

  val->data = strdup(value);
  elm_genlist_item_update(val->item);

  if (was_expanded) {
    elm_genlist_item_expanded_set(val->item, EINA_TRUE);
  }
}

PropertyValue*
property_list_option_add(
      JkPropertyList* pl,
      const char* path,
      const char* value)
{
  PropertyNode* node = _property_list_node_find_parent(pl, path);
  if (!node) {
    printf("%s, could not find a root\n", __FUNCTION__);
    return NULL;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);

  PropertyNode* child = property_list_node_new();
  eina_hash_add(node->nodes, strdup(s[num-1]), child);

  Elm_Genlist_Item_Type t;
  if (!strcmp(value, "Some")) {
    t = ELM_GENLIST_ITEM_TREE;
  }
  else {
    t = ELM_GENLIST_ITEM_NONE;
  }

  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);//s[num-1];
  val->cbs = pl->cbs;
  val->data = strdup(value);

  val->item = elm_genlist_item_append(pl->list, class_option,
                           val,
                           node->item,
                           t,
                           NULL,
                           NULL);

  child ->item = val->item;

  eina_hash_add(node->leafs, eina_stringshare_add(path), val);

  free(s[0]);
  free(s);

  return val;
}

void property_list_option_update(
      PropertyValue* val,
      const char* value)
{
  Elm_Genlist_Item_Type t;
  if (!strcmp(value, "Some")) {
    t = ELM_GENLIST_ITEM_TREE;
  }
  else {
    t = ELM_GENLIST_ITEM_NONE;
  }

  _update_option_item(val, t);
}

void
property_expand(PropertyValue* val)
{
    elm_genlist_item_expanded_set(val->item, EINA_FALSE);
    elm_genlist_item_expanded_set(val->item, EINA_TRUE);
}

void property_show(
      JkPropertyList* p,
      bool b)
{
  object_show(p->win, b);
}

static void _on_panel_geom(
      void *data,
      Evas *evas,
      Evas_Object *o,
      void *einfo)
{
  JkPropertyList* p = data;
  if (p->move) {
    int x, y, w, h;
    evas_object_geometry_get(o, &x, &y, &w, &h);
    p->move(p->cbs->data, x , y, w, h);
  }
}

JkPropertyList* jk_property_list_new(Window* w, int x, int y, int width, int height)
{
  /*
  JkPropertyList* pl = property_list_new(w->win);
  edje_object_part_swallow(w->edje, "part_property_test", pl->root);
  return pl;
  */

    /*
  Evas_Object* win = elm_win_add(w->win, "property", ELM_WIN_BASIC);
  elm_win_title_set(win, "property");

  Evas_Object* bg = elm_bg_add(win);
  evas_object_show(bg);
  evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, bg);

  JkPropertyList* p = property_list_new(win);
  evas_object_size_hint_weight_set(p->root, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, p->root);
  evas_object_resize(win, 256, 256);
  evas_object_show(win);

  */

  //Evas* e = evas_object_evas_get(w->win);
  //Evas_Object* panel = smart_panel_add(e);
  Evas_Object* panel = jk_property_panel_new(w,x,y,width,height);

  JkPropertyList* p = property_list_new(panel);
  evas_object_size_hint_weight_set(p->root, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //smart_panel_content_set(panel, p->root);
  elm_object_part_content_set(panel, "content", p->root);
  p->win = panel;

  evas_object_event_callback_add(panel, EVAS_CALLBACK_MOVE, _on_panel_geom, p);
  evas_object_event_callback_add(panel, EVAS_CALLBACK_RESIZE, _on_panel_geom, p);

  return p;

}

JkPropertyCb* property_list_cb_get(JkPropertyList* p)
{
  return p->cbs;
}

