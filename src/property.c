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
      void* data,
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
  cb->data = data;

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

  /*
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
  */
  //evas_object_show(label);
  evas_object_show(bx);
  //evas_object_show(bx_label);

  //free(ss[0]);
  //free(ss);
  return bx;
}

PropertyValue* property_node_new(const char* path)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);
  val->create_child = _node_create;
  val->style = NODE;

  return val;
}

void _bt_cb(void* data)
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

void _bt_cb_box(void* data)
{
  struct _BtCb *btcb = data;
  PropertyValue* val = btcb->data;
  printf("val  :%p \n", val);
  printf("val cbs :%p \n", val->cbs);
  printf("val cbs data :%p \n", val->cbs->data);
  printf("val cbs node :%p \n", val->node);
  printf("val cbs node, NO btcb data2 :%p \n", btcb->data2);
  btcb->cb(
       val->cbs->data,
        val->node, 
        //btcb->data2,
        NULL,
        NULL,
        0);

  printf("TODO  update  VEC LEN\n");
}


void vec_update_len(PropertyValue* val)
{
  Eo* label = val->item_eo;
  //unsigned int num;
  //char** ss = eina_str_split_full(val->path, "/", 0, &num);
  //const char* name = ss[num-1];

  char s[256];
  //sprintf(s, "<b>%s</b>, len : %d", name, val->len);
  sprintf(s, "| len : %d", val->len);
  //if (val->item && elm_genlist_item_expanded_get(val->item))
  //sprintf(s, "%s : ", name);
  //else
  //sprintf(s, "%s", name);

  elm_object_text_set(label, s);

  //free(ss[0]);
  //free(ss);
}

Eo* vec_new(PropertyValue* val, Eo* obj)
{
  Eo* bx = elm_box_add(obj);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_FALSE);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx, 0, 0.5);

  Eo* bxh = elm_box_add(obj);
  evas_object_show(bxh);
  elm_box_horizontal_set(bxh, EINA_TRUE);
  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bxh, 0, fh);
  elm_box_align_set(bxh, 0, 1);
  //elm_box_align_set(bxh, 0, 0.5f);
  elm_box_padding_set(bxh, 4, 0);
  evas_object_size_hint_weight_set(bxh, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bxh, EVAS_HINT_FILL, EVAS_HINT_FILL);

  Evas_Object* label = elm_label_add(bxh);
  elm_box_pack_end(bxh, label);
  evas_object_show(label);
  val->item_eo = label;
  vec_update_len(val);

  Eo* bt = elm_button_add(obj);
  elm_object_text_set(bt, "+");
  evas_object_show(bt);
  elm_box_pack_end(bxh, bt);
  struct _BtCb *btcb = calloc(1, sizeof *btcb);
  btcb->cb = val->cbs->vec_add;
  btcb->data = val;
  btn_cb_set(bt, _bt_cb_box, btcb);

  elm_box_pack_end(bx, bxh);

  return bx;
}

