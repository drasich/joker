#ifndef __property__
#define __property__
#include "Elementary.h"

typedef struct _Property Property;

//typedef void (*property_object_set)(void* object, void* data);
typedef void (*property_changed)(const void* object, const void* data);
typedef const char* (*property_get)(const void* object);

struct _Property
{
  Evas_Object* root;
  Evas_Object* box;
  Evas_Object* en;

  const void* data;

  property_changed changed;
  property_get get;
};


Property* property_entry_new(Evas_Object* win);
void property_register_cb(
      Property* t,
      property_changed changed,
      property_get get
      );

void property_data_set(
      Property* t,
      const void* data
      );

#endif
