/* Enable access to unstable EFL API that are still in beta */
#define EFL_BETA_API_SUPPORT 1

/* Enable access to unstable EFL EO API. */
#define EFL_EO_API_SUPPORT 1

#include "glview.h"
#include "shader.h"
#include "buffer.h"
#include "cypher.h"
#include "window.h"
#include "panel.h"

#define __UNUSED__

static void
simple_window_del(void *data, Evas_Object *obj, void *event_info)
{
  elm_exit();
}

static int _modifier_get(const Evas_Modifier* m)
{
  int mod_flag = 0;
  if (evas_key_modifier_is_set(m, "Shift")) {
    mod_flag |= 1 << 0;
  }
  if (evas_key_modifier_is_set(m, "Control")) {
    mod_flag |= 1 << 1;
  }
  return mod_flag;
}


static void
_key_down(void *data __UNUSED__, Evas *e __UNUSED__, Evas_Object *o __UNUSED__, void *event_info)
{
  Evas_Event_Key_Down *ev = (Evas_Event_Key_Down*)event_info;
  EINA_LOG_DBG("KEY: down, keyname: %s , key %s", ev->keyname, ev->key);
  //printf("KEY: down, keyname: %s , key %s\n", ev->keyname, ev->key);

  Window* w = data;
  if (w->key_down) {
    w->key_down(
          w->data,
          _modifier_get(ev->modifiers),
          ev->keyname,
          ev->key,
          ev->timestamp);
  }

  //View* v = evas_object_data_get(o, "view");
  //Control* cl = v->control;
  //control_key_down(cl, ev);
}
static void
_mouse_move(void *data __UNUSED__, Evas *e __UNUSED__, Evas_Object *o, void *event_info)
{
  elm_object_focus_set(o, EINA_TRUE);
  Evas_Event_Mouse_Move *ev = (Evas_Event_Mouse_Move*) event_info;

  Evas_Coord x, y, w, h;
  evas_object_geometry_get (o, &x, &y, &w, &h);
  int curx = ev->cur.canvas.x - x;
  int cury = ev->cur.canvas.y - y;

  int prevx = ev->prev.canvas.x - x;
  int prevy = ev->prev.canvas.y - y;
  //View* v = evas_object_data_get(o, "view");
  //
  int mod_flag = _modifier_get(ev->modifiers);

  Window* win = data;
  if (win->mouse_move) {
    win->mouse_move(
          win->data,
          mod_flag,
          ev->buttons,
          curx,
          cury,
          prevx,
          prevy,
          ev->timestamp);
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
  elm_object_focus_set(o, EINA_TRUE);

  Window* w = data;
  if (w->mouse_down) {
    w->mouse_down(
          w->data,
          _modifier_get(ev->modifiers),
          ev->button,
          ev->canvas.x,
          ev->canvas.y,
          ev->timestamp);
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
    w->mouse_up(
          w->data,
          _modifier_get(ev->modifiers),
          ev->button,
          ev->canvas.x,
          ev->canvas.y,
          ev->timestamp);
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
          _modifier_get(ev->modifiers),
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
  Evas_Object* win = elm_win_util_standard_add("3d view", "3d view");
  elm_win_autodel_set(win, EINA_TRUE);
  evas_object_smart_callback_add(win, "delete,request", simple_window_del, NULL);

  Evas_Object* box = elm_box_add(win);
  evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, box);
  evas_object_show(box);

  Evas_Object* glview = _create_glview(win);
  elm_box_pack_end(box, glview);

  evas_object_resize(win, 256, 256);
  //evas_object_resize(win, 64, 64);
  evas_object_show(win);
}

void jk_init()
{
  eina_init();
  eet_init();
  srand (time(NULL));

  //elm_config_preferred_engine_set("opengl_x11");
  elm_config_accel_preference_set("opengl");
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
  exit_callback_call();
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

static Evas_Object* _create_select_rect(Evas_Object* parent)
{
  Evas* e = evas_object_evas_get(parent);
  Evas_Object* r = evas_object_rectangle_add(e);
  int a = 15;
  evas_object_color_set(r, a, a, a, a);
  evas_object_resize(r, 0,0);
  evas_object_hide(r);
  return r;
}

Window*
window_new()
{
  Window* w = calloc(1, sizeof *w);

  Evas_Object* win = elm_win_util_standard_add("3d view", "3d view");
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

  w->rect = _create_select_rect(win);

  evas_object_resize(win, 400, 256);
  //evas_object_resize(win, 864, 434);
  evas_object_show(win);


  return w;
}

static void
_close_window(void *data, Evas_Object *obj, void *event_info)
{
  rust_elm_callback cb = evas_object_data_get(obj, "cb");
  void *cb_data = evas_object_data_get(obj, "cb_data");

  if (cb != NULL) {
    cb(cb_data);
  }
}


Evas_Object*
jk_window_new(rust_elm_callback cb, const void* cb_data)
{
  Evas_Object* win = elm_win_util_standard_add("3d jk view", "3d jk view");
  elm_win_autodel_set(win, EINA_TRUE);
  evas_object_smart_callback_add(win, "delete,request", _close_window, NULL);
  evas_object_data_set(win, "cb", cb);
  evas_object_data_set(win, "cb_data", cb_data);

  evas_object_resize(win, 64, 64);
  evas_object_show(win);

  return win;
}



static rust_elm_callback _init_callback_cb = 0;
static void* _init_callback_data = 0;

void init_callback_set(rust_elm_callback cb, void * data)
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

static rust_elm_callback _exit_callback_cb = 0;
static void* _exit_callback_data = 0;

void exit_callback_set(rust_elm_callback cb, void * data)
{
  _exit_callback_cb = cb;
  _exit_callback_data = data;
}

bool exit_callback_call()
{
  if (_exit_callback_cb && _exit_callback_data) {
    _exit_callback_cb(_exit_callback_data);
    return true;
  }

  return false;
}


JkTree* window_tree_new(Window* w)
{
  /*
  JkTree* t = tree_widget_new(w->win);
  edje_object_part_swallow(w->edje, "part_tree", t->root);
  return t;
  */

  Evas_Object* win = elm_win_add(w->win, "tree", ELM_WIN_BASIC);
  elm_win_title_set(win, "scene tree");
  //Evas_Object* win = elm_win_util_standard_add("genlist3", "Genlist 3");

  Evas_Object* bg = elm_bg_add(win);
  evas_object_show(bg);
  evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, bg);

  JkTree* t = tree_widget_new(win);
  evas_object_size_hint_weight_set(t->root, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, t->root);
  evas_object_resize(win, 256, 256);
  evas_object_show(win);

  return t;
}

JkAction* window_action_new(Window* w)
{
  Evas_Object* win = elm_win_add(w->win, "action", ELM_WIN_BASIC);
  elm_win_title_set(win, "action");

  Evas_Object* bg = elm_bg_add(win);
  evas_object_show(bg);
  evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, bg);

  JkAction* a = widget_action_new(win);
  evas_object_size_hint_weight_set(a->root, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, a->root);
  //evas_object_resize(win, 256, 256);
  evas_object_show(win);

  return a;
}

JkCommand* window_command_new(Window* w)
{
  /*
  Evas_Object* win = elm_win_add(w->win, "command", ELM_WIN_BASIC);
  elm_win_title_set(win, "command");

  Evas_Object* bg = elm_bg_add(win);
  evas_object_show(bg);
  evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, bg);
  */

  Evas_Object* win = w->win;

  JkCommand* c = widget_command_new(win);
  evas_object_size_hint_weight_set(c->root, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //elm_win_resize_object_add(win, c->root);
  //evas_object_resize(win, 256, 256);
  //evas_object_show(win);
  //


  return c;
}



JkProperty* window_property_new(Window* w)
{
  JkProperty* p = property_entry_new(w->win);
  edje_object_part_swallow(w->edje, "part_property_test", p->root);
  return p;
}

JkPropertySet* jk_property_set_new(Window* w)
{
  JkPropertySet* ps = property_set_new(w->win);
  //edje_object_part_swallow(w->edje, "part_property_test", ps->root);
  return ps;
}

JkPropertyList* jk_property_list_new(Window* w)
{
  /*
  JkPropertyList* pl = property_list_new(w->win);
  edje_object_part_swallow(w->edje, "part_property_test", pl->root);
  return pl;
  */

    /*
  Evas_Object* win = elm_win_add(w->win, "property", ELM_WIN_BASIC);
  elm_win_title_set(win, "property");

  Evas_Object* bg = elm_bg_add(win);
  evas_object_show(bg);
  evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, bg);

  JkPropertyList* p = property_list_new(win);
  evas_object_size_hint_weight_set(p->root, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_win_resize_object_add(win, p->root);
  evas_object_resize(win, 256, 256);
  evas_object_show(win);

  */

    //chris
  //Evas* e = evas_object_evas_get(w->win);
  //Evas_Object* panel = smart_panel_add(e);
  Evas_Object* panel = layout_panel_add(w->win);
  evas_object_move(panel, 100, 100);
  //evas_object_show(panel);

  JkPropertyList* p = property_list_new(panel);
  evas_object_size_hint_weight_set(p->root, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_resize(panel, 256, 256);
  //smart_panel_content_set(panel, p->root);
  elm_object_part_content_set(panel, "content", p->root);
  p->win = panel;

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

void
window_rect_visible_set(Window* w, bool b)
{
  if (b) {
    evas_object_show(w->rect);
  }
  else {
    evas_object_hide(w->rect);
  }
}

void
window_rect_set(Window* win, float x, float y, float w, float h)
{
  evas_object_geometry_set(win->rect, x, y, w, h);
}

void tmp_func(
      Window* window,
      void* data,
      rust_callback init,
      rust_callback draw,
      resize_callback resize)
{
  Evas_Object* gl = window->glview;

  evas_object_data_set(gl, "cb_data", data);
  evas_object_data_set(gl, "cb_init", init);

  evas_object_data_set(gl, "cb_draw", draw);
  evas_object_data_set(gl, "cb_resize", resize);
}

void jk_exit()
{
  elm_exit();
}
