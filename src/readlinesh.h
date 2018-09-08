
#ifndef READLINESH_H
#define READLINESH_H

#include <stdbool.h>

extern float readlinesh_version;

typedef struct
{
  char* prompt;
  char* destination;
  char* history;
} readlinesh_params;

void readlinesh_params_reset(readlinesh_params* params);

bool readlinesh_opts2params(int argc, char** argv,
                            readlinesh_params* params,
                            char** errors);

void readlinesh_params_free(readlinesh_params* params);

bool readlinesh(readlinesh_params* params,
                char** errors);

void readlinesh_abort(char* errors);

#endif
