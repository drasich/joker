#include "property.h"

static void
_entry_changed_cb_list(
      void* data,
      Evas_Object *obj,
      void* event)
{
  PropertyValue* val = data;
  JkPropertyCb* cbs = val->cbs;
  const char* value = elm_object_text_get(obj);

  if (cbs->register_change_string) {
    cbs->register_change_string(cbs->data, val->node, NULL, value, 0);
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
    cbs->register_change_string(cbs->data, val->node, old, value, 1);
  }
}

Eo*
entry_new(PropertyValue* val, Eo* obj)
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
  val->item_eo = en;

  //evas_object_smart_callback_add(en, "unfocused", _entry_unfocused_cb, cp);
  //TODO
  /*
  evas_object_smart_callback_add(en, "aborted", _entry_aborted_cb, cp);
  evas_object_smart_callback_add(en, "clicked", _entry_clicked_cb, cp);
  */

   return bx;
}


PropertyValue*
property_string_new(
      const char* path,
      const char* value)
{
  PropertyValue *val = calloc(1, sizeof *val);
  val->path = strdup(path);
  val->data = strdup(value);

  val->create_child = entry_new;
  val->style = VALUE;

  return val;
}

void
property_string_update(
      PropertyValue* val,
      const char* value)
{
  if (val->data) free(val->data);

  val->data = strdup(value);
  elm_genlist_item_update(val->item);
  elm_object_text_set(val->item_eo, value);
}

