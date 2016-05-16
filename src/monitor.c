#include "Elementary.h"

typedef void (*MonitorCallback)(void* data, const char* path, int event);

struct _CbData
{
  MonitorCallback cb;
  void* data;
};

static void _monitor_add(void *data, Ecore_File_Monitor *em, Ecore_File_Event event, const char *path)
{
  printf("file event : %d, path %s \n", event, path);
  struct _CbData* cbdata = data;
  cbdata->cb(cbdata->data, path, event);
}


void jk_monitor_add(MonitorCallback cb, void* data, const char* path)
{
  //ecore_file_init(); //TODO ecore_file_shutdown

  struct _CbData* cbdata = calloc(1, sizeof *cbdata);
  cbdata->cb = cb;
  cbdata->data = data;
  printf("TODO ERASE data");

  Ecore_File_Monitor * efm = ecore_file_monitor_add(path,
        _monitor_add,
        cbdata
        );
}
