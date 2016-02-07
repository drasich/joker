#include "glview.h"
#define __UNUSED__

Eina_Bool
_anim(void *data)
{
   elm_glview_changed_set(data);
   return EINA_TRUE;
}

void
_del(void *data __UNUSED__, Evas *evas __UNUSED__, Evas_Object *obj, void *event_info __UNUSED__)
{
  EINA_LOG_DBG("del ani");
  Ecore_Animator *ani = evas_object_data_get(obj, "ani");
  if (ani) {
    ecore_animator_del(ani);
  }
}

static void
_init_gl(Evas_Object *obj)
{
  void* data = evas_object_data_get(obj, "cb_data");
  rust_callback init = evas_object_data_get(obj, "cb_init");

  cypher_init(init, data);
}

static void
_del_gl(Evas_Object *obj)
{
  cypher_del();
  Ecore_Animator *ani = evas_object_data_get(obj, "ani");
  if (ani) {
    ecore_animator_del(ani);
  }

}

static void
_resize_gl(Evas_Object *obj)
{
  int w, h;
  elm_glview_size_get(obj, &w, &h);

  void* data = evas_object_data_get(obj, "cb_data");
  resize_callback resize = evas_object_data_get(obj, "cb_resize");

  cypher_resize(resize, data, w, h);
}

static void
_draw_gl(Evas_Object *obj)
{
  int w, h;
  elm_glview_size_get(obj, &w, &h);

  void* data = evas_object_data_get(obj, "cb_data");
  rust_callback draw = evas_object_data_get(obj, "cb_draw");

  cypher_draw(draw, data, w, h);
}


Evas_Object*
_create_glview(Evas_Object* win, bool auto_refresh)
{
  Evas_Object *glview;

  glview = elm_glview_add(win);

  elm_glview_init_func_set(glview, _init_gl);
  elm_glview_del_func_set(glview, _del_gl);
  elm_glview_resize_func_set(glview, _resize_gl);
  elm_glview_render_func_set(glview, _draw_gl);

  if (auto_refresh) {
    Ecore_Animator *ani = ecore_animator_add(_anim, glview);
    evas_object_data_set(glview, "ani", ani);
  }

  if (!gl)
  gl = elm_glview_gl_api_get(glview);

  evas_object_size_hint_align_set(glview, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(glview, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_glview_mode_set(glview, ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH);
  elm_glview_resize_policy_set(glview, ELM_GLVIEW_RESIZE_POLICY_RECREATE);
  //elm_glview_resize_policy_set(glview, ELM_GLVIEW_RESIZE_POLICY_SCALE);
  elm_glview_render_policy_set(glview, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);
  //elm_glview_render_policy_set(glview, ELM_GLVIEW_RENDER_POLICY_ALWAYS);
  evas_object_show(glview);

  elm_object_focus_set(glview, EINA_TRUE);
  return glview;
}

JkGlview* jk_glview_new(
      Evas_Object* win,
      void* data,
      rust_callback init,
      rust_callback draw,
      resize_callback resize)
{
  JkGlview* jgl = calloc(1, sizeof *jgl);

  Evas_Object* gl =  _create_glview(win, true);

  evas_object_data_set(gl, "cb_data", data);
  evas_object_data_set(gl, "cb_init", init);
  evas_object_data_set(gl, "cb_draw", draw);
  evas_object_data_set(gl, "cb_resize", resize);
  elm_win_resize_object_add(win, gl);

  jgl->glview = gl;

  return jgl;
}

void jk_glview_request_update(JkGlview* jgl)
{
   elm_glview_changed_set(jgl->glview);
}

