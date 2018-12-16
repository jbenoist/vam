cmake_minimum_required (VERSION 2.8.6)

project (vam)

if (CMAKE_BUILD_TYPE MATCHES "ASAN")
  # implies -DCMAKE_C_COMPILER=/path/to/clang
  set(san_lib asan)
  set(san_opts -fsanitize=address)
endif (CMAKE_BUILD_TYPE MATCHES "ASAN")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-g -O2 -Wall -D_GNU_SOURCE ${san_opts})
add_executable(vam_test vam.c vam_test.c)
target_link_libraries(vam_test ${san_lib})
