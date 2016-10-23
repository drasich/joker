#include "property.h"

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
    cbs->register_change_enum(cbs->data, val->node, old, txt, 1);
  }

  if ( elm_genlist_item_type_get(val->item) == ELM_GENLIST_ITEM_TREE &&
        elm_genlist_item_expanded_get(val->item)) {
    //because tree anim takes time we have to do this
    elm_genlist_item_subitems_clear(val->item);
    elm_genlist_item_expanded_set(val->item, EINA_FALSE);
    elm_genlist_item_expanded_set(val->item, EINA_TRUE);
  }
}


Eo* _enum_create(PropertyValue* val, Evas_Object* obj)
{
  Eo* bx_root = elm_box_add(obj);
  elm_box_horizontal_set(bx_root, EINA_FALSE);
  evas_object_size_hint_weight_set(bx_root, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx_root, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_align_set(bx_root, 0, 0.5);
  evas_object_show(bx_root);


  Eo* bx = elm_box_add(obj);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_TRUE);
  Evas_Coord fw = -1, fh = -1;
  elm_coords_finger_size_adjust(1, &fw, 1, &fh);
  evas_object_size_hint_min_set(bx, 0, fh);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_align_set(bx, 0, 0.5);
  //elm_box_align_set(bx, 0, 0.5f);
  elm_box_padding_set(bx, 4, 0);

  Evas_Object* label = elm_label_add(bx);

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
  val->item_eo = hoversel;
   }

  elm_box_pack_end(bx_root, bx);

  /*
  Eo* bx_child = elm_box_add(obj);
  elm_box_horizontal_set(bx_child, EINA_FALSE);
  evas_object_size_hint_weight_set(bx_child, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(bx_child, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //elm_box_align_set(bx_child, 0, 0.5);
  val->child = bx_child;
  evas_object_show(bx_child);
  elm_box_pack_end(bx_root, bx_child);
  */


   return bx_root;
}


PropertyValue* property_enum_new(
      const char* path,
      char* possible_values,
      const char* value)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);//s[num-1];
  val->data = strdup(value);
  val->user_data = strdup(possible_values);
  val->create_child = _enum_create;
  val->style = NODE;

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

void property_box_enum_update(
      JkPropertyBox* pb,
      PropertyValue* val,
      const char* value)
{
  if (!strcmp(value, val->data)) {
    // values are same so return
    return;
  }

  if (val->data) free(val->data);

  elm_box_clear(val->child);
  elm_object_text_set(val->item_eo, value);

  val->data = strdup(value);
}

