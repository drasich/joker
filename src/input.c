#include "input.h"

int jk_key_modifier_get(const Evas_Modifier* m)
{
  int mod_flag = 0;
  if (evas_key_modifier_is_set(m, "Shift")) {
    mod_flag |= 1 << 0;
  }
  if (evas_key_modifier_is_set(m, "Control")) {
    mod_flag |= 1 << 1;
  }
  return mod_flag;
}

