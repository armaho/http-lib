#include <assert.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "client.h"
#include "debug.h"

static const int winSize = 9;

HttpErr initHttpClient(HttpClient *client, const char *addr, const char *port) {
  int err;
  int sockfd;
  struct addrinfo hints;
  struct addrinfo *res, *serv;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  assert(client != NULL);

  if ((err = getaddrinfo(addr, port, &hints, &res)) != 0) {
    return HERR_GETADDRINFO;
  }

  for (serv = res; serv != NULL; serv = serv->ai_next) {
    if ((sockfd = socket(serv->ai_family, serv->ai_socktype, serv->ai_protocol)) == -1) {
#ifdef DEBUG_CLIENT
      perror("socket");
#endif
      continue;
    }

    if (connect(sockfd, serv->ai_addr, serv->ai_addrlen) == -1) {
#ifdef DEBUG_CLIENT
      perror("connect");
#endif
      continue;
    }

    break;
  }

  if (serv == NULL) {
    return HERR_NO_HOST;
  }

  freeaddrinfo(res);

  if ((client->conn = (HttpConn *)malloc(sizeof(HttpConn))) == NULL) {
#ifdef DEBUG_CLIENT
    perror("malloc");
#endif
    return HERR_OS;
  }
  client->conn->sockfd = sockfd;
  
  return HERR_NO_ERR;
}

HttpErr freeHttpClient(HttpClient *client) {
  return freeHttpConn(client->conn);
}

