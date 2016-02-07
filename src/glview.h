#ifndef __glview__
#define __glview__
#include <Elementary.h>
#include "gl.h"
#include "cypher.h"
#include "stdbool.h"

Eina_Bool _anim(void *data);
void _del(void *data, Evas *evas, Evas_Object *obj, void *event_info);

Evas_Object* _create_glview(Evas_Object* win, bool auto_refresh);

typedef struct _JkGlview JkGlview;
struct _JkGlview
{
  Evas_Object* glview;
  void* cb_data;
  rust_callback init;
  rust_callback draw;
  resize_callback resize;
};

JkGlview* jk_glview_new(
      Evas_Object* win,
      void* data,
      rust_callback init,
      rust_callback draw,
      resize_callback resize
      );

void jk_glview_request_update(JkGlview* jgl);

#endif
