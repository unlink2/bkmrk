#ifndef BKMAP_H_
#define BKMAP_H_

#include "error.h"
#include "scl/sclstr.h"
#include <stdio.h>

#define BK_FILE_ENV "BK_FILE"

typedef struct BkMapEntry {
  Str name;
  Str value;
  Str desc;
  Error err;
} BkMapEntry;

BkMapEntry bk_init();
BkMapEntry bk_from_raw(char *input);
Error bk_list(FILE *f);
Error bk_find(FILE *f, char *name);

FILE *bk_open_file();
void bk_close_file(FILE *f);

#endif
