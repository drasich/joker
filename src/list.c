#include "list.h"
#include "stdlib.h"
#include "panel.h"

JkList* jk_list_new()
{
  JkList *l = calloc(1, sizeof *l);
  //l->test = 12;
  return l;
}

Eo* jk_list_wdg_new(Window* w, const char* name)
{
  Evas_Object* panel = layout_panel_add(w->win, name);
  evas_object_move(panel, 100,100);
  evas_object_resize(panel, 500,500);
  return panel;
}

