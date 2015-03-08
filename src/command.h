#ifndef __ui_command__
#define __ui_command__
#include "stdbool.h"
#include <Elementary.h>
#include <Eina.h>

typedef struct _Command JkCommand;

struct _Command
{
  Evas_Object* root;
  Evas_Object* box;
  Evas_Object* gl;
};

JkCommand* widget_command_new(Evas_Object* win);

typedef void (*command_callback)(void *data);

typedef struct _CommandCallbackData CommandCallbackData;
struct _CommandCallbackData
{
  const char* name;
  void* data;
  command_callback fn;
};

void command_new(
      JkCommand* command,
      const char* name,
      void* data,
      command_callback fn);

void command_show(JkCommand* command);

#endif

