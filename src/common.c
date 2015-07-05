#include "common.h"

void object_show(Evas_Object* o, bool b)
{
  if (b) {
    evas_object_show(o);
  }
  else {
    evas_object_hide(o);
  }

}

