#include "communication.h"
#include "string-helper.h"
#include "debug.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define INIT_BUF_SIZE 128

static HttpErr sendRaw(const HttpConn *conn, const char *message, size_t len) {
  assert(conn != NULL);

  size_t totalSentLen = 0;
  while (totalSentLen < len) {
    ssize_t sentLen = send(conn->sockfd, message + totalSentLen, len - totalSentLen, 0);

    if (sentLen == -1) {
      return HERR_CANNOT_SEND;
    }
    totalSentLen += sentLen;

#ifdef DEBUG_COMMUNICATION
    printf("sent packet. len: %zd\n", sentLen);
#endif
  }

  return HERR_NO_ERR;
}

static HttpErr recvRaw(const HttpConn *conn, char **buf, size_t *len) {
#define BUF (*buf)
#define TMP_BUF_CAP 128
  HttpErr err;

  if ((err = strInitBufIfNull(buf, len, INIT_BUF_SIZE)) != HERR_NO_ERR) {
    return err;
  }

  int tmpBufLen;
  char tmpBuf[TMP_BUF_CAP];
  while (true) {
    if ((tmpBufLen = recv(conn->sockfd, tmpBuf, TMP_BUF_CAP - 1, 0)) == 0) {
      break;
    } else if (tmpBufLen == -1) {
      return HERR_CANNOT_RECV;
    }

#ifdef DEBUG_COMMUNICATION
    printf("Packet Recieved. Len: %d\n", tmpBufLen);
#endif
    tmpBuf[tmpBufLen] = '\0';
    
    strcatRealloc(buf, tmpBuf, len);
  }

#ifdef DEBUG_COMMUNICATION
  printf("### RESPONSE ###\n");
  printf("Len: %lu\n", strlen(BUF));
  printf("----------------\n");
  printf("%s\n", BUF);
#endif

  return HERR_NO_ERR;
#undef TMP_BUF_CAP
#undef BUF
}

HttpErr sendHttpRequest(const HttpConn *conn, const HttpRequest *req) {
  assert(conn != NULL);
  assert(req != NULL);

  HttpErr err;

  char *buf = NULL;
  size_t bufCap;

  if ((err = serializeHttpRequest(req, &buf, &bufCap)) != HERR_NO_ERR) {
    return err;
  }

  if ((err = sendRaw(conn, buf, strlen(buf)))) {
    return err;
  }

  free(buf);

  char *resp = NULL;
  size_t respCap;

  if ((err = recvRaw(conn, &resp, &respCap)) != HERR_NO_ERR) {
    return err;
  }

  return HERR_NO_ERR;
}

