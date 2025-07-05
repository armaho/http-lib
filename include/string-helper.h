#ifndef _http_lib_string_helper_h_
#define _http_lib_string_helper_h_

#include <stdlib.h>

#include "err.h"

HttpErr strInitBufIfNull(char **bufPtr, size_t *bufCap, size_t desieredCap);
HttpErr strcatRealloc(char **bufPtr, const char *app, size_t *buflen);

#endif
