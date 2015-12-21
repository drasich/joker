#include "list.h"
#include "stdlib.h"

JkList* jk_list_new()
{
  JkList *l = calloc(1, sizeof *l);
  //l->test = 12;
  return l;
}

Eo* jk_list_wdg_new(Eo* win, const char* name)
{
  Evas_Object* panel = layout_panel_add(win, name);
  return panel;
}
