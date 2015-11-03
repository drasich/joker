#ifndef __ui_common__
#define __ui_common__
#include <Elementary.h>
#include "stdbool.h"

void object_show(Evas_Object* o, bool b);

typedef void (*panel_geom_cb)(
      void* data, int x, int y, int w, int h);

#endif
