#ifndef BKMAP_H_
#define BKMAP_H_

#include "error.h"
#include "scl/sclstr.h"
#include <stdio.h>

#define BK_FILE_ENV "BK_FILE"
#define BK_VAR_PRE '$'

typedef struct BkMapEntry {
  Str name;
  Str value;
  Str desc;
  Error err;
} BkMapEntry;

#define RL_MAX 9
typedef struct ReplaceList {
  char *data[RL_MAX];
  usize len;
} ReplaceList;

BkMapEntry bk_init();
BkMapEntry bk_from_raw(char *input);
Error bk_list(FILE *f);
Error bk_find(FILE *f, char *name, ReplaceList *rl);

ReplaceList rl_init();
void rl_insert(ReplaceList *rl, char *str);
char *rl_get(ReplaceList *rl, usize index);
void rl_free(ReplaceList *rl);

FILE *bk_open_file();
void bk_close_file(FILE *f);

#endif
