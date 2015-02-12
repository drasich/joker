#include <Elementary.h>
#include <Eina.h>
#include "tree.h"
//#include "object.h"
//#include "view.h"
#define __UNUSED__

static Elm_Genlist_Item_Class *itc1;
static Elm_Genlist_Item_Class *itc4;

static char *
gl_item_text_get(void *data, Evas_Object *obj, const char *part __UNUSED__)
{
  JkTree* t = evas_object_data_get(obj, "tree");
  if (t->name_get) {
    const char* name = t->name_get(data);
    return strdup(name);
  }

  return strdup("no function to get name");
}

Eina_Bool
gl4_state_get(void *data __UNUSED__, Evas_Object *obj __UNUSED__, const char *part __UNUSED__)
{
   return EINA_FALSE;
}

void gl4_del(void *data __UNUSED__, Evas_Object *obj __UNUSED__)
{
   //printf("item deleted.\n");
}

static void
gl4_sel(void *data, Evas_Object *obj __UNUSED__, void *event_info)
{
   JkTree* t = data;

   if (t->item_selected) {
     Elm_Object_Item *glit = event_info;
     void* o = elm_object_item_data_get(glit);

     t->item_selected(o);
   }
}


static void
gl4_exp(void *data, Evas_Object *obj __UNUSED__, void *event_info)
{
  //TODO expand children
   Elm_Object_Item *glit = event_info;
   Evas_Object *gl = elm_object_item_widget_get(glit);

   void* o = elm_object_item_data_get(glit);
   JkTree* t = data;

    if (t->expand) {
      t->expand(t->data,o, glit);
    }
}

static void
gl4_con(void *data, Evas_Object *obj __UNUSED__, void *event_info)
{
  //JkTree* v = data;
  Elm_Object_Item *glit = event_info;
  //something TODO?
  /*
  Object* o = elm_object_item_data_get(glit);

  Eina_List* l;
  Object* child;
  EINA_LIST_FOREACH(o->children, l, child) {
    eina_hash_del_by_key(v->tree->objects, &child);
  }
  */

  elm_genlist_item_subitems_clear(glit);
}

static void
gl4_exp_req(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_TRUE);
}

static void
gl4_con_req(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_FALSE);
}

static void
gl4_unselect(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   printf("unselect item\n");
   //TODO
   /*
   View* v = data;
   if (v) { 
     Context* context = v->context;
     context_object_remove(context, (Object*) elm_object_item_data_get(glit));
   }
   */

   void* o = elm_object_item_data_get(glit);
   JkTree* t = data;

    if (t->unselected) {
      t->unselected(t->data, o, glit);
    }
}

static void
gl4_select(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Elm_Object_Item *glit = event_info;

   void* o = elm_object_item_data_get(glit);
   JkTree* t = data;

    if (t->selected) {
      t->selected(t->data, o, glit);
    }
}

JkTree* 
tree_widget_new(Evas_Object* win)
{
  printf("tree widget new !!win: %p \n",win);
  JkTree *t = calloc(1, sizeof *t);

  Evas_Object *gli, *bx, *rd1, *rd2, *frame;

  bx = elm_box_add(win);
  t->box = bx;
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(bx);
  t->root = bx;

  gli = elm_genlist_add(win);
  evas_object_name_set(gli, "tree_widget");
  evas_object_data_set(gli, "tree", t);
  t->gl = gli;
  evas_object_size_hint_align_set(gli, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(gli, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(gli);
  elm_genlist_tree_effect_enabled_set(gli, EINA_TRUE);
  elm_genlist_multi_select_set(gli, EINA_TRUE);
  elm_genlist_reorder_mode_set(gli, EINA_TRUE);  
  elm_genlist_multi_select_mode_set(gli, ELM_OBJECT_MULTI_SELECT_MODE_WITH_CONTROL);

  itc1 = elm_genlist_item_class_new();
  itc1->item_style     = "default";
  itc1->func.text_get = gl_item_text_get;
  itc1->func.content_get  = NULL;
  itc1->func.state_get = gl4_state_get;
  itc1->func.del       = gl4_del;

  itc4 = elm_genlist_item_class_new();
  itc4->item_style = "tree_effect";
  itc4->func.text_get = gl_item_text_get;
  itc4->func.content_get = NULL;
  itc4->func.state_get = gl4_state_get;
  itc4->func.del = gl4_del;

  t->class_tree = itc4;
  t->class_simple = itc1;

  elm_genlist_item_class_ref(itc1);
  elm_genlist_item_class_free(itc1);

  evas_object_smart_callback_add(gli, "expand,request", gl4_exp_req, gli);
  evas_object_smart_callback_add(gli, "contract,request", gl4_con_req, gli);
  evas_object_smart_callback_add(gli, "expanded", gl4_exp, t);
  evas_object_smart_callback_add(gli, "contracted", gl4_con, t);
  evas_object_smart_callback_add(gli, "unselected", gl4_unselect, t);
  evas_object_smart_callback_add(gli, "selected", gl4_select, t);

  elm_box_pack_end(bx, gli);

  //t->objects = eina_hash_pointer_new(NULL);
  return t;
}

Elm_Object_Item*
tree_object_add(JkTree* t, void* o, Elm_Object_Item* parent)
{
  printf("tree object add ::  %p\n", o);

  const Elm_Genlist_Item_Class* class = t->class_simple;
  Elm_Genlist_Item_Type type = ELM_GENLIST_ITEM_NONE;

  if (t->can_expand) {
    if (t->can_expand(o)) {
      printf("it can expand..................... !!!\n");
      class = t->class_tree;
      type = ELM_GENLIST_ITEM_TREE;
    }
    else printf("..................cannot expand !!!\n");
  }
  else
      printf("no expand fn????????????..................... !!!\n");

  Elm_Object_Item* eoi = elm_genlist_item_append(
        t->gl,
        class,
        o,
        parent,
        type,
        gl4_sel,
        t);

  //EINA_LOG_DBG("I add parent %p, object pointer %p, object name pointer %p", eoi, o, &o->name );
  //eina_hash_add(t->objects, &o, eoi);
  //property_holder_genlist_item_add(&o->name, eoi);

  return eoi;
}


void tree_register_cb(
      JkTree* t,
      void* data,
      tree_object_name_get name,
      tree_item_selected item_selected,
      tree_object_can_expand can_expand,
      tree_object_expand expand,
      tree_selected selected,
      tree_selected unselected)
{
  t->name_get = name;
  t->item_selected = item_selected;
  t->can_expand = can_expand;
  t->expand = expand;
  t->selected = selected;
  t->unselected = unselected;

  t->data = data;
}

void tree_object_select(JkTree* t, void* o)
{
  // deselect already selected objects if it's not 'o'
  Eina_List* items = elm_genlist_realized_items_get(t->gl);
  Elm_Object_Item* i;
  Eina_List* l;

  EINA_LIST_FOREACH(items, l, i) {
    void* eo = elm_object_item_data_get(i);
    if (o == eo) {
      elm_genlist_item_selected_set(i, EINA_TRUE);
    }
    else {
      elm_genlist_item_selected_set(i, EINA_FALSE);
    }
  }

  eina_list_free(items);

  ///////////////
  //TODO if object is not displayed ('realized')
  // display it and move to it

  /*
  Elm_Object_Item* eoi = eina_hash_find(t->objects, &o);
  if (eoi) {
    elm_genlist_item_selected_set(eoi, EINA_TRUE);
  }
  else {
      Eina_List* path = object_parents_path_get(o);
      Eina_List* pl;
      Object* po;
      EINA_LIST_FOREACH(path, pl, po) {
        eoi = eina_hash_find(t->objects, &po);
        if (eoi) {
          elm_genlist_item_expanded_set(eoi, EINA_TRUE);
        }
      }
      eoi = eina_hash_find(t->objects, &o);
      if (eoi) {
        elm_genlist_item_show(eoi, ELM_GENLIST_ITEM_SCROLLTO_MIDDLE);
        elm_genlist_item_selected_set(eoi, EINA_TRUE);
      }

      */
}

void tree_item_select(Elm_Object_Item* item)
{
  elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_MIDDLE);
  elm_genlist_item_selected_set(item, EINA_TRUE);
}

void tree_deselect_all(JkTree *t)
{
  Eina_List* items = elm_genlist_realized_items_get(t->gl);
  Elm_Object_Item* i;
  Eina_List* l;

  EINA_LIST_FOREACH(items, l, i) {
    void* eo = elm_object_item_data_get(i);
      elm_genlist_item_selected_set(i, EINA_FALSE);
  }

  eina_list_free(items);
}

void tree_item_expand(Elm_Object_Item* item)
{
  elm_genlist_item_expanded_set(item, EINA_TRUE);
}

void tree_update(JkTree* t)
{
  elm_genlist_realized_items_update(t->gl);
}

void tree_item_update(Elm_Object_Item* item)
{
  elm_genlist_item_update(item);
}


