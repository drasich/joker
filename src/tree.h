#ifndef __ui_tree__
#define __ui_tree__
//#include "object.h"
//#include "context.h"
//#include "view.h"
#include "stdbool.h"

typedef struct _Tree JkTree;

typedef const char* (*tree_object_name_get)(void* data);
typedef void (*tree_item_selected)(void* data);
typedef bool (*tree_object_can_expand)(void* data);
//typedef void (*tree_object_expand)(JkTree* t, void* data, Elm_Object_Item* parent);
typedef void (*tree_object_expand)(void* data, void* object, Elm_Object_Item* parent);
typedef void (*tree_selected)(void* data, void* object, Elm_Object_Item* parent);

struct _Tree
{
  Evas_Object* root;
  Evas_Object* box;
  Evas_Object* gl;

  //Context* context;
  //View* view;
  //Control* control;

  //Eina_Hash* objects;

  const Elm_Genlist_Item_Class* class_tree;
  const Elm_Genlist_Item_Class* class_simple;

  tree_object_name_get name_get;
  tree_item_selected item_selected;
  tree_object_can_expand can_expand;
  tree_object_expand expand;
  tree_selected selected;

  void* data;
};

void tree_register_cb(
      JkTree* t,
      void* data,
      tree_object_name_get name,
      tree_item_selected item_selected,
      tree_object_can_expand can_expand,
      tree_object_expand expand,
      tree_selected selected
      );


JkTree* tree_widget_new(Evas_Object* win);
//void tree_object_add(JkTree* t,  struct _Object* o);
//void tree_object_remove(JkTree* t,  struct _Object* o);

//void tree_object_select(JkTree* t, struct _Object* o);
//void tree_objects_select(JkTree* t, Eina_List* objects);
//void tree_object_update(JkTree* t, struct _Object* o);

//void tree_scene_set(JkTree* t, struct _Scene* s);

//void tree_unselect_all(JkTree* t);

Elm_Object_Item* tree_object_add(JkTree* t, void* o, Elm_Object_Item* parent);
void tree_object_select(JkTree* t, void* o);
void tree_item_select(Elm_Object_Item* item);

void tree_deselect_all(JkTree *t);
void tree_item_expand(Elm_Object_Item* item);
void tree_update(JkTree* t);
void tree_item_update(Elm_Object_Item* item);

#endif

