#include <time.h>

#include "date-helper.h"

HttpErr getCurrentDateStr(char *buf, size_t cap) {
  time_t current_t = time(NULL);
  if (current_t == (time_t)-1) {
    return HERR_CANNOT_GET_TIME;
  }
  
  struct tm *current_tm = gmtime(&current_t);
  
  if (strftime(buf, cap, "%a, %e %b %G %R GMT", current_tm) == 0) {
    return HERR_CANNOT_GET_TIME;
  }

  return HERR_NO_ERR;
}
