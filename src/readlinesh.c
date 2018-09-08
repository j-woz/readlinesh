
#define _GNU_SOURCE // for asprintf()
#include <getopt.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "readlinesh.h"

float readlinesh_version = 1.0;

static char* default_prompt = "> ";
static char* default_destination = (char*) 1;

/** Need this for signal handler */
static readlinesh_params* params_active = NULL;

#define NL "\n"
static char* usage = NL
  " -d <destination>  -- Where to write the line (default stdout)  " NL
  " -H <history>      -- History file (default ~/.readline-history)" NL
  " -p <prompt>       -- The prompt (default \"> \")               " NL
  NL
  "The line is written to history even on Ctrl-C."    NL
  "Use Ctrl-D to cancel and skip writing to history." NL
  "See the man page for more details."                NL
  NL
  "\t Author: Justin M Wozniak <wozniak@mcs.anl.gov>" NL
  ;

static void
help(void)
{
  printf("readlinesh usage: readline <options...>\n");
  printf("%s", usage);
  exit(EXIT_SUCCESS);
}

static void
version(void)
{
  printf("readlinesh version: %0.1f\n", readlinesh_version);
  exit(EXIT_SUCCESS);
}

void
readlinesh_params_reset(readlinesh_params* params)
{
  params->prompt      = NULL;
  params->destination = NULL;
  params->history     = NULL;
}

bool
readlinesh_opts2params(int argc, char** argv,
                       readlinesh_params* params,
                       char** errors)
{
  int opt;
  while ((opt = getopt(argc, argv, "d:hH:p:v")) != -1)
  {
    switch (opt)
    {
      case 'd':
        params->destination = strdup(optarg);
        break;
      case 'h':
        help();
        break;
      case 'H':
        params->history = strdup(optarg);
        break;
      case 'p':
        params->prompt = strdup(optarg);
        break;
      case 'v':
        version();
        break;
      default:
        // getopt prints an error message
        return false;
    }
  }
  return true;
}

static void setup_defaults(readlinesh_params*  defaults,
                           readlinesh_params** params);

static bool setup_history(const readlinesh_params* params,
                          char** errors);

static void handle_signal(int signal);

static bool use_input(const readlinesh_params* params,
                      const char* input,
                      char** errors);

bool
readlinesh(readlinesh_params* params,
           char** errors)
{
  bool result = true;

  readlinesh_params defaults;
  setup_defaults(&defaults, &params);

  result = setup_history(params, errors);
  if (!result) return false;

  params_active = params;
  signal(SIGINT, handle_signal);
  char* input = readline(params->prompt);
  if (!input)
  {
    puts("");
    return false;
  }

  result = use_input(params, input, errors);

  free(input);
  return result;
}

static bool ensure_history_exists(const char* history);

static bool
setup_history(const readlinesh_params* params, char** errors)
{
  bool result = ensure_history_exists(params->history);
  if (!result)
  {
    asprintf(errors, "could not open history: %s", params->history);
    return false;
  }

  // Configure readline to auto-complete paths when the tab key is hit.
  rl_bind_key('\t', rl_complete);
  read_history(params->history);
  return true;
}

static bool
ensure_history_exists(const char* history)
{
  FILE* f = fopen(history, "a");
  if (f == NULL) return false;
  fclose(f);
  return true;
}

static void
handle_signal(int signal)
{
  puts("");
  add_history(rl_line_buffer);
  append_history(1, params_active->history);
  exit(128+signal);
}

static void
setup_defaults(readlinesh_params*  defaults,
               readlinesh_params** params)
{
  if (*params == NULL)
  {
    readlinesh_params_reset(defaults);
    *params = defaults;
  }

  readlinesh_params* p = *params;
  if (p->prompt == NULL)
    p->prompt = default_prompt;
  if (p->destination == NULL)
    p->destination = default_destination;
  if (p->history == NULL)
  {
    char* home = getenv("HOME");
    asprintf(&p->history, "%s/.readlinesh-history", home);
  }
}

static bool write_string(const char* file, const char* string,
                         char** errors);

static bool
use_input(const readlinesh_params* params, const char* input,
          char** errors)
{
  bool result = true;
  add_history(input);
  append_history(1, params->history);
  history_truncate_file(NULL, 1000);
  if (params->destination == default_destination)
    printf("%s\n", input);
  else
    result = write_string(params->destination, input, errors);
  return result;
}

static bool
write_string(const char* file, const char* string, char** errors)
{
  FILE* f = fopen(file, "w");
  if (f == NULL)
  {
    asprintf(errors, "Could not open for write: %s", file);
    return false;
  }
  fprintf(f, "%s\n", string);
  fclose(f);
  return true;
}

void
readlinesh_abort(char* errors)
{
  if (errors != NULL)
  {
    printf("readline: %s\n", errors);
    free(errors);
  }
  exit(EXIT_FAILURE);
}
