#ifndef __panel__
#define __panel__
#include <Elementary.h>
#include "common.h"

typedef struct _Panel Panel;

struct _Panel
{
  Evas_Object* close;
  Evas_Object* reduce;;
};

//typedef void (rust_cb)(void* data);
Evas_Object * smart_panel_add(Evas *evas);
void smart_panel_content_set(Evas_Object *o, Evas_Object* content);

Eo* layout_panel_add(Evas_Object* parent, const char* name);

typedef struct _JkPanel JkPanel;

struct _JkPanel
{
  Evas_Object* panel;

  panel_geom_cb move;
  panel_geom_cb resize;

  void* data;
};


#endif
