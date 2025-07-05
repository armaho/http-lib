#ifndef _http_lib_conn_h_
#define _http_lib_conn_h_

#include <stdlib.h>

#include "err.h"

typedef struct {
  int sockfd;
} HttpConn;

HttpErr closeHttpConn(HttpConn *conn);

#endif
