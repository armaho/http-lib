#ifndef _http_lib_client_h_
#define _http_lib_client_h_

#include <stdlib.h>

#include "conn.h"
#include "err.h"

typedef struct {
  HttpConn *conn;
} HttpClient;

HttpErr initHttpClient(HttpClient *client, const char *addr, const char *port);
HttpErr freeHttpClient(HttpClient *client);

#endif
