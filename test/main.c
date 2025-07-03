#include "client.h"
#include "request.h"
#include <stdio.h>

int main(int argc, char **argv) {
  HttpRequest req;

  initHttpRequest(&req, HREQ_GET, "/", 1);

  char *buf = (char *)malloc(sizeof(char));
  size_t bufCap = 1;

  HttpErr err;

  if ((err = serializeHttpRequest(&req, &buf, &bufCap)) != HERR_NO_ERR) {
    printf("err %d\n", err);
    exit(1);
  }

  printf("req: %s\n", buf);
  return 0;
}
