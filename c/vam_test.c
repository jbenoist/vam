#include "vam.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SOURCE_COUNT 1000
#define SAMPLE_COUNT 10000000
#define ARRAY_LAST(a) (a[ARRAY_SIZE(a)-1])
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_RAND(a) (a[random()%ARRAY_SIZE(a)])

static const int range[] = {10, 20, 30};
static const int exclude[] = {[5]=1, [11]=1, [23]=1, [29]=1};

static double *distribution(int *input, int input_len, int maxval) {
  double cum = 0.00;
  double *dist = calloc(maxval, sizeof(*dist));
  for (int i = 0; i < input_len; i++) {
    cum += 1.00;
    dist[input[i]] += 1.0;
  }
  for (int i = 0; i < maxval; i++) {
    dist[i] /= cum;
  }
  return dist;
}

int main(int argc, char **argv)
{
  vam_t *vam;
  double *source_dist;
  double *sample_dist;
  int *source = malloc(SOURCE_COUNT*sizeof(*source));
  int *sample = malloc(SAMPLE_COUNT*sizeof(*sample));
  for (int i = 0; i < SOURCE_COUNT; i++) {
    do {
      source[i] = random() % ARRAY_RAND(range);
    } while (exclude[source[i]] == 1);
  }
  source_dist = distribution(source, SOURCE_COUNT, ARRAY_LAST(range));
  vam = vam_new(source_dist, ARRAY_LAST(range));
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    sample[i] = vam_sample(vam);
  }
  sample_dist = distribution(sample, SAMPLE_COUNT, ARRAY_LAST(range));
  for (int i = 0; i < ARRAY_LAST(range); i++) {
    double diff = 0;
    if (sample_dist[i] > 0) {
      diff = 100.00-source_dist[i]/sample_dist[i]*100.00;
    }
    assert(diff < 1.00);
    if (exclude[i] == 0) {
      printf("%2d %.2f%% %.2f%% %5.2f%%\n", i, source_dist[i]*100, sample_dist[i]*100, diff);
    } else {
      assert(diff == 0.00);
      printf("%2d\n", i);
    }
  }
  free(source);
  free(sample);
  free(source_dist);
  free(sample_dist);
  vam_free(vam);
  return 0;
}
