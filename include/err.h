#ifndef _http_lib_err_h_
#define _http_lib_err_h_

typedef enum {
  HERR_NO_ERR,
  HERR_GETADDRINFO,
  HERR_NO_HOST,
  HERR_CANNOT_RECV,
  HERR_CANNOT_SEND,
  HERR_OS,
  HERR_INVALID_METHOD,
} HttpErr;

#endif
