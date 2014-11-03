#ifndef __property__
#define __property__
#include "Elementary.h"

typedef struct _Property JkProperty;

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


JkProperty* property_entry_new(Evas_Object* win);
void property_register_cb(
      JkProperty* t,
      property_changed changed,
      property_get get
      );

void property_data_set(
      JkProperty* t,
      const void* data
      );

typedef struct _PropertySet JkPropertySet;

struct _PropertySet
{
  Evas_Object* root;
  Evas_Object* box;

  const void* data;

  Eina_Hash* fields;
};

JkPropertySet* property_set_new(Evas_Object* win);
void property_set_data_set(JkPropertySet* set, void* data);

void property_set_clear(JkPropertySet* set);

void property_set_string_add(
      JkPropertySet* ps,
      const char* name,
      const char* value
      );

/////////////////

/*
typedef struct _PropertyEntry JkPropertyEntry;

struct _PropertyEntry
{
  Evas_Object* box;
  Evas_Object* label;
  Evas_Object* entry;

  const char* property_path;
  const JkProperty* container;

  property_changed changed;
  property_get get;
};
*/




#endif
