/*
 * For discrete distribution sampling in constant time.
 *
 * Based on Vose's Alias algorithm:
 * http://www.keithschwarz.com/darts-dice-coins/
 */

#include <stdlib.h>
#include "array-stack.h"

struct vam {
  int n;
  int *alias;
  double *prob;
};

ARRAY_STACK_DECLARE(int_stack, int);

struct vam *vam_new(double *w, int n)
{
  double *prob;
  ARRAY_STACK_NEW(int_stack, small, n);
  ARRAY_STACK_NEW(int_stack, large, n);
  struct vam *v = calloc(1, sizeof(*v));

  v->n = n;
  prob = calloc(n, sizeof(double));
  for (int i = 0; i < n; i++) {
    prob[i] = w[i] * (double)n;
    if (prob[i] < 1.0) {
      push_int_stack(small, i);
    } else {
      push_int_stack(large, i);
    }
  }
  v->prob = calloc(n, sizeof(*v->prob));
  v->alias = calloc(n, sizeof(*v->alias));
  while (!empty_int_stack(small) && !empty_int_stack(large)) {
    int s = pop_int_stack(small);
    int l = pop_int_stack(large);
    v->prob[s] = prob[s];
    v->alias[s] = l;
    prob[l] = (prob[l] + prob[s]) - 1.0;
    if (prob[l] < 1.0) {
      push_int_stack(small, l);
    } else {
      push_int_stack(large, l);
    }
  }
  free(prob);
  while (!empty_int_stack(large)) {
    v->prob[pop_int_stack(large)] = 1.0;
  }
  while (!empty_int_stack(small)) {
    v->prob[pop_int_stack(small)] = 1.0;
  }
  free(small);
  free(large);
  return v;
}

int vam_sample(struct vam *v)
{
  int fair = rand() % v->n;
  double biased = (double)rand() / (double)(RAND_MAX);

  if (biased < v->prob[fair]) {
    return fair;
  }
  return v->alias[fair];
}

void vam_free(struct vam *v)
{
  free(v->prob);
  free(v->alias);
  free(v);
}

