#include <Elementary.h>
#include <Eina.h>
#include "tree.h"
//#include "object.h"
//#include "view.h"
#define __UNUSED__

static Elm_Genlist_Item_Class *itc1;
static Elm_Genlist_Item_Class *itc4;

static char *gl4_text_get(void *data, Evas_Object *obj, const char *part __UNUSED__)
{
  /*
  char buf[256];
  Object* o = (Object*) data;
  snprintf(buf, sizeof(buf), "%s", o->name);
  return strdup(buf);
  */
  //TODO rust tree->get_name(data)
  Tree* t = evas_object_data_get(obj, "tree");
  if (t->name_get) {
    printf("object name text get %p \n", data);
    //return strdup("testcaca");
    const char* name = t->name_get(data);
    printf("object name :::::::::: %s \n ", name);
    //printf("object name %s \n ", evas_object_name_get(obj));
    return strdup(name);
  }
  return strdup("test");
}

Evas_Object *gl4_content_get(void *data __UNUSED__, Evas_Object *obj, const char *part)
{
  return NULL;

  char buf[PATH_MAX];
  if (!strcmp(part, "elm.swallow.icon"))
   {
    Evas_Object *ic = elm_icon_add(obj);
    snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
    elm_image_file_set(ic, buf, NULL);
    evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
    evas_object_show(ic);
    return ic;
   }
  else if (!strcmp(part, "elm.swallow.end"))
   {
    Evas_Object *ck;
    ck = elm_check_add(obj);
    evas_object_propagate_events_set(ck, EINA_FALSE);
    evas_object_show(ck);
    return ck;
   }

  return NULL;
}

Eina_Bool gl4_state_get(void *data __UNUSED__, Evas_Object *obj __UNUSED__, const char *part __UNUSED__)
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
  //TODO rust tree->select(data)
   Elm_Object_Item *glit = event_info;
   //int depth = elm_genlist_item_expanded_depth_get(glit);
   //printf("expanded depth for selected item is %d", depth);

   /*
   View* v = data;
   if (v) { 
     Context* context = v->context;
     //context_clean_objects(context);
     context_object_add(context, (Object*) elm_object_item_data_get(glit));
   }
   */
}


static void
gl4_exp(void *data, Evas_Object *obj __UNUSED__, void *event_info)
{
  //TODO expand children
   Elm_Object_Item *glit = event_info;
   Evas_Object *gl = elm_object_item_widget_get(glit);

   void* o = elm_object_item_data_get(glit);
   Tree* t = data;

   /*
   Eina_List*l;
   Object* child;
   EINA_LIST_FOREACH(o->children, l, child) {
     if (eina_list_count(child->children) > 0) {

       Elm_Object_Item* eoi = elm_genlist_item_append(
             gl,
             itc4,
             child,
             glit,// parent
             ELM_GENLIST_ITEM_TREE,
             gl4_sel,
             data);

       eina_hash_add(v->tree->objects, &child, eoi);
     }
     else {
       Elm_Object_Item* eoi = elm_genlist_item_append(
             gl,
             itc1,
             child,
             glit,
             ELM_GENLIST_ITEM_NONE,
             gl4_sel,
             data);
       eina_hash_add(v->tree->objects, &child, eoi);

     }
   }
   */
}

static void
gl4_con(void *data, Evas_Object *obj __UNUSED__, void *event_info)
{
  /*
  View* v = data;
  Elm_Object_Item *glit = event_info;
  Object* o = elm_object_item_data_get(glit);

  Eina_List* l;
  Object* child;
  EINA_LIST_FOREACH(o->children, l, child) {
    eina_hash_del_by_key(v->tree->objects, &child);
  }

  elm_genlist_item_subitems_clear(glit);
  */
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
_tree_effect_enable_cb(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   elm_genlist_tree_effect_enabled_set(data, EINA_TRUE);
}

static void
_tree_effect_disable_cb(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   elm_genlist_tree_effect_enabled_set(data, EINA_FALSE);
}

static void
gl4_unselect(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   /*
   View* v = data;
   if (v) { 
     Context* context = v->context;
     context_object_remove(context, (Object*) elm_object_item_data_get(glit));
   }
   */
}



/*
static void
_context_tree_msg_receive(Context* c, void* tree, const char* msg)
{
  printf("context tree msg receive %s\n", msg);
  if (!strcmp(msg, "clean_objects"))
  tree_unselect_all(tree);
  else if (!strcmp(msg, "add_object"))
  tree_objects_select(tree, c->objects);
  else if (!strcmp(msg, "objects_changed")) {
    tree_objects_select(tree, c->objects);
  }
}
*/

Tree* 
tree_widget_new(Evas_Object* win)//, struct _View* v)
{
  printf("tree widget new !!win: %p \n",win);
  Tree *t = calloc(1, sizeof *t);

  Evas_Object *gli, *bx, *rd1, *rd2, *frame;

  bx = elm_box_add(win);
  t->box = bx;
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(bx);
  t->root = bx;

  gli = elm_genlist_add(win);
  evas_object_name_set(gli, "yoyoyoyoyoyee");
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
  itc1->func.text_get = gl4_text_get;
  itc1->func.content_get  = gl4_content_get;
  itc1->func.state_get = gl4_state_get;
  itc1->func.del       = gl4_del;

  itc4 = elm_genlist_item_class_new();
  itc4->item_style = "tree_effect";
  itc4->func.text_get = gl4_text_get;
  itc4->func.content_get = gl4_content_get;
  itc4->func.state_get = gl4_state_get;
  itc4->func.del = gl4_del;

  t->class_tree = itc4;
  t->class_simple = itc1;

  elm_genlist_item_class_ref(itc1);
  elm_genlist_item_class_free(itc1);

  evas_object_smart_callback_add(gli, "expand,request", gl4_exp_req, gli);
  evas_object_smart_callback_add(gli, "contract,request", gl4_con_req, gli);
  evas_object_smart_callback_add(gli, "expanded", gl4_exp, NULL);
  evas_object_smart_callback_add(gli, "contracted", gl4_con, NULL);
  evas_object_smart_callback_add(gli, "unselected", gl4_unselect, NULL);

  elm_box_pack_end(bx, gli);

  //t->objects = eina_hash_pointer_new(NULL);
  printf("pointer win, t %p , %p \n", win, t);
  /*
  tree_object_add(t);
  tree_object_add(t);
  tree_object_add(t);
  tree_object_add(t);
  */

  return t;
}

void
tree_object_add(Tree* t, void* o)
{
  printf("tree object add ::  %p\n", o);
  static Elm_Object_Item* parent = NULL;
  //if (o->parent)
  //parent = _tree_get_item(t, o);

  const Elm_Genlist_Item_Class* class = t->class_simple;
  //if (eina_list_count(o->children) > 0) {
  bool b = false;
  Elm_Genlist_Item_Type type = ELM_GENLIST_ITEM_NONE;
  if (t->can_expand) {
    b = t->can_expand(o);
  }

  if (b) {
    t->class_tree;
    type = ELM_GENLIST_ITEM_TREE;
  }

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
}


void tree_register_cb(
      Tree* t,
      tree_object_name_get name,
      tree_object_select select,
      tree_object_can_expand can_expand,
      tree_object_expand expand)
{
  t->name_get = name;
  t->select = select;
  t->can_expand = can_expand;
  t->expand = expand;
}

