#ifndef __panel__
#define __panel__
#include <Elementary.h>

typedef struct _Panel Panel;

struct _Panel
{
  Evas_Object* close;
  Evas_Object* reduce;;
};

//typedef void (rust_cb)(void* data);
Evas_Object * smart_panel_add(Evas *evas);


#endif
