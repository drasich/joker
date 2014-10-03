#include "glview.h"
#include "shader.h"
#include "buffer.h"
#include "cypher.h"
//#include "drawable.h"
#include "window.h"
#include "tree.h"

static void
_init_gl(Evas_Object *obj)
{
  cypher_init();
}

static void
_del_gl(Evas_Object *obj)
{
  cypher_del();
}

static void
_resize_gl(Evas_Object *obj)
{
  int w, h;
  elm_glview_size_get(obj, &w, &h);

  cypher_resize(w,h);
}

static void
_draw_gl(Evas_Object *obj)
{
  int w, h;
  elm_glview_size_get(obj, &w, &h);

  cypher_draw(w, h);
}



static void
simple_window_del(void *data, Evas_Object *obj, void *event_info)
{
  elm_exit();
}

//extern Evas_Object* win;

void
create_simple_window()
{
  Evas_Object* win = elm_win_util_standard_add("simple_window", "simple_window");
  elm_win_autodel_set(win, EINA_TRUE);
  evas_object_smart_callback_add(win, "delete,request", simple_window_del, NULL);

  Evas_Object* box = elm_box_add(win);
  evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, box);
  evas_object_show(box);

  Evas_Object* glview = _create_glview(win);
  elm_box_pack_end(box, glview);

  //callbacks
  elm_glview_init_func_set(glview, _init_gl);
  elm_glview_del_func_set(glview, _del_gl);
  elm_glview_resize_func_set(glview, _resize_gl);
  elm_glview_render_func_set(glview, _draw_gl);


  //evas_object_resize(win, 256, 256);
  evas_object_resize(win, 64, 64);
  evas_object_show(win);
}

void jk_init()
{
  eina_init();
  eet_init();
  srand (time(NULL));

  elm_config_preferred_engine_set("opengl_x11");
  elm_config_focus_highlight_animate_set(EINA_TRUE);
  elm_config_focus_highlight_enabled_set(EINA_TRUE);
  //create_simple_window();
}

EAPI_MAIN int
simple_window_main(int argc, char **argv)
{
  jk_init();
  init_callback_call();
  elm_run();
  elm_shutdown();
  return 0;
}

int
elmmain(int argc, char **argv)
{
  int ret;
  _elm_startup_time = ecore_time_unix_get();
  elm_init(argc, argv);
  ret = simple_window_main(argc, argv);
  return ret;
}

void
elm_simple_window_main()
{
  elmmain(0,0);
}

Creator*
creator_new()
{
  Creator* c = calloc(1, sizeof *c);

  Evas_Object* win = elm_win_util_standard_add("simple_window", "simple_window");
  c->win = win;
  elm_win_autodel_set(win, EINA_TRUE);
  evas_object_smart_callback_add(win, "delete,request", simple_window_del, NULL);

  Evas_Object* box = elm_box_add(win);
  evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, box);
  evas_object_show(box);

  Evas_Object* glview = _create_glview(win);
  elm_box_pack_end(box, glview);

  //callbacks
  elm_glview_init_func_set(glview, _init_gl);
  elm_glview_del_func_set(glview, _del_gl);
  elm_glview_resize_func_set(glview, _resize_gl);
  elm_glview_render_func_set(glview, _draw_gl);


  //evas_object_resize(win, 256, 256);
  evas_object_resize(win, 64, 64);
  evas_object_show(win);

  return c;
}


static rust_init_callback _init_callback_cb = 0;

void init_callback_set(rust_init_callback cb)
{
  _init_callback_cb = cb;
}

bool init_callback_call()
{
  if (_init_callback_cb) {
    _init_callback_cb();
    return true;
  }

  return false;
}


void creator_tree_new(Creator* c)
{
  Tree* t = tree_widget_new(c->win);
}
