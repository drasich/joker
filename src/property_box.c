#include "property.h"
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "panel.h"

static PropertyNode*
_property_box_node_new()
{
  PropertyNode* node = calloc(1, sizeof *node);
  node->leafs = eina_hash_string_superfast_new(NULL);
  node->nodes = eina_hash_string_superfast_new(NULL);

  return node;
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

  p->node = _property_box_node_new();
  p->win = win;

  return p;
}

JkPropertyBox*
jk_property_box_new(Evas_Object* panel)
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

JkPropertyCb*
property_box_cb_get(JkPropertyBox* p)
{
  return p->cbs;
}

PropertyValue*
property_box_single_item_add(
      JkPropertyBox* pb,
      void* node,
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
  val->node = node;

  Eo* pbx = pb->box;
  if (parent) {
    if (!parent->child) {

      pbx = parent->eo;

      Eo* bx_child_container = elm_box_add(pbx);
      elm_box_horizontal_set(bx_child_container, EINA_TRUE);
      evas_object_size_hint_weight_set(bx_child_container, EVAS_HINT_EXPAND, 0.0);
      evas_object_size_hint_align_set(bx_child_container, EVAS_HINT_FILL, EVAS_HINT_FILL);
      //elm_box_align_set(bx_child, 0, 0.5);
      evas_object_show(bx_child_container);
      elm_box_pack_end(pbx, bx_child_container);

      Eo* empty = elm_label_add(pbx);
      evas_object_show(empty);
      elm_object_text_set(empty, "    ");
      elm_box_pack_end(bx_child_container, empty);

      Eo* bx_child = elm_box_add(pbx);
      elm_box_horizontal_set(bx_child, EINA_FALSE);
      evas_object_size_hint_weight_set(bx_child, EVAS_HINT_EXPAND, 0.0);
      evas_object_size_hint_align_set(bx_child, EVAS_HINT_FILL, EVAS_HINT_FILL);
      //elm_box_align_set(bx_child, 0, 0.5);
      evas_object_show(bx_child);
      //elm_box_pack_end(pbx, bx_child);
      elm_box_pack_end(bx_child_container, bx_child);

      parent->child = bx_child;
    }

      pbx = parent->child;
  }

  Eo* bxeo = elm_box_add(pbx);
  evas_object_show(bxeo);
  elm_box_horizontal_set(bxeo, EINA_FALSE);
  evas_object_size_hint_weight_set(bxeo, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bxeo, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx, 0, 0.5);
  elm_box_pack_end(pbx,bxeo);


  Eo* bx = elm_box_add(pbx);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_align_set(bx, 0, 0.5);

  /*
  if (parent) {
    Eo* empty = elm_label_add(pbx);
    evas_object_show(empty);
    elm_object_text_set(empty, "    ");
    elm_box_pack_end(bx, empty);
  }
  */

  //Evas_Coord fw = -1, fh = -1;
  //elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  //evas_object_size_hint_min_set(bx, 0, fh);
  
  //TODO
  Eo* name = elm_label_add(bx);

  unsigned int num;
  char** ss = eina_str_split_full(val->path, "/", 0, &num);
  char s[256];

  if (val->style == NODE || val->style == VEC) {
  sprintf(s, "<b> %s </b>  ", ss[num-1]);
  }
  else {
    sprintf(s, " %s   ", ss[num-1]);
  }

  elm_object_text_set(name, s);
  elm_box_pack_end(bx, name);
  evas_object_show(name);

  elm_box_pack_end(bx, val->create_child(val, pb->box));

  val->eo = bxeo;
  elm_box_pack_end(bxeo, bx);

  /*
  Eo* bx_child = elm_box_add(pbx);
  elm_box_horizontal_set(bx_child, EINA_FALSE);
  evas_object_size_hint_weight_set(bx_child, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx_child, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx_child, 0, 0.5);
  val->child = bx_child;
  evas_object_show(bx_child);
  elm_box_pack_end(pbx, bx_child);
  */

  return val;

}

PropertyValue* property_vec_new(
      const char* path,
      int len
      )
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);
  val->len = len;
  val->create_child = vec_new;
  val->style = VEC;

  return val;
}

void property_box_vec_update(
		JkPropertyBox* box,
      PropertyValue* val,
      int len)
{
  if (val->len == len) {
    // len did not change so return
    return;
  }

  val->len = len;
  vec_update_len(val);
}

static Eo* _box_child_get(Eo* box, int index)
{
  Eina_List* list = elm_box_children_get(box);
  Eo* obj = eina_list_nth(list, index);
  eina_list_free(list);
  return obj;
}

PropertyValue*
property_box_vec_item_add(
      JkPropertyBox* pb,
      void* cb_data,
      PropertyValue* val,
      PropertyValue* parent,
      int index
      )
{
  const char* path = val->path;

  val->cbs = pb->cbs;
  val->node = cb_data;

  Eo* pbx = pb->box;
  if (parent) {
    if (index > 0)
    parent->children = eina_list_append_relative_list(parent->children, val, eina_list_nth_list(parent->children, index -1));
    else
    parent->children = eina_list_prepend(parent->children, val);

    if (!parent->child) {

      pbx = parent->eo;

      Eo* bx_child_container = elm_box_add(pbx);
      elm_box_horizontal_set(bx_child_container, EINA_TRUE);
      evas_object_size_hint_weight_set(bx_child_container, EVAS_HINT_EXPAND, 0.0);
      evas_object_size_hint_align_set(bx_child_container, EVAS_HINT_FILL, EVAS_HINT_FILL);
      //elm_box_align_set(bx_child, 0, 0.5);
      evas_object_show(bx_child_container);
      elm_box_pack_end(pbx, bx_child_container);

      Eo* empty = elm_label_add(pbx);
      evas_object_show(empty);
      elm_object_text_set(empty, "    ");
      elm_box_pack_end(bx_child_container, empty);

      Eo* bx_child = elm_box_add(pbx);
      elm_box_horizontal_set(bx_child, EINA_FALSE);
      evas_object_size_hint_weight_set(bx_child, EVAS_HINT_EXPAND, 0.0);
      evas_object_size_hint_align_set(bx_child, EVAS_HINT_FILL, EVAS_HINT_FILL);
      //elm_box_align_set(bx_child, 0, 0.5);
      evas_object_show(bx_child);
      //elm_box_pack_end(pbx, bx_child);
      elm_box_pack_end(bx_child_container, bx_child);

      parent->child = bx_child;
    }

      pbx = parent->child;
  }

  Eo* bxeo = elm_box_add(pbx);
  evas_object_show(bxeo);
  elm_box_horizontal_set(bxeo, EINA_FALSE);
  evas_object_size_hint_weight_set(bxeo, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bxeo, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx, 0, 0.5);

  Eo* beforethis = _box_child_get(pbx, index);
  if (beforethis) 
  elm_box_pack_before(pbx, bxeo, beforethis);
  else
  elm_box_pack_end(pbx,bxeo);


  Eo* bx = elm_box_add(bxeo);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_TRUE);
  elm_box_padding_set(bx, 4, 0);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_align_set(bx, 0, 0.5);

  /*
  if (parent) {
    Eo* empty = elm_label_add(pbx);
    evas_object_show(empty);
    elm_object_text_set(empty, "    ");
    elm_box_pack_end(bx, empty);
  }
  */


  //Evas_Coord fw = -1, fh = -1;
  //elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  //evas_object_size_hint_min_set(bx, 0, fh);
  
  char index_str[256];
  sprintf(index_str, "%d  ", index);

  Eo* name = elm_label_add(bx);
  val->name = name;
  elm_object_text_set(name, index_str);
  elm_box_pack_end(bx, name);
  evas_object_show(name);

  elm_box_pack_end(bx, val->create_child(val, pb->box));
  
  val->eo = bxeo;
  elm_box_pack_end(bxeo, bx);


  Eo* bt = elm_button_add(bx);
  elm_object_text_set(bt, "+");
  evas_object_show(bt);
  elm_box_pack_end(bx, bt);
  struct _BtCb *btcb = calloc(1, sizeof *btcb);
  btcb->cb = val->cbs->vec_add;
  btcb->data = val;
  btcb->data2 = cb_data;
  btn_cb_set(bt, _bt_cb_box, btcb);

  bt = elm_button_add(bx);
  elm_object_text_set(bt, "-");
  evas_object_show(bt);
  elm_box_pack_end(bx, bt);
  btcb = calloc(1, sizeof *btcb);
  btcb->cb = val->cbs->vec_del;
  btcb->data = val;
  btcb->data2 = cb_data;
  btn_cb_set(bt, _bt_cb_box, btcb);

  /*
  Eo* bx_child = elm_box_add(pbx);
  evas_object_show(bx_child);
  elm_box_horizontal_set(bx_child, EINA_FALSE);
  evas_object_size_hint_weight_set(bx_child, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx_child, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx_child, 0, 0.5);
  val->child = bx_child;
  elm_box_pack_end(pbx, bx_child);
  */



  Eina_List* list;
  PropertyValue* child_val;

  EINA_LIST_FOREACH(parent->children, list, child_val)
  {
  	const char* t = elm_object_text_get(child_val->name);
  }


  int i = index + 1;
  Eina_List* start = eina_list_nth_list(parent->children, i);
  //EINA_LIST_FOREACH(start, list, child_val)
  for(list = start; list; list = eina_list_next(list))
  {
  	sprintf(index_str, "%d  ", i++);
	child_val = eina_list_data_get(list);
  	elm_object_text_set(child_val->name, index_str);
  }

  return val;
}

void
property_box_vec_item_del(
      JkPropertyBox* pb,
      PropertyValue* parent,
      int index
      )
{
  Eina_List* children = elm_box_children_get(parent->child);
  Eo* item = eina_list_nth(children, index);
  eina_list_free(children);
  elm_box_unpack(parent->child, item);


  parent->children = eina_list_remove(parent->children,
      eina_list_nth(parent->children, index));

  evas_object_del(item);

  Eina_List* list;
  PropertyValue* child_val;
  int i = index;
  Eina_List* start = eina_list_nth_list(parent->children, i);
  //EINA_LIST_FOREACH(start, list, child_val)
  char index_str[256];
  for(list = start; list; list = eina_list_next(list))
  {
  	sprintf(index_str, "%d  ", i++);
	child_val = eina_list_data_get(list);
  	elm_object_text_set(child_val->name, index_str);
  }
}

