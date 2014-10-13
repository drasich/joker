#ifndef __property__
#define __property__
#include "Elementary.h"

typedef struct _Property Property;

typedef void (*property_object_set)(void* object, void* data);
typedef void (*property_changed)(void* object, const void* data);

struct _Property
{
  Evas_Object* root;
  Evas_Object* box;
  Evas_Object* en;

  //void* data;

  property_changed changed;
};


Property* property_entry_new(Evas_Object* win);
void property_register_cb(
      Property* t,
      property_changed changed);

#endif
