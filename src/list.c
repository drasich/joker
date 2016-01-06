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
   char buf[256];
   snprintf(buf, sizeof(buf), "%s", genlist_demo_names[((int)(uintptr_t)data)%50]);
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

static Evas_Object* _create_genlist(Evas_Object* win)
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
  evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_ALWAYS);
  elm_genlist_mode_set(gl, ELM_LIST_COMPRESS);
  elm_genlist_homogeneous_set(gl, EINA_TRUE);
  elm_box_pack_end(bx2, gl);
  evas_object_event_callback_add(gl, EVAS_CALLBACK_FREE, _cleanup_cb, api);
  api->gl = gl;
  evas_object_show(gl);
  evas_object_smart_callback_add(gl, "selected", _gl_focus_item_cb, "selected");
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

  for (i = 0; i < 500; i++)
  elm_genlist_item_append(gl, itc,
        (void *)(long)i, NULL,
        ELM_GENLIST_ITEM_NONE,
        NULL, NULL);

  evas_object_show(win);
  elm_object_focus_set(entry, EINA_TRUE);
  evas_object_smart_callback_add(entry, "changed,user", _entry_change_cb, api);

  return bx;
}


Eo* jk_list_wdg_new(Window* w, const char* name)
{
  Evas_Object* panel = layout_panel_add(w->win, name);
  evas_object_move(panel, 100,100);
  evas_object_resize(panel, 100,100);

  //Eo* content = _content_new(w->win);
  Eo* content = _create_genlist(w->win);
  elm_object_part_content_set(panel, "content", content);

  return panel;
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

