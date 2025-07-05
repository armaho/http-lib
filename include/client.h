#ifndef _http_lib_client_h_
#define _http_lib_client_h_

#include <stdlib.h>

#include "conn.h"
#include "err.h"
#include "request.h"

typedef struct {
  const char *servAddr;
  const char *servPort;
} HttpClient;

HttpErr initHttpClient(HttpClient *client, const char *addr, const char *port);
HttpErr sendRequestHttpClient(const HttpClient *client, const HttpRequest *req);

#endif
