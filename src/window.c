#include "glview.h"
#include "shader.h"
#include "buffer.h"
#include "drawable.h"

static void
_init_gl(Evas_Object *obj)
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_STENCIL_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepthf(1.0f);
  glClearStencil(0);
}

static void
_del_gl(Evas_Object *obj)
{
  //TODO delete stuff
}

static void
_resize_gl(Evas_Object *obj)
{
  int w, h;
  elm_glview_size_get(obj, &w, &h);

  // GL Viewport stuff. you can avoid doing this if viewport is all the
  // same as last frame if you want
  glViewport(0, 0, w, h);

}

static Shader* lastshader = NULL;
static void
_shader_request_handle()
{
  Eina_List *l;
  ShaderRequest *sr;
  Eina_List* shader_requests = shader_request_get();
  EINA_LIST_FOREACH(shader_requests, l, sr) {
    Shader* ss = shader_init_string(sr->vert, sr->frag, sr->att);
    shader_use(ss);
    lastshader = ss;
    sr->cb(sr->material, 55, ss);
  }

  EINA_LIST_FREE(shader_requests, sr){
   free(sr);
  }

  eina_list_free(shader_requests);
}

static Buffer* lastbuf = NULL;
static void
_buffer_request_handle()
{
  Eina_List *l;
  BufferRequest* br;
  Eina_List* buffer_requests = buffer_request_get();
  EINA_LIST_FOREACH(buffer_requests, l, br) {
    //printf("init shader : %s, %s \n", request->vert, request->frag);
    Buffer* bs = buffer_init(br->vertex, br->count);
    lastbuf = bs;
    br->cb(br->mesh, 66, bs);
  }

  EINA_LIST_FREE(buffer_requests, br){
   free(br);
  }
  eina_list_free(buffer_requests);

}

static void
_draw_handle()
{
  /*
  Eina_List *l;
  DrawRequest* dr;
  Eina_List* draw_requests = draw_request_get();
  EINA_LIST_FOREACH(draw_requests, l, dr) {
    shader_draw(dr->shader, dr->buffer);
  }

  EINA_LIST_FREE(buffer_requests, br){
   free(br);
  }
  eina_list_free(buffer_requests);
  */

  const Drawable* dr = getZADATA();
  if (dr == NULL) return;
  else
   {
    shader_draw(dr->shader, dr->buffer);
    return;
   }

  /*

  if (lastshader && lastbuf){
    shader_draw(lastshader, lastbuf);
  }
  */

}

static void
_draw_gl(Evas_Object *obj)
{
  int w, h;
  elm_glview_size_get(obj, &w, &h);

  glViewport(0, 0, w, h);

  glClearColor(0.2, 0.4, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _shader_request_handle();
  _buffer_request_handle();

  _draw_handle();

  glFinish();
}



static void
simple_window_del(void *data, Evas_Object *obj, void *event_info)
{
  elm_exit();
}


void
create_simple_window()
{
  Evas_Object *win;
  win = elm_win_util_standard_add("simple_window", "simple_window");
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
  evas_object_show(win);
}

void create_glview()
{
  eina_init();
  eet_init();
  srand (time(NULL));

  elm_config_preferred_engine_set("opengl_x11");
  elm_config_focus_highlight_animate_set(EINA_TRUE);
  elm_config_focus_highlight_enabled_set(EINA_TRUE);
  create_simple_window();
}

EAPI_MAIN int
simple_window_main(int argc, char **argv)
{
  create_glview();
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

void
simple_window_init()
{
  eina_init();
  shader_request_init();
}

