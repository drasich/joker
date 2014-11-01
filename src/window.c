/* Enable access to unstable EFL API that are still in beta */
#define EFL_BETA_API_SUPPORT 1

/* Enable access to unstable EFL EO API. */
#define EFL_EO_API_SUPPORT 1

#include "glview.h"
#include "shader.h"
#include "buffer.h"
#include "cypher.h"
//#include "drawable.h"
#include "window.h"
#include "tree.h"
#include "property.h"

#define __UNUSED__

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

static void
_key_down(void *data __UNUSED__, Evas *e __UNUSED__, Evas_Object *o __UNUSED__, void *event_info)
{
  Evas_Event_Key_Down *ev = (Evas_Event_Key_Down*)event_info;
  EINA_LOG_DBG("KEY: down, keyname: %s , key %s", ev->keyname, ev->key);
  //printf("KEY: down, keyname: %s , key %s\n", ev->keyname, ev->key);

  Window* w = data;
  if (w->key_down) {
    w->key_down(w->data, "", ev->keyname, ev->key, ev->timestamp);
  }

  //View* v = evas_object_data_get(o, "view");
  //Control* cl = v->control;
  //control_key_down(cl, ev);
}

static void
_mouse_move(void *data __UNUSED__, Evas *e __UNUSED__, Evas_Object *o, void *event_info)
{
  //elm_object_focus_set(o, EINA_TRUE);
  Evas_Event_Mouse_Move *ev = (Evas_Event_Mouse_Move*) event_info;

  Evas_Coord x, y, w, h;
  evas_object_geometry_get (o, &x, &y, &w, &h);
  int curx = ev->cur.canvas.x - x;
  int cury = ev->cur.canvas.y - y;

  int prevx = ev->prev.canvas.x - x;
  int prevy = ev->prev.canvas.y - y;
  //View* v = evas_object_data_get(o, "view");
  //
  Window* win = data;
  if (win->mouse_move) {
    win->mouse_move(win->data, "", ev->buttons, curx, cury, prevx, prevy, ev->timestamp);
  }

  /*
  const Evas_Modifier * mods = ev->modifiers;
  if ( evas_key_modifier_is_set(mods, "Control") &&
        (ev->buttons & 1) != 0 ) {
    //_handle_rect_select(v,ev);
    return;
  }
  */

  //Control* cl = v->control;
  //control_mouse_move(cl, ev);
}

static void
_mouse_down(void *data __UNUSED__, Evas *e __UNUSED__, Evas_Object *o, void *event_info)
{
  Evas_Event_Mouse_Down *ev = (Evas_Event_Mouse_Down*) event_info;
  //elm_object_focus_set(o, EINA_TRUE);

  Window* w = data;
  if (w->mouse_down) {
    w->mouse_down(w->data, "", ev->button, ev->canvas.x, ev->canvas.y, ev->timestamp);
  }

  /*
  View* v = evas_object_data_get(o, "view");
  Scene* s = v->context->scene;
  Control* cl = v->control;
  if (control_mouse_down(cl, ev))
    return;

  //if (ev->button == 3 ){
  const Evas_Modifier * mods = ev->modifiers;
  if ( ev->button == 1 && evas_key_modifier_is_set(mods, "Control")) {
    _makeRect(v, ev);
    return;
  }

  if (ev->button == 3) {
    Evas_Object* win = evas_object_top_get (evas_object_evas_get(o));
    Evas_Object* menu = _context_menu_create(win, v);
    evas_object_show(menu);
    elm_menu_move(menu, ev->canvas.x, ev->canvas.y);
    return;
  }
  */
}

static void
_mouse_up(void *data __UNUSED__, Evas *e __UNUSED__, Evas_Object *o, void *event_info)
{
  Evas_Event_Mouse_Up *ev = (Evas_Event_Mouse_Up*)event_info;
  //if (ev->button != 1) return;
  //printf("MOUSE: up   @ %4i %4i\n", ev->canvas.x, ev->canvas.y);

  Window* w = data;
  if (w->mouse_up) {
    w->mouse_up(w->data, "", ev->button, ev->canvas.x, ev->canvas.y, ev->timestamp);
  }

  //evas_object_hide(indicator[0]);
  //
  /*
  View* v = evas_object_data_get(o, "view");
  Evas_Object* rect = v->select_rect;
  evas_object_hide(rect);

  Control* cl = v->control;
  if (control_mouse_up(cl, ev))
  return;

  _mouse_up_select(v, ev);
  */
}



static void
_mouse_wheel(void *data __UNUSED__, Evas *e __UNUSED__, Evas_Object *o, void *event_info)
{
  Evas_Event_Mouse_Wheel *ev = (Evas_Event_Mouse_Wheel*) event_info;

  Window* w = data;
  if (w->mouse_wheel) {
    w->mouse_wheel(
          w->data,
          "",
          ev->direction,
          ev->z,
          ev->canvas.x,
          ev->canvas.y,
          ev->timestamp);
  }


  /*
  View* v = evas_object_data_get(o, "view");
  //float x = ev->cur.canvas.x - ev->prev.canvas.x;
  //float y = ev->cur.canvas.y - ev->prev.canvas.y;
  Vec3 axis = {0, 0, ev->z};
  axis = vec3_mul(axis, 1.5f);
  camera_pan(v->camera, axis);
  */
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


  evas_object_resize(win, 256, 256);
  //evas_object_resize(win, 64, 64);
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

static Evas_Object *create_edje(Evas_Object* win)
{
  Evas_Object *edje;
  Evas* canvas = evas_object_evas_get(win);

  edje = edje_object_add(canvas);
  if (!edje) {
    EINA_LOG_CRIT("could not create edje object!");
    return NULL;
   }

  if (!edje_object_file_set(edje, "edc/test.edj", "example_group")) {
    int err = edje_object_load_error_get(edje);
    const char *errmsg = edje_load_error_str(err);
    EINA_LOG_ERR("could not load 'my_group' from .edj file : %s",
          errmsg);

    evas_object_del(edje);
    return NULL;
   }

  return edje;
}

Window*
window_new()
{
  Window* w = calloc(1, sizeof *w);

  Evas_Object* win = elm_win_util_standard_add("simple_window", "simple_window");
  w->win = win;
  printf("pointer win %p \n", win);
  elm_win_autodel_set(win, EINA_TRUE);
  evas_object_smart_callback_add(win, "delete,request", simple_window_del, NULL);

  Eo* table = elm_table_add(win);
  evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //elm_win_resize_object_add(win, table);
  evas_object_show(table);
  elm_table_homogeneous_set(table, EINA_TRUE);

  Eo* edje = create_edje(win);
  w->edje = edje;
  elm_win_resize_object_add(win, edje);
  evas_object_move(edje, 0, 0);
  evas_object_resize(edje, 200, 200);
  evas_object_show(edje);
  edje_object_part_swallow(edje, "part_glview", table);
  //elm_win_resize_object_add(win, edje);
  //evas_object_size_hint_weight_set(edje, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

  /*
  Evas_Object* box = elm_box_add(win);
  evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //elm_win_resize_object_add(win, box);
  evas_object_show(box);
  */

  Evas_Object* glview = _create_glview(win);
  w->glview = glview;
  elm_table_pack(table, glview, 0, 0, 1, 5);
  //elm_table_pack(table, edje, 0, 5, 1, 5);
  //elm_table_pack(table, glview, 0, 0, 1, 1);
  //elm_box_pack_end(box, table);
  //elm_box_pack_end(box, glview);
  //elm_box_pack_end(box, edje);

  //JkTree* t = tree_widget_new(win);
  //edje_object_part_swallow(edje, "part_tree", t->root);


  //callbacks
  elm_glview_init_func_set(glview, _init_gl);
  elm_glview_del_func_set(glview, _del_gl);
  elm_glview_resize_func_set(glview, _resize_gl);
  elm_glview_render_func_set(glview, _draw_gl);

  //TODO
  //evas_object_event_callback_add(glview, EVAS_CALLBACK_DEL, _del, glview);
  evas_object_event_callback_add(glview, EVAS_CALLBACK_KEY_DOWN, _key_down, w);
  evas_object_event_callback_add(glview, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move, w);
  evas_object_event_callback_add(glview, EVAS_CALLBACK_MOUSE_DOWN, _mouse_down, w);
  evas_object_event_callback_add(glview, EVAS_CALLBACK_MOUSE_UP, _mouse_up, w);
  evas_object_event_callback_add(glview, EVAS_CALLBACK_MOUSE_WHEEL, _mouse_wheel, w);
  /*
  evas_object_event_callback_add(glview, EVAS_CALLBACK_MOUSE_IN, _mouse_in, NULL);
  */

  evas_object_resize(win, 456, 456);
  //evas_object_resize(win, 64, 64);
  evas_object_show(win);

  return w;
}


static rust_init_callback _init_callback_cb = 0;
static void* _init_callback_data = 0;

void init_callback_set(rust_init_callback cb, void * data)
{
  _init_callback_cb = cb;
  _init_callback_data = data;
}

bool init_callback_call()
{
  if (_init_callback_cb && _init_callback_data) {
    _init_callback_cb(_init_callback_data);
    return true;
  }

  return false;
}

JkTree* window_tree_new(Window* w)
{
  JkTree* t = tree_widget_new(w->win);
  edje_object_part_swallow(w->edje, "part_tree", t->root);
  return t;
}

JkProperty* window_property_new(Window* w)
{
  JkProperty* p = property_entry_new(w->win);
  edje_object_part_swallow(w->edje, "part_property_test", p->root);
  return p;
}

void window_button_new(Window* w)
{
  printf("create button\n");
  Eo* bt = eo_add(ELM_BUTTON_CLASS, w->win);
  //Eo* bt = elm_button_add(c->win);
  //eo_do(bt,
  //  evas_object_resize(100,100));
  evas_object_resize(bt, 100,100);
  evas_object_show(bt);

  int r,g,b,a;
  evas_object_color_get(bt, &r,&g,&b,&a);
  float f = 0.7f;
  r *= f;
  g *= f;
  b *= f;
  a *= f;

  evas_object_color_set(bt, r,g,b,a);
}

void
window_callback_set(
      Window* w,
      const void* data,
      window_mouse_down mouse_down,
      window_mouse_up mouse_up,
      window_mouse_move mouse_move,
      window_mouse_wheel mouse_wheel,
      window_key_down key_down
      )
{
  w->data = data;
  w->mouse_down = mouse_down;
  w->mouse_up = mouse_up;
  w->mouse_move = mouse_move;
  w->mouse_wheel = mouse_wheel;
  w->key_down = key_down;
}
