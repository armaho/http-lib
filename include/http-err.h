#ifndef _http_lib_err_h_
#define _http_lib_err_h_

typedef enum {
  HERR_NO_ERR,
  HERR_GET_ADDR_INFO,
  HERR_NO_HOST,
  HERR_CANNOT_SEND,
} HttpErr;

#endif
