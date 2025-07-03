#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "request.h" 
#include "string-helper.h"

#define INIT_BUF_SIZE (1 << 7)

HttpErr initHttpRequest(HttpRequest *req, 
    HttpRequestMethod method, 
    const char *uri, 
    size_t uriLen) {
  assert(req != NULL);
  assert(uri != NULL);

  req->method = method;
  req->uri = uri;
  req->uriLen = uriLen;

  return HERR_NO_ERR;
}

HttpErr serializeHttpRequest(HttpRequest *req, char **buf, size_t *len) {
#define BUF (*buf)
#define LEN (*len)

  assert(req != NULL);
  assert(buf != NULL);
  assert(len != NULL);

  char *method;

  if (BUF == NULL) {
    LEN = INIT_BUF_SIZE;
    BUF = (char *)malloc(INIT_BUF_SIZE * sizeof(char));
    if (BUF == NULL) {
      return HERR_OS;
    }
  }
  BUF[0] = '\0';

  switch (req->method) {
    case HREQ_GET: method = "GET"; break;
    default: return HERR_INVALID_METHOD;
  }

  strcatRealloc(buf, method, len);
  strcatRealloc(buf, " ", len);

  strcatRealloc(buf, req->uri, len);
  strcatRealloc(buf, " ", len);

  strcatRealloc(buf, "HTTP/1.0", len);
  strcatRealloc(buf, " ", len);

  strcatRealloc(buf, "\r\n", len);

  strcatRealloc(buf, "\r\n", len);

  return HERR_NO_ERR;

#undef BUF
}

