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
   printf("%s: %p\n", (char *)data, event_info);
   select_callback fn = evas_object_data_get(obj, "fn");
   void* fn_data = evas_object_data_get(obj, "fn_data");
   if (fn && fn_data) {
     Elm_Object_Item *glit = event_info;
     const char* t = elm_object_item_text_get(glit);
     fn(fn_data, t);
   }
}


static void
_gl_focus_key_down_cb(void *data EINA_UNUSED, Evas *e EINA_UNUSED,
                      Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Evas_Event_Key_Down *ev = event_info;
   printf("\n=== Key Down : %s ===\n", ev->keyname);
}

char *genlist_demo_names[] = {
        "Aaliyah", "Aamir", "Aaralyn", "Aaron", "Abagail",
        "Babitha", "Bahuratna", "Bandana", "Bulbul", "Cade", "Caldwell",
        "Chandan", "Caster", "Dagan ", "Daulat", "Dag", "Earl", "Ebenzer",
        "Ellison", "Elizabeth", "Filbert", "Fitzpatrick", "Florian", "Fulton",
        "Frazer", "Gabriel", "Gage", "Galen", "Garland", "Gauhar", "Hadden",
        "Hafiz", "Hakon", "Haleem", "Hank", "Hanuman", "Jabali ", "Jaimini",
        "Jayadev", "Jake", "Jayatsena", "Jonathan", "Kamaal", "Jeirk",
        "Jasper", "Jack", "Mac", "Macy", "Marlon", "Milson",
        NULL
};

static char *
glf_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   char** names = evas_object_data_get(obj, "names");
   size_t len = evas_object_data_get(obj, "len");
  //printf("item len : %d \n ", ((int) (uintptr_t)len));
  printf("item len : %d \n ", len);
   char buf[256];
   //snprintf(buf, sizeof(buf), "%s", genlist_demo_names[((int)(uintptr_t)data)%50]);
   snprintf(buf, sizeof(buf), "%s", names[((int)(uintptr_t)data)%len]);
   return strdup(buf);
}

Eina_Bool
gl_filter_get(void *data, Evas_Object *obj EINA_UNUSED, void *key)
{
   if (!strlen((char *)key)) return EINA_TRUE;

   if (strcasestr(genlist_demo_names[((int)(uintptr_t)data)%50], (char *)key))
     return EINA_TRUE;
   // Default case should return false (item fails filter hence will be hidden)
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
  elm_box_pack_end(bx, entry);
  evas_object_show(entry);

  bx2 = elm_box_add(bx);
  evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_pack_end(bx, bx2);
  evas_object_show(bx2);

  gl = elm_genlist_add(bx);
  evas_object_event_callback_add(gl, EVAS_CALLBACK_FREE, _cleanup_cb, api);
  evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_ALWAYS);
  elm_genlist_mode_set(gl, ELM_LIST_COMPRESS);
  elm_genlist_homogeneous_set(gl, EINA_TRUE);
  elm_box_pack_end(bx2, gl);
  api->gl = gl;
  evas_object_show(gl);
  evas_object_smart_callback_add(gl, "selected", _gl_select_item_cb, "selected");
  evas_object_smart_callback_add(gl, "unselected", _gl_focus_item_cb, "unselected");
  evas_object_smart_callback_add(gl, "activated", _gl_focus_item_cb, "activated");
  evas_object_smart_callback_add(gl, "highlighted", _gl_focus_item_cb, "highlighted");
  evas_object_smart_callback_add(gl, "unhighlighted", _gl_focus_item_cb, "unhighlighted");
  evas_object_smart_callback_add(gl, "filter,done", _gl_filter_finished_cb, NULL);
  evas_object_event_callback_add(gl, EVAS_CALLBACK_KEY_DOWN, _gl_focus_key_down_cb, NULL);

  evas_object_data_set(gl, "names", genlist_demo_names);
  evas_object_data_set(gl, "len", 50);

  itc = elm_genlist_item_class_new();
  itc->item_style = "default";
  itc->func.text_get = glf_text_get;
  itc->func.content_get = NULL;
  itc->func.filter_get = gl_filter_get;
  itc->func.state_get = NULL;
  itc->func.del = NULL;

  for (i = 0; i < 500; i++)
  elm_genlist_item_append(gl, itc,
        (void *)(long)i, NULL,
        ELM_GENLIST_ITEM_NONE,
        NULL, NULL);

  //elm_object_focus_set(entry, EINA_TRUE);
  evas_object_smart_callback_add(entry, "changed,user", _entry_change_cb, api);

  struct __JkList* ll = calloc(1, sizeof *ll);
  ll->box = bx;
  ll->gl = gl;
  ll->itc = itc;

  return ll;
}


Eo* jk_list_wdg_new(Window* w, const char* name)
{
  Evas_Object* panel = layout_panel_add(w->win, name);
  evas_object_move(panel, 100,100);
  evas_object_resize(panel, 100,100);

  //Eo* content = _content_new(w->win);
  struct __JkList* ll = _create_genlist(w->win);
  elm_object_part_content_set(panel, "content", ll->box);

  evas_object_data_set(panel, "jklist", ll);

  return panel;
}

void jklist_set_names(Evas_Object* panel, char** names, size_t len)
{
  struct __JkList* ll = evas_object_data_get(panel, "jklist");
  evas_object_data_set(ll->gl, "names", names);
  evas_object_data_set(ll->gl, "len", len);

  elm_genlist_clear(ll->gl);

  for (int i = 0; i < len; i++)
  elm_genlist_item_append(ll->gl, ll->itc,
        (void *)(long)i, NULL,
        ELM_GENLIST_ITEM_NONE,
        NULL, NULL);
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

