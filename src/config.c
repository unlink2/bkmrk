#include "config.h"
#include "bkmap.h"
#include <stdlib.h>

Config config;
SclAlloc alloc;

Config config_init() {
  Config c = {"", "\n", ':', bk_open_file(), OK};
  alloc = scl_alloc_init(malloc, free);
  return c;
}

void config_free(Config *c) { bk_close_file(c->input); }
