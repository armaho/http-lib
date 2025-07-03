#include <string.h>

#include "string-helper.h"

HttpErr strcatRealloc(char **bufPtr, const char *app, size_t *bufCapPtr) {
#define BUF (*bufPtr)
#define BUF_CAP (*bufCapPtr)

  size_t finalLen = strlen(app) + strlen(BUF) + 1;

  if (finalLen > BUF_CAP) {
    BUF_CAP = 2 * finalLen;
    BUF = (char *)realloc(BUF, BUF_CAP * sizeof(char));
    if (BUF == NULL) {
      return HERR_OS;
    }
  }

  strlcat(BUF, app, BUF_CAP);
  
  return HERR_NO_ERR;
#undef BUF
}

