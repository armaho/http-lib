#ifndef _http_lib_string_helper_h_
#define _http_lib_string_helper_h_

#include <stdlib.h>

#include "err.h"

HttpErr strcatRealloc(char **bufPtr, const char *app, size_t *buflen);

#endif
