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


Eo* jk_list_wdg_new(Window* w, const char* name)
{
  Evas_Object* panel = layout_panel_add(w->win, name);
  evas_object_move(panel, 100,100);
  evas_object_resize(panel, 100,100);

  Eo* content = _content_new(w->win);
  elm_object_part_content_set(panel, "content", content);

  return panel;
}

