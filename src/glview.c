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
  ecore_animator_del(ani);
}

Evas_Object*
_create_glview(Evas_Object* win)
{
  Evas_Object *glview;

  glview = elm_glview_add(win);

  Ecore_Animator *ani = ecore_animator_add(_anim, glview);
  evas_object_data_set(glview, "ani", ani);

  if (!gl)
  gl = elm_glview_gl_api_get(glview);

  evas_object_size_hint_align_set(glview, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(glview, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_glview_mode_set(glview, ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH);
  elm_glview_resize_policy_set(glview, ELM_GLVIEW_RESIZE_POLICY_RECREATE);
  //elm_glview_resize_policy_set(glview, ELM_GLVIEW_RESIZE_POLICY_SCALE);
  //elm_glview_render_policy_set(glview, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);
  elm_glview_render_policy_set(glview, ELM_GLVIEW_RENDER_POLICY_ALWAYS);
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

  Evas_Object* gl =  _create_glview(win);
  evas_object_data_set(gl, "cb_data", data);
  evas_object_data_set(gl, "cb_init", init);
  evas_object_data_set(gl, "cb_draw", draw);
  evas_object_data_set(gl, "cb_resize", resize);
  elm_win_resize_object_add(win, gl);

  jgl->glview = gl;

  return jgl;
}

