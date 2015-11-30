#include "common.h"

void object_show(Evas_Object* o, bool b)
{
  if (b) {
    evas_object_show(o);
  }
  else {
    evas_object_hide(o);
  }
}

static void
_button_callback(
      void *data,
      Evas_Object *obj,
      void *event_info)
{
  ButtonCallbackData* bcd = data;
  bcd->fn(bcd->data);
}


static void _free_data(void *data, Evas* e, Evas_Object* o, void* event_info)
{
  free(data);
}

void btn_cb_set(
      Eo* bt,
      button_callback fn,
      void* data)
{
  ButtonCallbackData* bcd = calloc(1, sizeof *bcd);
  bcd->data = data;
  bcd->fn = fn;
  evas_object_smart_callback_add(bt, "clicked", _button_callback, bcd);
  evas_object_event_callback_add(bt, EVAS_CALLBACK_FREE, _free_data, bcd);
}

