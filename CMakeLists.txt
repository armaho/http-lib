cmake_minimum_required(VERSION 3.29)
project(http_lib C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(http_lib
        
  include/client.h
  include/err.h
  include/debug.h
  include/conn.h
  include/request.h
  include/string-helper.h
  include/communication.h

  src/client.c
  src/conn.c
  src/request.c
  src/string-helper.c
  src/communication.c

  test/main.c)
