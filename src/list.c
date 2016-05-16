#include <string.h>
#include "list.h"
#include "stdlib.h"
#include "panel.h"

JkList* jk_list_new()
{
  JkList *l = calloc(1, sizeof *l);
  //l->test = 12;
  return l;
}

static Eo* _content_new(Evas_Object* win)
{
  Evas_Object* box = elm_box_add(win);
  elm_box_homogeneous_set(box, EINA_FALSE);
  //evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(box);
  Eo* l = elm_list_add(win);
  elm_list_item_append(l, "Item 0", NULL, NULL, NULL, NULL);
  elm_list_item_append(l, "Item 1", NULL, NULL, NULL, NULL);
  elm_list_item_append(l, "Item 2", NULL, NULL, NULL, NULL);
  evas_object_size_hint_align_set(l, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(l, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(l);
  elm_box_pack_end(box, l);

  Eo* e = elm_entry_add(win);
  elm_entry_single_line_set(e, EINA_TRUE);
  elm_entry_scrollable_set(e, EINA_TRUE);
  evas_object_size_hint_align_set(e, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_show(e);
  elm_box_pack_end(box, e);

  /*
  Evas_Object* b = elm_button_add(win);
  evas_object_size_hint_align_set(b, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(b, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(b);
  elm_box_pack_end(box, b);
  */
  return box;
}

struct _api_data
{
   unsigned int state;  /* What state we are testing       */
   void *box;           /* Use this to get box content     */

   Elm_Genlist_Item_Class *itc;
   Elm_Genlist_Item_Class *itc1;
   Elm_Genlist_Item_Class *itc2;
   void *gl;

   void *filter_data;   /* The data used for filtering     */
};
typedef struct _api_data api_data;



static void
_gl_focus_item_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("%s: %p\n", (char *)data, event_info);
}

static void
_gl_select_item_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   select_callback fn = evas_object_data_get(obj, "fn");
   void* fn_data = evas_object_data_get(obj, "fn_data");
   if (fn && fn_data) {
     Elm_Object_Item *glit = event_info;
     const char* t = elm_object_item_text_get(glit);
     fn(fn_data, t);
   }
   Evas_Object* container = data;
   evas_object_hide(container);
}

static void
_gl_unfocus_item_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
  printf("unfocus ______________ \n");
  Evas_Object* panel = data;
  evas_object_hide(panel);
}



static void
_gl_focus_key_down_cb(void *data EINA_UNUSED, Evas *e EINA_UNUSED,
                      Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Evas_Event_Key_Down *ev = event_info;
   printf("\n=== Key Down : %s ===\n", ev->keyname);
}

static char *
glf_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   return strdup(data);
}

Eina_Bool
gl_filter_get(void *data, Evas_Object *obj EINA_UNUSED, void *key)
{
   if (!strlen((char *)key)) return EINA_TRUE;

   if (strcasestr(data, (char*) key))
     return EINA_TRUE;
   return EINA_FALSE;
}

static void
_gl_filter_finished_cb(void *data EINA_UNUSED,
                       Evas_Object *obj EINA_UNUSED,
                       void *event_info EINA_UNUSED)
{
   printf("Filter finished\n");
}

void
_entry_change_cb(void *data, Evas_Object *obj, void *event EINA_UNUSED)
{
   api_data *api = (api_data *)data;
   char buf[100];
   unsigned int count = 0;
   Elm_Object_Item *item;

   if (api->filter_data) free(api->filter_data);

   sprintf(buf, "%s", elm_object_text_get(obj));
   api->filter_data = strdup(buf);
   elm_genlist_filter_set(api->gl, (void *)(api->filter_data));
   if (!strlen(buf))
     {
        printf("Input data string empty; returning\n");
        return;
     }

   item = elm_genlist_first_item_get(api->gl);
   if (!item)
     {
        printf("No matches for the key %s\n", buf);
        return;
     }
   while (item)
     {
        ++count;
        item = elm_genlist_item_next_get(item);
     }
   printf("Number of matches for %s is %d\n", buf, count);
}

static void
_cleanup_cb(void *data, Evas *e EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = (api_data *)data;
   if (api->filter_data) free(api->filter_data);
   free(api);
}

struct __JkList
{
  Evas_Object* box;
  Evas_Object* gl;
  Elm_Genlist_Item_Class *itc;
};

static struct __JkList* _create_genlist(Evas_Object* win)
{
  Evas_Object *bx, *bx2, *entry, *gl;
  Elm_Genlist_Item_Class *itc = NULL;
  int i;

  api_data *api = calloc(1, sizeof(api_data));

  bx = elm_box_add(win);
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(bx);

  entry = elm_entry_add(bx);
  elm_entry_single_line_set(entry, EINA_TRUE);
  elm_entry_scrollable_set(entry, EINA_TRUE);
  evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, 0.0);
  evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, 0.0);
  elm_object_part_text_set(entry, "guide", "Search.");
  int w , h;
  evas_object_size_hint_min_get(entry, &w, &h);
  w = w < 100? 100:w;
  evas_object_size_hint_min_set(entry, w, h);
  elm_box_pack_end(bx, entry);
  evas_object_show(entry);

  bx2 = elm_box_add(bx);
  evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_pack_end(bx, bx2);
  evas_object_show(bx2);

  Eo* table = elm_table_add(win);
  elm_table_add(table);

  evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(table, EVAS_HINT_FILL, EVAS_HINT_FILL);

  Eo* rect = evas_object_rectangle_add(evas_object_evas_get(win));
  evas_object_size_hint_min_set(rect, 250, 200);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_table_pack(table, rect, 0, 0, 1, 1);
  evas_object_show(table);

  gl = elm_genlist_add(bx);
  evas_object_event_callback_add(gl, EVAS_CALLBACK_FREE, _cleanup_cb, api);
  evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_ALWAYS);
  elm_genlist_mode_set(gl, ELM_LIST_COMPRESS);
  elm_genlist_homogeneous_set(gl, EINA_TRUE);
  elm_table_pack(table, gl , 0, 0, 1, 1);
  elm_box_pack_end(bx2, table);
  api->gl = gl;
  evas_object_show(gl);

  evas_object_smart_callback_add(gl, "unselected", _gl_focus_item_cb, "unselected");
  evas_object_smart_callback_add(gl, "activated", _gl_focus_item_cb, "activated");
  evas_object_smart_callback_add(gl, "highlighted", _gl_focus_item_cb, "highlighted");
  evas_object_smart_callback_add(gl, "unhighlighted", _gl_focus_item_cb, "unhighlighted");
  evas_object_smart_callback_add(gl, "filter,done", _gl_filter_finished_cb, NULL);
  evas_object_event_callback_add(gl, EVAS_CALLBACK_KEY_DOWN, _gl_focus_key_down_cb, NULL);

  itc = elm_genlist_item_class_new();
  itc->item_style = "default";
  itc->func.text_get = glf_text_get;
  itc->func.content_get = NULL;
  itc->func.filter_get = gl_filter_get;
  itc->func.state_get = NULL;
  itc->func.del = NULL;

  //elm_object_focus_set(entry, EINA_TRUE);
  evas_object_smart_callback_add(entry, "changed,user", _entry_change_cb, api);

  struct __JkList* ll = calloc(1, sizeof *ll);
  ll->box = bx;
  ll->gl = gl;
  ll->itc = itc;

  return ll;
}

static Eo* _createpanel(Window* w, const char* name)
{
  Evas_Object* panel = layout_panel_add(w->win, name);
  evas_object_move(panel, 100,100);
  evas_object_resize(panel, 100,100);

  //Eo* content = _content_new(w->win);
  struct __JkList* ll = _create_genlist(w->win);
  elm_object_part_content_set(panel, "content", ll->box);

  evas_object_smart_callback_add(ll->gl, "selected", _gl_select_item_cb, panel);
  //evas_object_smart_callback_add(ll->gl, "unfocused", _gl_unfocus_item_cb, panel);

  evas_object_data_set(panel, "jklist", ll);

  return panel;

}

static Eo* _createhover(Window* w, const char* name)
{
  Evas_Object* hover = elm_hover_add(w->win);
  elm_hover_parent_set(hover, w->win);
  //elm_object_style_set(hover,"popout");

  Evas_Object* panel = layout_panel_add(w->win, name);

  struct __JkList* ll = _create_genlist(w->win);
  elm_object_part_content_set(panel, "content", ll->box);
  elm_layout_sizing_eval(panel);

  //Eo* content = _content_new(w->win);
  //elm_object_part_content_set(hover, "bottom", ll->box);
  elm_object_part_content_set(hover, "bottom", panel);

  evas_object_smart_callback_add(ll->gl, "selected", _gl_select_item_cb, hover);
  //evas_object_smart_callback_add(ll->gl, "unfocused", _gl_unfocus_item_cb, panel);

  evas_object_data_set(hover, "jklist", ll);

  return hover;

}


Eo* jk_list_wdg_new(Window* w, const char* name)
{
  return _createpanel(w, name);
}

Eo* jk_list_wdg_new2(Window* w, const char* name)
{
  return _createhover(w, strdup(name));
}


void jklist_set_names(Evas_Object* panel, char** names, size_t len)
{
  struct __JkList* ll = evas_object_data_get(panel, "jklist");
  elm_genlist_clear(ll->gl);

  for (int i = 0; i < len; i++) {
    printf("set names ............... i : %d, ::: %s \n", i,
          names[((int)(uintptr_t)i)%len]
          );
    elm_genlist_item_append(
          ll->gl,
          ll->itc,
          strdup(names[((int)(uintptr_t)i)%len]),
          NULL,
          ELM_GENLIST_ITEM_NONE,
          NULL, NULL);
  }
}

void jk_list_fn_set(
      Evas_Object *o,
      select_callback fn,
      void* data)
{
  printf("list fn \n");
  struct __JkList* ll = evas_object_data_get(o, "jklist");
  Evas_Object* list = ll->gl;

  evas_object_data_set(list, "fn", fn);
  evas_object_data_set(list, "fn_data", data);
}


void do_something_with_slice(void* slice, size_t len)
{
  char** yop = slice;
  printf("len : %d \n", len);
  for (int i = 0; i < len; ++i)
   {
    //printf("slice : %d, %s \n",i, *(yop+i));
    printf("slice : %d, %s \n",i, yop[i]);
   }
}

