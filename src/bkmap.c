#include "bkmap.h"
#include "config.h"
#include <scl/sclstr.h>
#include <scl/scllog.h>
#include <scl/sclmem.h>
#include <stdlib.h>

BkMapEntry bk_init() {
  BkMapEntry entry;
  scl_memset(&entry, 0, sizeof(entry));
  entry.desc = str_init("", 0);
  entry.name = str_init("", 0);
  entry.value = str_init("", 0);
  return entry;
}

bool bk_at_end(const char i) { return i == '\0' || i == '\n' || i == '\r'; }

char *bk_next(Str *s, char *input) {
  char *begin = input;
  while (*input != config.separator && !bk_at_end(*input)) {
    input++;
  }
  usize len = input - begin;
  if (len > 0) {
    *s = str_init(begin, len);
  }

  return input + 1;
}

BkMapEntry bk_from_raw(char *input) {
  BkMapEntry entry = bk_init();

  // go until detecting a : or eof
  input = bk_next(&entry.name, input);
  input = bk_next(&entry.value, input);
  input = bk_next(&entry.desc, input);
  entry.err = OK;
  return entry;
}

Error bk_list(FILE *f) {
  if (f == NULL) {
    return ERR_FILE_NOT_FOUND;
  }
  fseek(f, 0, 0);
  char *line = NULL;
  usize len = 0;
  usize read = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    BkMapEntry entry = bk_from_raw(line);
    if (entry.err) {
      return entry.err;
    }
    scl_log_output("" str_fmt "|\t" str_fmt "|\t" str_fmt "\n",
                   str_out(entry.name), str_out(entry.value),
                   str_out(entry.desc));
  }

  alloc.free(line);

  return OK;
}

Error bk_find(FILE *f, char *name, ReplaceList *rl) {
  if (f == NULL) {
    return ERR_FILE_NOT_FOUND;
  }
  fseek(f, 0, 0);
  char *line = NULL;
  usize len = 0;
  usize read = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    BkMapEntry entry = bk_from_raw(line);
    if (entry.err) {
      return entry.err;
    }
    if (str_eq_raw(entry.name, name)) {
      // print the entire string and replace %0 %1 etc with the corresponding
      // index in the replace list
      scl_log_output("%s", config.pre);

      for (usize i = 0; i < entry.value.len; i++) {
        char c = entry.value.raw[i];
        char c2 = '\0';
        if (i + 1 < entry.value.len) {
          c2 = entry.value.raw[i + 1];
        }
        if (c != BK_VAR_PRE || !(c2 >= '0' && c2 <= '9')) {
          // escape character
          if (c2 == BK_VAR_PRE && c == BK_VAR_PRE) {
            i++;
          }
          scl_putchar(c);
        } else {
          i++;
          SclError err = SCL_OK;
          Str s = str_init(&c2, 1);
          usize index = str_to_i64(s, 10, &err);
          scl_log_output("%s", rl_get(rl, index));
        }
      }

      scl_log_output("%s", config.post);
      return OK;
    }
  }
  alloc.free(line);

  return ERR_NOT_FOUND;
}

ReplaceList rl_init() {
  ReplaceList rl;
  scl_memset(&rl, 0, sizeof(rl));

  return rl;
}
void rl_insert(ReplaceList *rl, char *str) {
  if (rl->len > RL_MAX) {
    scl_log_error("Replace list is full!\n");
  }
  rl->data[rl->len] = str;
  rl->len++;
}

char *rl_get(ReplaceList *rl, usize index) {
  if (index >= rl->len) {
    return "(null)";
  }
  return rl->data[index];
}

void rl_free(ReplaceList *rl) {}

FILE *bk_open_file() {
  const char *path = getenv(BK_FILE_ENV); // NOLINT
  if (path) {
    return fopen(path, "re");
  }
  return stdin;
}

void bk_close_file(FILE *f) {
  if (f != stdin) {
    fclose(f);
  }
}
