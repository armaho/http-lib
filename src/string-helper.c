#include <assert.h>
#include <string.h>

#include "string-helper.h"

HttpErr strInitBufIfNull(char **bufPtr, size_t *bufCap, size_t desieredCap) {
#define BUF (*bufPtr)
#define CAP (*bufCap)

  assert(bufPtr != NULL);
  assert(bufCap != NULL);

  if (BUF != NULL) {
    return HERR_NO_ERR;
  }

  CAP = desieredCap;
  BUF = (char *)malloc(desieredCap * sizeof(char));
  if (BUF == NULL) {
    return HERR_OS;
  }

  BUF[0] = '\0';

  return HERR_NO_ERR;

#undef BUF
#undef CAP
}

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

