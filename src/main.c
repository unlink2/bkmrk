
/**
 * When built without test
 */
#include "bkmap.h"
#ifndef TEST

/// only use main if binary
#if TYPE == bin

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

const char *argp_program_version = "bk 0.1";
const char *argp_program_bug_address = "<lukas@krickl.dev>";
static char doc[] = "bk";
static char args_doc[] =
    "Quick access to a list of bookmarks using a simple "
    "command. To change the bookmark file set " BK_FILE_ENV;

static struct argp_option options[] = {
    {"list", 'l', NULL, 0, "List all bk entires"},
    {"post", 'p', "POSTFIX", 0, "Postfix for bk output"},
    {"pre", 'b', "PREFIX", 0, "Prefix for bk output"},
    {"sep", 's', "SEPARATOR", 0, "File separator"},
    {"rep", 'r', "REPLACE", 0,
     "Replace argument. Arguments are inserted usign $0, $1 etc"},
    {0}};

static error_t parse_opt(int key, char *arg,
                         struct argp_state *state) { // NOLINT
  Config *cfg = state->input;

  switch (key) {
  case 'l':
    cfg->err |= bk_list(cfg->input);
    exit(0); // NOLINT
    break;
  case 'p':
    cfg->post = arg;
    break;
  case 'b':
    cfg->pre = arg;
    break;
  case 's':
    cfg->separator = arg[0];
    break;
  case 'r':
    rl_insert(&cfg->rl, arg);
    break;
  case ARGP_KEY_ARG:
    /*
      if (state->arg_num >= 0) {
        // Too many arguments
        argp_usage(state); // NOLINT
      }
      // arguments->args[state->arg_num] = arg;
    */

    // all args are an emoji name, go find them in the map!
    cfg->err |= bk_find(cfg->input, arg, &cfg->rl);
    break;
  case ARGP_KEY_END:
    if (state->arg_num < 1) {
      /* Not enough arguments. */
      argp_usage(state); // NOLINT
    }
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char **argv) {
  config = config_init();
  argp_parse(&argp, argc, argv, 0, 0, &config); // NOLINT

  config_free(&config);

  return config.err;
}

#endif
#endif

/**
 * When built with test
 */
#ifdef TEST

#include <scl/macros.h>

int main(int argc, char **argv) {
  const struct CMUnitTest tests[] = {NULL};
  return cmocka_run_group_tests(tests, NULL, NULL);
}

#endif
