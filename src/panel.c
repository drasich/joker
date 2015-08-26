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
   bool edge;
};

EVAS_SMART_SUBCLASS_NEW("Smart_Panel", _smart_panel,
                        Evas_Smart_Class, Evas_Smart_Class,
                        evas_object_smart_clipped_class_get, _smart_callbacks);

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
   evas_object_color_set(rect, rand() % 255, rand() % 255, rand() % 255, 255);
   evas_object_resize(rect, 100, 400);
   evas_object_show(rect);
   priv->rect = rect;
   evas_object_smart_member_add(rect, o);

   priv->edge = false;

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
   }
   else {
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





