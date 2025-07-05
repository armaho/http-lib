#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "request.h" 
#include "string-helper.h"
#include "date-helper.h"

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

HttpErr serializeHttpRequest(const HttpRequest *req, char **buf, size_t *len) {
#define BUF (*buf)
#define LEN (*len)

  assert(req != NULL);
  assert(buf != NULL);
  assert(len != NULL);

  HttpErr err;
  
  if ((err = strInitBufIfNull(buf, len, INIT_BUF_SIZE)) != HERR_NO_ERR) {
    return err;
  }

  char *method;
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

#define DATE_BUF_SIZE 100

  char date[DATE_BUF_SIZE];
  if ((err = getCurrentDateStr(date, DATE_BUF_SIZE)) != HERR_NO_ERR) {
    return err;
  }
  
  strcatRealloc(buf, "Date: ", len);
  strcatRealloc(buf, date, len);
  strcatRealloc(buf, "\r\n", len);

  strcatRealloc(buf, "\r\n", len);

#ifdef DEBUG_REQUEST
  printf("%s", BUF);
#endif

  return HERR_NO_ERR;

#undef BUF
}

