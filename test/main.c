#include "client.h"
#include "communication.h"
#include "request.h"
#include <sysexits.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "usage: http-lib <hostname> <port>\n");
    exit(EX_USAGE);
  }

  HttpErr err;
  HttpClient client;

  if ((err = initHttpClient(&client, argv[1], argv[2])) != HERR_NO_ERR) {
    printf("client err: %d", err);
    exit(EX_SOFTWARE);
  }

  HttpRequest req;

  if ((err = initHttpRequest(&req, HREQ_GET, "/", 1)) != HERR_NO_ERR) {
    printf("init request err: %d", err);
    exit(EX_SOFTWARE);
  }

  if ((err = sendHttpRequest(client.conn, &req)) != HERR_NO_ERR) {
    printf("send request err: %d", err);
    exit(EX_SOFTWARE);
  }

  if ((err = sendHttpRequest(client.conn, &req)) != HERR_NO_ERR) {
    printf("send request err: %d", err);
    exit(EX_SOFTWARE);
  }

  freeHttpClient(&client);

  return 0;
}
