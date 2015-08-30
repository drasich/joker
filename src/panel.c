#include "panel.h"
#include "Evas.h"
#include "stdbool.h"

static const Evas_Smart_Cb_Description _smart_callbacks[] =
{
   {"christest", "i"},
   {NULL, NULL}
};

typedef struct _Smart_Panel Smart_Panel;
/*
 * This structure augments clipped smart object's instance data,
 * providing extra members required by our example smart object's
 * implementation.
 */
struct _Smart_Panel
{
   Evas_Object_Smart_Clipped_Data base;
   Evas_Object *rect;
   Evas_Object *edje;
   bool edge;
   bool moving;
   int x, y;
   int w, h;
};

EVAS_SMART_SUBCLASS_NEW("Smart_Panel", _smart_panel,
                        Evas_Smart_Class, Evas_Smart_Class,
                        evas_object_smart_clipped_class_get, _smart_callbacks);

static void
_ondown(void *data, Evas *e, Evas_Object *o, void *event_info)
{
    printf("yosh \n  ");
    Smart_Panel * priv = data;
    priv->moving = true;

   Evas_Event_Mouse_Down *ev = (Evas_Event_Mouse_Down*) event_info;

   Evas_Coord x, y, w, h;
   evas_object_geometry_get (o, &x, &y, &w, &h);

    priv->x = ev->canvas.x - x;
    priv->y = ev->canvas.y - y;
}

static void
_ondown_edge(
        void *data EINA_UNUSED,
        Evas_Object *o EINA_UNUSED,
        const char  *emission,
        const char  *source)

{
   //_sig_print(emission, source);
   printf("on down edge \n");
    Smart_Panel * priv = data;
    priv->moving = true;

   Evas_Coord x, y, w, h;
   evas_object_geometry_get (o, &x, &y, &w, &h);

   Evas_Coord mx, my;
   Evas* e = evas_object_evas_get(o);
   evas_pointer_output_xy_get(e, &mx, &my);

   priv->x = mx - x;
   priv->y = my - y;

}


static void
_onup(void *data, Evas *e, Evas_Object *o, void *event_info)
{
    printf("up \n  ");
    Smart_Panel * priv = data;
    priv->moving = false;
}

static void
_onup_edge(
        void *data EINA_UNUSED,
        Evas_Object *o EINA_UNUSED,
        const char  *emission,
        const char  *source)

{
   //_sig_print(emission, source);
   printf("on up edge \n");
    Smart_Panel * priv = data;
    priv->moving = false;
}



static void
_onmove(void *data, Evas *e, Evas_Object *o, void *event_info)
{
  Evas_Event_Mouse_Move *ev = (Evas_Event_Mouse_Move*) event_info;

  Evas_Coord x, y, w, h;
  evas_object_geometry_get (o, &x, &y, &w, &h);

  /*
  int curx = ev->cur.canvas.x - x;
  int cury = ev->cur.canvas.y - y;

  int prevx = ev->prev.canvas.x - x;
  int prevy = ev->prev.canvas.y - y;
  */

    Smart_Panel * priv = data;
    if (priv->moving) {
        int curx = ev->cur.canvas.x - priv->x;
		if (!priv->edge) {
			if (curx >0) {
        		evas_object_move(o, curx, ev->cur.canvas.y - priv->y);
			}
			else {
				priv->w = w;
				priv->h = h;

				priv->edge = true;
				//Evas_Coord cx,cy,cw,ch;
			 	//ecore_evas_geometry_get(e, &cx, &cy, &cw, &ch);
				Evas_Coord cx,cy,cw,ch;
			 	evas_output_size_get(e, &cw, &ch);

        		evas_object_move(o, 0, 0);
        		evas_object_resize(o, w, ch);
			}
		}
		else {
			if (curx >5) {
				priv->edge = false;
        		evas_object_move(o, curx, ev->cur.canvas.y - priv->y);
        		evas_object_resize(o, priv->w, priv->h);
			}
		}
    }

}

static void
_onmove_edge(
        void *data EINA_UNUSED,
        Evas_Object *o EINA_UNUSED,
        const char  *emission,
        const char  *source)

{
    printf("mouse move \n");
  Evas_Coord x, y, w, h;
  evas_object_geometry_get (o, &x, &y, &w, &h);

   Evas_Coord mx, my;
   Evas* e = evas_object_evas_get(o);
   evas_pointer_output_xy_get(e, &mx, &my);

    Smart_Panel * priv = data;
    if (priv->moving) {
        int curx = mx - priv->x;
		if (!priv->edge) {
			if (curx >0) {
        		evas_object_move(o, curx, my - priv->y);
			}
			else {
				priv->w = w;
				priv->h = h;

				priv->edge = true;
				//Evas_Coord cx,cy,cw,ch;
			 	//ecore_evas_geometry_get(e, &cx, &cy, &cw, &ch);
				Evas_Coord cx,cy,cw,ch;
			 	evas_output_size_get(e, &cw, &ch);

        		evas_object_move(o, 0, 0);
        		evas_object_resize(o, w, ch);
			}
		}
		else {
			if (curx >5) {
				priv->edge = false;
        		evas_object_move(o, curx, my - priv->y);
        		evas_object_resize(o, priv->w, priv->h);
			}
		}
    }
}

static Evas_Object *create_edje(Evas* e)
{
  Evas_Object *edje;

  edje = edje_object_add(e);
  if (!edje) {
    EINA_LOG_CRIT("could not create edje object!");
    return NULL;
   }

  if (!edje_object_file_set(edje, "edc/panel.edj", "main")) {
    int err = edje_object_load_error_get(edje);
    const char *errmsg = edje_load_error_str(err);
    EINA_LOG_ERR("could not load 'my_group' from .edj file : %s",
          errmsg);

    evas_object_del(edje);
    return NULL;
   }

  return edje;
}


static void
_smart_panel_add(Evas_Object *o)
{
   EVAS_SMART_DATA_ALLOC(o, Smart_Panel);

   /* call parent_sc->add() before member_adding the children, otherwise the
    * smart object's clipper won't be created yet, and the children won't be
    * clipped to it */
   _smart_panel_parent_sc->add(o);

   Evas* e = evas_object_evas_get(o);

   /* this is a border around the smart object's area, delimiting it */
   /*
   priv->border = evas_object_image_filled_add(e);
   evas_object_image_file_set(priv->border, "red.png", NULL);
   evas_object_image_border_set(priv->border, 3, 3, 3, 3);
   evas_object_image_border_center_fill_set(
     priv->border, EVAS_BORDER_FILL_NONE);
   evas_object_show(priv->border);
   evas_object_smart_member_add(priv->border, o);
   */

   Evas_Object *rect = evas_object_rectangle_add(e);
   evas_object_color_set(rect, rand() % 255, rand() % 255, rand() % 255, 255/2);
   //evas_object_color_set(rect, 255, 0, 0, 255);
   evas_object_resize(rect, 100, 400);
   //evas_object_show(rect);
   priv->rect = rect;
   evas_object_smart_member_add(rect, o);

   /*
   evas_object_event_callback_add(rect, EVAS_CALLBACK_MOUSE_DOWN, _ondown, priv);
   evas_object_event_callback_add(rect, EVAS_CALLBACK_MOUSE_UP, _onup, priv);
   evas_object_event_callback_add(rect, EVAS_CALLBACK_MOUSE_MOVE, _onmove, priv);
   */

   priv->edge = false;
   priv->moving = false;

  Eo* edje = create_edje(e);
  priv->edje = edje;
  evas_object_move(edje, 100, 100);
  evas_object_resize(edje, 100, 400);
  evas_object_show(edje);
  /*
  const Evas_Object* bar = edje_object_part_object_get(edje, "bar");

   evas_object_event_callback_add(bar, EVAS_CALLBACK_MOUSE_DOWN, _ondown, priv);
   evas_object_event_callback_add(bar, EVAS_CALLBACK_MOUSE_UP, _onup, priv);
   evas_object_event_callback_add(bar, EVAS_CALLBACK_MOUSE_MOVE, _onmove, priv);
   */
  edje_object_signal_callback_add(edje, "mouse,down,1", "bar",_ondown_edge, priv);
  edje_object_signal_callback_add(edje, "mouse,move", "bar",_onmove_edge, priv);
  edje_object_signal_callback_add(edje, "mouse,up,1", "bar",_onup_edge, priv);



}

static void
_smart_panel_del(Evas_Object *o)
{
  Smart_Panel * priv = evas_object_smart_data_get(o);

   if (priv->rect) {
       // _evas_smart_example_child_callbacks_unregister(priv->rect);
        priv->rect = NULL;
   }

   _smart_panel_parent_sc->del(o);
}

static void
_smart_panel_resize(Evas_Object *o,
                                 Evas_Coord w,
                                 Evas_Coord h)
{
   Evas_Coord ow, oh;
   evas_object_geometry_get(o, NULL, NULL, &ow, &oh);
   printf("resize to %d, %d \n", ow, oh);
   if ((ow == w) && (oh == h)) return;

   /* this will trigger recalculation */
   evas_object_smart_changed(o);
}

static void
_smart_panel_calculate(Evas_Object *o)
{
   Evas_Coord x, y, w, h;

   Smart_Panel * priv = evas_object_smart_data_get(o);
   if (!priv) return;

   evas_object_geometry_get(o, &x, &y, &w, &h);

   printf("recalculate to %d, %d, %d, %d \n", x, y, w, h);

   if (priv->edge) {
   	evas_object_resize(priv->rect, w/4, h);
   	evas_object_move(priv->rect, 0, 0);
   	evas_object_resize(priv->edje, w/4, h);
   	evas_object_move(priv->edje, 0, 0);
   }
   else {
   	evas_object_resize(priv->rect, 200, 400);
   	evas_object_resize(priv->edje, 200, 400);
   }

}

static void
_smart_panel_smart_set_user(Evas_Smart_Class *sc)
{
   /* specializing these two */
   sc->add = _smart_panel_add;
   sc->del = _smart_panel_del;;

   /* clipped smart object has no hook on resizes or calculations */
   sc->resize = _smart_panel_resize;
   sc->calculate = _smart_panel_calculate;
}

// smart panel interface
//
//
//
//
Evas_Object *
smart_panel_add(Evas *evas)
{
   return evas_object_smart_add(evas, _smart_panel_smart_class_new());
}

void
smart_panel_content_set(Evas_Object *o, Evas_Object* content)
{
   Smart_Panel * priv = evas_object_smart_data_get(o);
   if (!priv) return;

   edje_object_part_swallow(priv->edje, "content", content);

}





