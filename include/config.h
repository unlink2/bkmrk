#ifndef CONFIG_H_
#define CONFIG_H_

#include <scl/sclalloc.h>
#include <stdio.h>
#include "bkmap.h"
#include "error.h"

typedef struct Config {
  const char *pre;
  const char *post;
  char separator;
  ReplaceList rl;

  FILE *input;
  Error err;
} Config;

extern Config config;
extern SclAlloc alloc;

Config config_init();

void config_free(Config *c);

#endif
