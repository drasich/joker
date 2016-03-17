
typedef void (MonitorCallback)(void* data, const char* path, int event);

void jk_monitor_add(MonitorCallback cb, void* data, const char* path);

