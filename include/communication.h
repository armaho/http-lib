#ifndef _http_lib_communication_h_
#define _http_lib_communication_h_

#include "err.h"
#include "conn.h"
#include "request.h"

HttpErr sendHttpRequest(const HttpConn *conn, const HttpRequest *req);

#endif
