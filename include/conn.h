#ifndef _http_lib_conn_h_
#define _http_lib_conn_h_

#include <stdlib.h>

#include "err.h"

typedef struct {
  int sockfd;
} HttpConn;

HttpErr sendRawMessageHttpConn(const HttpConn *client, const char *message, size_t len);
HttpErr freeHttpConn(HttpConn *conn);

#endif
