#ifndef __property__
#define __property__
#include "Elementary.h"
#include "stdbool.h"
#include "common.h"
#include "window.h"


typedef struct _Property JkProperty;

//typedef void (*property_object_set)(void* object, void* data);
typedef void (*property_changed)(const void* object, const void* data);
typedef const char* (*property_get)(const void* object);

typedef void (*property_changed2)(
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


/////////////////
typedef void (*property_tree_object_cb)(
      void* data,
      void* object,
      Elm_Object_Item* parent);

typedef struct _PropertyCb JkPropertyCb;
struct _PropertyCb
{
  property_changed2 changed_float;
  property_changed2 changed_string;
  property_changed2 changed_enum;
  property_register_change register_change_string;
  property_register_change register_change_float;
  property_register_change register_change_enum;
  property_register_change register_change_option;

  property_tree_object_cb expand;
  property_tree_object_cb contract;

  property_register_change vec_add;
  property_register_change vec_del;
};

void jk_property_cb_register(
      JkPropertyCb* cbs,
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
      );



typedef struct _PropertyList JkPropertyList;

struct _PropertyList
{
  Evas_Object* win;
  Evas_Object* root;
  Evas_Object* list;

  void* data;

  PropertyNode* node;
  PropertyNode* node_first_group;

  JkPropertyCb* cbs;

  panel_geom_cb move;
  panel_geom_cb resize;
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
      panel_geom_cb move
      );

PropertyValue* property_list_node_add(
      const char* path,
      const char* added_name);

void property_list_nodes_remove(
      JkPropertyList* pl,
      const char* path);

PropertyValue* property_list_float_add(
      const char* path,
      float value);

PropertyValue* property_list_string_add(
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



Eo* jk_property_panel_new(Window* w, int x, int y, int width, int height);
//JkPropertyBox* jk_window_property_box_new(Window* w);

void _property_node_clear(void* data);

JkPropertyCb* property_list_cb_get();
JkPropertyCb* property_box_cb_get();

typedef struct _PropertyBox JkPropertyBox;

struct _PropertyBox
{
  Evas_Object* win;
  Evas_Object* root;
  Evas_Object* box;

  void* data;

  PropertyNode* node;
  PropertyNode* node_first_group;

  JkPropertyCb* cbs;

  panel_geom_cb move;
  panel_geom_cb resize;
};

PropertyNode* property_box_node_new();

JkPropertyBox* property_box_new(Evas_Object* win);
void property_box_data_set(JkPropertyBox* set, void* data);

void property_box_clear(JkPropertyBox* set);

void property_box_string_add(
      JkPropertyBox* ps,
      const char* name,
      const char* value
      );

void property_box_float_add(
      JkPropertyBox* ps,
      const char* name,
      float value);

void property_box_node_add(
      JkPropertyBox* ps,
      const char* path);

//TODO TO BE TESTED
void property_box_string_update(
      JkPropertyBox* set,
      const char* path,
      const char* value);
void property_box_float_update(JkPropertyBox* set, const char* path, float value);


#endif
