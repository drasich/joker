#ifndef __property__
#define __property__
#include "Elementary.h"
#include "stdbool.h"
#include "common.h"

typedef struct _Property JkProperty;

//typedef void (*property_object_set)(void* object, void* data);
typedef void (*property_changed)(const void* object, const void* data);
typedef const char* (*property_get)(const void* object);

typedef void (*property_set_changed)(
      const void* object,
      const char* path,
      const void* data);
typedef void (*property_register_change)(
      const void* object,
      const char* path,
      const void* old,
      const void* new,
      int action_type);

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
typedef void (*property_tree_object_cb)(
      void* data,
      void* object,
      Elm_Object_Item* parent);

typedef struct _PropertyList JkPropertyList;

struct _PropertyList
{
  Evas_Object* win;
  Evas_Object* root;
  Evas_Object* list;

  void* data;

  PropertyNode* node;
  PropertyNode* node_first_group;

  property_set_changed changed_float;
  property_set_changed changed_string;
  property_set_changed changed_enum;
  property_register_change register_change_string;
  property_register_change register_change_float;
  property_register_change register_change_enum;
  property_register_change register_change_option;
  property_tree_object_cb expand;
  property_tree_object_cb contract;

  panel_geom_cb move;
  panel_geom_cb resize;

  property_register_change vec_add;
  property_register_change vec_del;
};


typedef struct _PropertyValue PropertyValue;
typedef Eo* (*item_create)(PropertyValue* val, Eo* obj);

struct _PropertyValue
{
  const char* path;
  void* data;
  Elm_Object_Item* item;
  JkPropertyList* list;
  void* user_data;
  int len;
  const char* added_name;

  item_create create_child;
};


JkPropertyList* property_list_new(Evas_Object* win);
void property_list_clear(JkPropertyList* pl);

void jk_property_list_register_cb(
      JkPropertyList* ps,
      void * data,
      property_set_changed changed_float,
      property_set_changed changed_string,
      property_set_changed changed_enum,
      property_register_change register_change_string,
      property_register_change register_change_float,
      property_register_change register_change_enum,
      property_register_change register_change_option,
      property_tree_object_cb expand,
      property_tree_object_cb contract,
      panel_geom_cb move
      );

void jk_property_list_register_vec_cb(
      JkPropertyList* ps,
      property_register_change add_cb,
      property_register_change del_cb);

PropertyValue* property_list_node_add(
      JkPropertyList* pl,
      const char* path,
      const char* added_name);

void property_list_nodes_remove(
      JkPropertyList* pl,
      const char* path);

PropertyValue* property_list_float_add(
      JkPropertyList* ps,
      const char* path,
      float value);

PropertyValue* property_list_string_add(
      JkPropertyList* ps,
      const char* path,
      const char* value);

PropertyValue*
property_list_single_item_add(
      JkPropertyList* pl,
      PropertyValue* pv);

PropertyValue*
property_list_single_vec_add(
      JkPropertyList* pl,
      PropertyValue* pv,
      bool is_node);

void property_list_group_add(
      JkPropertyList* ps,
      const char* path);

PropertyValue*
property_list_enum_add(
      JkPropertyList* pl,
      const char* path,
      char* possible_values,
      const char* value);

PropertyValue*
property_list_option_add(
      JkPropertyList* pl,
      const char* path,
      const char* value);

void property_list_enum_update(
      PropertyValue* val,
      const char* value);

PropertyNode* property_list_node_new();

void property_list_string_update(
      PropertyValue* val,
      const char* value);

void property_list_vec_update(
      PropertyValue* val,
      int len);

void property_list_option_update(
      PropertyValue* val,
      const char* value);

void property_list_float_update(
      PropertyValue* val,
      float value);

void property_expand(PropertyValue* value);

void property_show(
      JkPropertyList* p,
      bool b);

#endif
