#include "command.h"
#define __UNUSED__

static Elm_Genlist_Item_Class *itc1;

static char *
_gl_cmd_text_get(void *data, Evas_Object *obj, const char *part __UNUSED__)
{
  CommandCallbackData* ccd = data;
  return strdup(ccd->name);
}

static Eina_Bool
_gl_cmd_state_get(void *data __UNUSED__, Evas_Object *obj __UNUSED__, const char *part __UNUSED__)
{
   return EINA_FALSE;
}

static void _gl_cmd_del(void *data __UNUSED__, Evas_Object *obj __UNUSED__)
{
   //printf("item deleted.\n");
}

static void
_gl_cmd_sel(void *data, Evas_Object *obj __UNUSED__, void *event_info)
{
}

static void
_gl_cmd_pressed(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Elm_Object_Item *eoi = event_info;

   CommandCallbackData* ccd = elm_object_item_data_get(eoi);
   ccd->fn(ccd->data);
}

static void
_entry_cmd_activated(void *data, Evas_Object *obj, void *event)
{
  JkCommand* com = data;
  Elm_Object_Item* eoi = elm_genlist_selected_item_get(com->gl);

  if (eoi) {
    CommandCallbackData* ccd = elm_object_item_data_get(eoi);
    ccd->fn(ccd->data);
  }
  else {
    printf("no item selected\n");
  }
}

static void
_item_add(JkCommand* command, CommandCallbackData* ccd)
{
  const Elm_Genlist_Item_Class* class = itc1;
  Elm_Genlist_Item_Type type = ELM_GENLIST_ITEM_NONE;

  Elm_Object_Item* eoi = elm_genlist_item_append(
        command->gl,
        class,
        ccd,
        NULL,
        type,
        _gl_cmd_sel,
        command);

  ccd->item = eoi;
  command->visible = eina_list_append(command->visible, ccd);
}

static void
_item_del(JkCommand* command, CommandCallbackData* ccd)
{
  elm_object_item_del(ccd->item);
}

bool starts_with(const char *str, const char *other)
{
  size_t len_str = strlen(str);
  size_t len_other = strlen(other);
  return len_str < len_other ? false : strncmp(other, str, len_other) == 0;
}

static void
_entry_cmd_changed(void *data, Evas_Object *obj, void *event)
{
  const char* value = elm_object_text_get(obj);
  JkCommand* com = data;

  Eina_List *l;
  Eina_List *l_next;
  CommandCallbackData *ccd;

  printf("......................000000000000 entry changed %s \n", value);

  EINA_LIST_FOREACH_SAFE(com->visible, l, l_next, ccd) {
    if (!starts_with(ccd->name, value)) {
      com->visible = eina_list_remove_list(com->visible, l);
      _item_del(com, ccd);
      printf("......................del %s \n", ccd->name);
      com->hidden = eina_list_append(com->hidden, ccd);
    }
  }

  EINA_LIST_FOREACH_SAFE(com->hidden, l, l_next, ccd) {
    if (starts_with(ccd->name, value)) {
      com->hidden = eina_list_remove_list(com->hidden, l);
      //com->visible = eina_list_append(com->visible, ccd);
      _item_add(com, ccd);
      printf(".........................add %s \n", ccd->name);
    }
  }

  if (strcmp(value, "")) {
    Elm_Object_Item* item = elm_genlist_first_item_get(com->gl);
    if (item) {
      elm_genlist_item_selected_set(item, EINA_TRUE);
      elm_object_focus_set(obj, EINA_TRUE);
    }
  }

  //elm_genlist_realized_items_update(com->gl);
}

static void 
_cmd_list(JkCommand* cmd, Evas_Object* win, Evas_Object* bx)
{
  printf("tree widget new !!win: %p \n",win);
  Evas_Object *gli;

  gli = elm_genlist_add(win);
  cmd->gl = gli;
  evas_object_size_hint_align_set(gli, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(gli, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  //elm_genlist_homogeneous_set(gli, EINA_TRUE);
  elm_genlist_focus_on_selection_set(gli, EINA_FALSE);
  evas_object_show(gli);

  itc1 = elm_genlist_item_class_new();
  itc1->item_style     = "default";
  itc1->func.text_get = _gl_cmd_text_get;
  itc1->func.content_get  = NULL;
  itc1->func.state_get = _gl_cmd_state_get;
  itc1->func.del       = _gl_cmd_del;

  elm_genlist_item_class_ref(itc1);
  //elm_genlist_item_class_free(itc1);

  //TODO
  //evas_object_smart_callback_add(gli, "selected", gl4_select, t);
  evas_object_smart_callback_add(gli, "pressed", _gl_cmd_pressed, cmd);
  //elm_scroller_content_min_limit(gli, true, true);
  //evas_object_size_hint_min_set(gli, 256, 256);
  //evas_object_resize(gli, 256, 256);

  //elm_box_pack_end(bx, gli);
}


JkCommand* widget_command_new(Evas_Object* win)
{
  JkCommand *c = calloc(1, sizeof *c);

  Evas_Object* popup = elm_popup_add(win);
  elm_object_style_set(popup, "transparent");
  c->root = popup;

  Evas_Object *bx, *entry;
  bx = elm_box_add(win);
  c->box = bx;
  evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(bx);
  elm_box_horizontal_set(bx, EINA_FALSE);

  entry = elm_entry_add(win);
  evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, 0);
  //evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_box_pack_end(bx, entry);
  evas_object_show(entry);

  evas_object_smart_callback_add(entry, "activated", _entry_cmd_activated, c);
  evas_object_smart_callback_add(entry, "changed", _entry_cmd_changed, c);

  //elm_entry_scrollable_set(entry, EINA_TRUE);
  evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, 0.5);
  elm_object_text_set(entry, "type something");
  elm_entry_single_line_set(entry, EINA_TRUE);
  elm_entry_select_all(entry);

  Evas_Object *layout;
  layout = elm_layout_add(win);
  elm_layout_file_set(layout, "edc/popup.edj", "example_group");
  evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

  _cmd_list(c, win, bx);

  evas_object_show(layout);
  elm_object_part_content_set(layout, "part_list", c->gl);
  elm_box_pack_end(bx, layout);

  elm_object_part_content_set(popup, "default", bx);

  c->visible = NULL;
  c->hidden = NULL;

  return c;
}

static void
_command_callback(
      void *data,
      Evas_Object *obj,
      void *event_info)
{
  CommandCallbackData* ccd = data;
  ccd->fn(ccd->data);
}

void
command_new(
      JkCommand* command,
      const char* name,
      void* data,
      command_callback fn)
{
  Evas_Object* win = command->root;
  Evas_Object* box = command->box;

  CommandCallbackData* ccd = calloc(1, sizeof *ccd);
  ccd->name = strdup(name);
  ccd->data = data;
  ccd->fn = fn;

  //_item_add(command, ccd);
  command->hidden = eina_list_append(command->hidden, ccd);
}

void
command_show(JkCommand* command)
{
  if (evas_object_visible_get(command->root)) {
    evas_object_hide(command->root);
  }
  else {
    evas_object_show(command->root);
  }
}
