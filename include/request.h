#ifndef _http_lib_request_h_
#define _http_lib_request_h_

#include <stdlib.h>

#include "err.h"

typedef enum {
  HREQ_GET,
} HttpRequestMethod;

typedef struct {
  HttpRequestMethod method;
  const char *uri;
  size_t uriLen;
} HttpRequest;

HttpErr initHttpRequest(HttpRequest *req, 
    HttpRequestMethod method, 
    const char *uri, 
    size_t uriLen);
HttpErr serializeHttpRequest(const HttpRequest *req, char **buf, size_t *len);

#endif
