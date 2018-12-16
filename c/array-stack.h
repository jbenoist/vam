#ifndef _ARRAY_STACK_H
#define _ARRAY_STACK_H

#include <stdlib.h>

#define ARRAY_STACK_NEW(S, N, L)\
struct S *N = malloc(sizeof(*N) + L*sizeof(*N->v));\
{\
  N->h=0;\
}

#define ARRAY_STACK_DECLARE(S, T)\
\
struct S {\
  int h;\
  T v[0];\
};\
\
static void  __attribute__ ((unused)) push_##S(struct S *s, T v)\
{\
  s->v[s->h++] = v;\
}\
\
static T __attribute__ ((unused)) pop_##S(struct S *s)\
{\
  return s->v[--s->h];\
}\
\
static T __attribute__ ((unused)) top_##S(struct S *s)\
{\
  return s->v[s->h-1];\
}\
\
static int __attribute__ ((unused)) empty_##S(struct S *s)\
{\
  return s->h == 0;\
}

#endif  /* _ARRAY_STACK_H */
