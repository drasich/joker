#ifndef __ui_tree__
#define __ui_tree__
//#include "object.h"
//#include "context.h"
//#include "view.h"
#include "stdbool.h"

typedef struct _Tree Tree;

typedef const char* (*tree_object_name_get)(void* data);
typedef void (*tree_object_select)(void* data);
typedef bool (*tree_object_can_expand)(void* data);
typedef void (*tree_object_expand)(Tree* t, void* data, Elm_Object_Item* parent);


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
  tree_object_select select;
  tree_object_can_expand can_expand;
  tree_object_expand expand;
};

void tree_register_cb(
      Tree* t,
      tree_object_name_get name,
      tree_object_select select,
      tree_object_can_expand can_expand,
      tree_object_expand expand);


Tree* tree_widget_new(Evas_Object* win);
//void tree_object_add(Tree* t,  struct _Object* o);
//void tree_object_remove(Tree* t,  struct _Object* o);

//void tree_object_select(Tree* t, struct _Object* o);
//void tree_objects_select(Tree* t, Eina_List* objects);
//void tree_object_update(Tree* t, struct _Object* o);

//void tree_scene_set(Tree* t, struct _Scene* s);

//void tree_unselect_all(Tree* t);

void tree_object_add(Tree* t, void* o, Elm_Object_Item* parent);

#endif

