#ifndef __property__
#define __property__
#include "Elementary.h"

typedef struct _Property JkProperty;

//typedef void (*property_object_set)(void* object, void* data);
typedef void (*property_changed)(const void* object, const void* data);
typedef const char* (*property_get)(const void* object);

typedef void (*property_set_changed)(const void* object, const char* path, const void* data);
typedef void (*property_register_change)(const void* object, const char* path, const void* old, const void* new, int action_type);

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

///////////////////////////////
typedef struct _PropertyNode PropertyNode;

struct _PropertyNode
{
  //path => propertyentry/evas_object
  //example name OR position/x OR parameter/life/max
  Eina_Hash* leafs;
  //name =>  PropertyNode;  
  //example position or parameter or life
  Eina_Hash* nodes;
  Elm_Object_Item* item;
};


////////////////////////


typedef struct _PropertySet JkPropertySet;

struct _PropertySet
{
  Evas_Object* root;
  Evas_Object* box;

  const void* data;

  //Eina_Hash* fields;

  PropertyNode* node;

  property_set_changed changed_float;
  property_set_changed changed_string;
};

PropertyNode* property_set_node_new();

JkPropertySet* property_set_new(Evas_Object* win);
void jk_property_set_register_cb(
      JkPropertySet* ps,
      void * data,
      property_set_changed changed_float,
      property_set_changed changed_string
      );
void property_set_data_set(JkPropertySet* set, void* data);

void property_set_clear(JkPropertySet* set);

void property_set_string_add(
      JkPropertySet* ps,
      const char* name,
      const char* value
      );

void property_set_float_add(
      JkPropertySet* ps, 
      const char* name,
      float value);

void property_set_node_add(
      JkPropertySet* ps, 
      const char* path);

//TODO TO BE TESTED
void property_set_string_update(
      JkPropertySet* set,
      const char* path,
      const char* value);
void property_set_float_update(JkPropertySet* set, const char* path, float value);

/////////////////
typedef void (*property_tree_object_expand)(void* data, void* object, Elm_Object_Item* parent);

typedef struct _PropertyList JkPropertyList;

struct _PropertyList
{
  Evas_Object* root;
  Evas_Object* list;

  void* data;

  PropertyNode* node;

  property_set_changed changed_float;
  property_set_changed changed_string;
  property_register_change register_change_string;
  property_register_change register_change_float;
  property_tree_object_expand expand;
};

typedef struct _PropertyValue PropertyValue;

struct _PropertyValue
{
  const char* path;
  void* data;
  Elm_Object_Item* item;
  JkPropertyList* list;
};


JkPropertyList* property_list_new(Evas_Object* win);
void property_list_clear(JkPropertyList* pl);

void jk_property_list_register_cb(
      JkPropertyList* ps,
      void * data,
      property_set_changed changed_float,
      property_set_changed changed_string,
      property_register_change register_change_string,
      property_register_change register_change_float,
      property_tree_object_expand expand
      );

void property_list_node_add(
      JkPropertyList* pl, 
      const char* path);

void property_list_float_add(
      JkPropertyList* ps, 
      const char* path,
      float value);

void property_list_group_add(
      JkPropertyList* ps, 
      const char* path);

PropertyNode* property_list_node_new();

#endif
