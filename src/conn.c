#include <assert.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "conn.h"
#include "debug.h"

HttpErr sendRawMessageHttpConn(const HttpConn *conn, const char *message, size_t len) {
  assert(conn != NULL);

  size_t totalSentLen = 0;
  while (totalSentLen < len) {
    ssize_t sentLen = send(conn->sockfd, message + totalSentLen, len - totalSentLen, 0);

    if (sentLen == -1) {
      return HERR_CANNOT_SEND;
    }
    totalSentLen += sentLen;

#ifdef DEBUG_CONN
    printf("sent packet. len: %zd\n", sentLen);
#endif
  }

  return HERR_NO_ERR;
}

HttpErr freeHttpConn(HttpConn *conn) {
  if (close(conn->sockfd) == -1) {
    return HERR_OS;
  }
  return HERR_NO_ERR;
}
