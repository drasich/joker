#include "property.h"
#include <string.h>
#include <stdbool.h>
#include "common.h"
//#include "entry.h"
#include "entry/jk_entry.eo.h"
#include "panel.h"

static void
_spinner_changed_cb(void* data, Evas_Object *obj, void* event)
{
  JkPropertyCb* cbs = data;
  const char* name = evas_object_name_get(obj);
  double v =  elm_spinner_value_get(obj);
  if (cbs->changed_float) {
    cbs->changed_float(cbs->data, name, &v);
  }
}


static void
_entry_changed_cb_ps(void *data, Evas_Object *obj, void *event)
{
  const char* s = elm_object_text_get(obj);
  JkPropertyCb* cbs = data;

  const char* name = evas_object_name_get(obj);
  if (cbs->changed_string) {
    cbs->changed_string(cbs->data, name, s);
  }
}


JkPropertyBox*
property_box_new(Evas_Object* win)
{
  JkPropertyBox* p = calloc(1, sizeof *p);
  p->cbs = calloc(1, sizeof *p->cbs);

  /*
  Eo* bg = elm_bg_add(win);
  evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(bg);
  */

  Eo* bx = elm_box_add(win);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_align_set(bx, 0.5, 0);
  //elm_box_homogeneous_set(bx, EINA_TRUE);
  elm_box_horizontal_set(bx, EINA_FALSE);
  evas_object_show(bx);
  p->box = bx;

  Eo* scroller = elm_scroller_add(win);
  evas_object_size_hint_weight_set(scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_object_content_set(scroller, bx);
  p->root = scroller;

  p->node = property_box_node_new();
  p->win = win;

  return p;
}

PropertyNode* property_box_node_new()
{
  PropertyNode* node = calloc(1, sizeof *node);
  node->leafs = eina_hash_string_superfast_new(NULL);
  node->nodes = eina_hash_string_superfast_new(NULL);

  return node;
}

PropertyNode* _property_node_find(
      PropertyNode* node,
      const char* path)
{
  char** s = eina_str_split(path, "/", 0);

  int i = 0;
  while (s[i]) {

    if (s[i+1]) {
      PropertyNode* next = eina_hash_find(node->nodes, s[i]);
      if (next) {
        node = next;
        i++;
      }
      else {
        //eina_hash_foreach(node->nodes,_nodes_print, NULL);
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


static PropertyNode* _property_box_node_find(
      JkPropertyBox* ps,
      const char* path)
{
  return _property_node_find(ps->node, path);
}


Evas_Object* _property_leaf_find(
      JkPropertyBox* ps,
      const char* path)
{
  PropertyNode* node = _property_box_node_find(ps, path);

  if (node) {
    return eina_hash_find(node->leafs, path);
  }

  return NULL;
}

void
property_box_string_add(
      JkPropertyBox* ps,
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

  PropertyNode* node = _property_box_node_find(ps, name);
  eina_hash_add(node->leafs, eina_stringshare_add(name), en);
}

void
property_box_float_add(
      JkPropertyBox* ps, 
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

  PropertyNode* node = _property_box_node_find(ps, name);
  eina_hash_add(node->leafs, eina_stringshare_add(name), sp);

  evas_object_smart_callback_add(sp, "changed", _spinner_changed_cb, ps );
}

void property_box_string_update(
      JkPropertyBox* set,
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

void property_box_float_update(JkPropertyBox* set, const char* path, float value)
{
  Evas_Object* o = _property_leaf_find(set, path);

  if (o) {
    elm_spinner_value_set(o, value);
  }
  else {
    printf("could not find float property with path '%s'\n", path);
  }

}

void property_box_node_add(
      JkPropertyBox* ps, 
      const char* path)
{
  PropertyNode* node = _property_box_node_find(ps, path);
  if (!node) {
    printf("$s, could not find a root\n", __FUNCTION__);
    return;
  }

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_box_node_new();
  eina_hash_add(node->nodes, s[num-1], child);
  
  Evas_Object* label = elm_label_add(ps->box);
  char ls[256];
  sprintf(ls, "<b> %s </b> : ", s[num-1]);

  elm_object_text_set(label, ls);
  evas_object_show(label);
  elm_box_pack_end(ps->box, label);
  evas_object_show(label);
}

/*
JkPropertySet* jk_property_set_new(Window* w)
{
  JkPropertySet* ps = property_set_new(w->win);
  //edje_object_part_swallow(w->edje, "part_property_test", ps->root);
  return ps;
}
*/

static void _on_panel_geom(
      void *data,
      Evas *evas,
      Evas_Object *o,
      void *einfo)
{
  JkPropertyBox* p = data;
  if (p->move) {
    int x, y, w, h;
    evas_object_geometry_get(o, &x, &y, &w, &h);
    p->move(p->cbs->data, x , y, w, h);
  }
}


JkPropertyBox* jk_property_box_new(Evas_Object* panel)
{
  JkPropertyBox* p = property_box_new(panel);
  elm_object_part_content_set(panel, "content", p->root);

  return p;
}

void
property_box_clear(JkPropertyBox* pl)
{
  elm_box_clear(pl->box);
  _property_node_clear(pl->node);
  pl->node_first_group = NULL;
}

void jk_property_box_register_cb(
      JkPropertyBox* p,
      void * data,
      panel_geom_cb move
      )
{
  p->cbs->data = data;
  p->move = move;
}

JkPropertyCb* property_box_cb_get(JkPropertyBox* p)
{
  return p->cbs;
}

PropertyValue*
property_box_single_item_add(
      JkPropertyBox* pb,
      PropertyValue* val,
      PropertyValue* parent
      )
{
  const char* path = val->path;

  /*
  PropertyNode* node = _property_list_node_find_parent(pl, path);
  if (!node) {
    printf("%s, could not find a root\n", __FUNCTION__);
    return NULL;
  }
  */

  //PropertyNode* node = pb->node;

  val->cbs = pb->cbs;

  Eo* pbx = pb->box;
  if (parent) {
    printf("there is a parent, and child is : %p \n", parent->child);
    pbx = parent->child;
  }

  Eo* bx = elm_box_add(pbx);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_align_set(bx, 0, 0.5);

  //Evas_Coord fw = -1, fh = -1;
  //elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  //evas_object_size_hint_min_set(bx, 0, fh);

  elm_box_pack_end(bx, val->create_child(val, pbx));

  val->eo = bx;
  printf("valeo box : %p\n", bx);
  elm_box_pack_end(pbx, bx);

  return val;

}

PropertyValue* property_box_single_node_add(
      JkPropertyBox* pb,
      PropertyValue* val)
{
  const char* path = val->path;
  /*
  PropertyNode* node = _property_list_node_find_parent(pl, path);
  if (!node) {
    printf("%s, could not find a root for %s\n", __FUNCTION__, path);
    return NULL;
  }
  */

  PropertyNode *node = pb->node;

  unsigned int num;
  char** s = eina_str_split_full(path, "/", 0, &num);
  PropertyNode* child = property_list_node_new();
  eina_hash_add(node->nodes, strdup(s[num-1]), child);

  val->cbs = pb->cbs;
  free(s[0]);
  free(s);


  Eo* bx = elm_box_add(pb->box);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);

  elm_box_align_set(bx, 0, 0.5f);

  if (val->create_child) {
    elm_box_pack_end(bx, val->create_child(val, pb->root));
  }
  else {
    Evas_Object* label = _node_create(val, bx);
    evas_object_show(label);
    elm_box_pack_end(bx, label);
  }

  val->eo = bx;
  elm_box_pack_end(pb->box, bx);

  return val;
}

void property_box_remove(
      JkPropertyBox* pb,
      PropertyValue* val)
{
  printf("dance !!!!!!!!!!!!!!! %p \n", val->eo);
  elm_box_unpack(pb->box, val->eo);
  evas_object_del(val->eo);
}

void property_box_add(
      JkPropertyBox* pb,
      PropertyValue* val)
{
}


void property_box_enum_update(
      JkPropertyBox* pb,
      PropertyValue* val,
      const char* value)
{
  if (!strcmp(value, val->data)) {
    printf("value are same so return : %s = %s \n", value, val->data);
    return;
  }

  if (val->data) free(val->data);

  printf("CCCCCCCCCCCCCCCCCCCCc :: %p %s \n", val->item_eo, value);
  elm_box_clear(val->child);
  elm_object_text_set(val->item_eo, value);

  //TODO clear items

  val->data = strdup(value);

  //TODO add items
}

PropertyValue* property_vec_add(
      const char* path,
      int len
      )
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);
  val->len = len;
  val->create_child = vec_new;

  return val;
}

PropertyValue*
property_box_vec_item_add(
      JkPropertyBox* pb,
      PropertyValue* val,
      PropertyValue* parent
      )
{
  const char* path = val->path;

  val->cbs = pb->cbs;

  Eo* pbx = pb->box;
  if (parent) {
    printf("vec item add : there is a parent, and child is : %p \n", parent->child);
    pbx = parent->child;
  }

  Eo* bx = elm_box_add(pbx);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_align_set(bx, 0, 0.5);

  //Evas_Coord fw = -1, fh = -1;
  //elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  //evas_object_size_hint_min_set(bx, 0, fh);

  elm_box_pack_end(bx, val->create_child(val, pbx));

  val->eo = bx;
  printf("valeo box : %p\n", bx);
  elm_box_pack_end(pbx, bx);


  Eo* bt = elm_button_add(pbx);
  elm_object_text_set(bt, "+");
  evas_object_show(bt);
  elm_box_pack_end(bx, bt);
  struct _BtCb *btcb = calloc(1, sizeof *btcb);
  btcb->cb = val->cbs->vec_add;
  btcb->data = val;
  btn_cb_set(bt, _bt_cb, btcb);

  bt = elm_button_add(pbx);
  elm_object_text_set(bt, "-");
  evas_object_show(bt);
  elm_box_pack_end(bx, bt);
  btcb = calloc(1, sizeof *btcb);
  btcb->cb = val->cbs->vec_del;
  btcb->data = val;
  btn_cb_set(bt, _bt_cb, btcb);

  Eo* bx_child = elm_box_add(pbx);
  evas_object_show(bx_child);
  elm_box_horizontal_set(bx_child, EINA_FALSE);
  evas_object_size_hint_weight_set(bx_child, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx_child, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx_child, 0, 0.5);
  val->child = bx_child;

  elm_box_pack_end(pbx, bx_child);

  return val;

}

void property_box_children_clear(PropertyValue* val)
{
  printf("TODO clear the PropertyValue\n");
  elm_box_clear(val->child);
}
