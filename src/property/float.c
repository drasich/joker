#include "property.h"
#include "entry/jk_entry.h"
#include "entry/jk_entry.eo.legacy.h"

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
  //eo_do(obj, v = jk_entry_value_get());
  v = jk_entry_value_get(obj);
  float f = v;
  memcpy(val->data, &f, sizeof f);

  if (cbs->changed_float) {
    printf("CHANGED FLOAT : %p \n", val->node);
    cbs->changed_float(cbs->data, val->node, &v);
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
  //eo_do(obj, v = jk_entry_value_get());
  v = jk_entry_value_get(obj);
  float f = v;
  memcpy(val->data, &f, sizeof f);

  double vs;
  //eo_do(obj, vs = jk_entry_value_saved_get());
  vs = jk_entry_value_saved_get(obj);

  if (cbs->register_change_float) {
    cbs->register_change_float(cbs->data, val->node, &vs, &v, 1);
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
   printf("parent obj : %p \n", obj);
   //Evas_Object *en = eo_add(JK_ENTRY_CLASS, obj);
   Evas_Object *en = jk_entry_add(obj);

  //evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
  evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(en);
   elm_box_pack_end(bx, en);

     //Eo* rect = evas_object_rectangle_add(evas_object_evas_get(obj));
  //evas_object_show(rect);
  //evas_object_color_set(rect, rand() % 255, rand() % 255, rand() % 255, 255/2);
  //evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
//
   //elm_box_pack_end(bx, rect);

   printf("en : %p \n", en);
  evas_object_smart_callback_add(en, "changed,end", _jk_entry_changed_end_cb_list, val);
  evas_object_smart_callback_add(en, "changed", _jk_entry_changed_cb_list, val);

  const float* f = val->data;
  //eo_do(en, jk_entry_value_set(*f));
  jk_entry_value_set(en, *f);
  val->item_eo = en;

  evas_object_show(bx);
  return bx;
}


PropertyValue*
property_float_new(
      const char* path,
      float value)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);
  //val->list = pl;
  val->data = calloc(1, sizeof value);
  memcpy(val->data, &value, sizeof value);

  printf("adding float with %s \n", path);

  val->create_child = float_new;
  val->style = VALUE;

  return val;
}

void property_float_update(
      PropertyValue* val,
      float value)
{
  memcpy(val->data, &value, sizeof value);
  elm_genlist_item_update(val->item);
  //eo_do(val->item_eo, jk_entry_value_set(value));
  jk_entry_value_set(val->item_eo, value);
}

