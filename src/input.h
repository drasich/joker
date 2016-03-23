#ifndef __input__
#define __input__
#include "Elementary.h"
#include "stdbool.h"

typedef void (*jk_mouse_down)(
      const void* data,
      int mod_flag,
      int buttons,
      int x,
      int y,
      int timestamp
      );
typedef void (*jk_mouse_up)(
      const void* data,
      int mod_flag,
      int buttons,
      int x,
      int y,
      int timestamp
      );
typedef void (*jk_mouse_move)(
      const void* data,
      int mod_flag,
      int button,
      int cur_x,
      int cur_y,
      int prev_x,
      int prev_y,
      int timestamp
      );
typedef void (*jk_mouse_wheel)(
      const void* data,
      int mod_flag,
      int direction,
      int z,
      int x,
      int y,
      int timestamp
      );
typedef void (*jk_key_down)(
      const void* data,
      int mod_flag,
      char* keyname,
      const char* key,
      unsigned int keycode,
      int timestamp
      );

int jk_key_modifier_get(const Evas_Modifier* m);

#endif
