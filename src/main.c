
#include <stdio.h>
#include <stdlib.h>

#include "readlinesh.h"

int
main(int argc, char* argv[])
{
  bool result;
  readlinesh_params params;
  readlinesh_params_reset(&params);
  char* errors = NULL;
  result = readlinesh_opts2params(argc, argv, &params, &errors);
  if (! result) readlinesh_abort(errors);

  result = readlinesh(&params, &errors);
  if (! result) readlinesh_abort(errors);
  return EXIT_SUCCESS;
}
