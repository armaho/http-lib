#include <assert.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "conn.h"
#include "debug.h"

HttpErr closeHttpConn(HttpConn *conn) {
  if (close(conn->sockfd) == -1) {
    return HERR_OS;
  }
  return HERR_NO_ERR;
}
