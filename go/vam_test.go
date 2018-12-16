package vam

import (
  "fmt"
  "math/rand"
  "testing"
)

const SOURCE_COUNT = 1000
const SAMPLE_COUNT = 10000000

var _range = []int{10, 20, 30}
var exclude = []int{5: 1, 11: 1, 23: 1, 29: 1}

func distribution(input []int, div int) []float64 {
  cum := float64(0)
  dist := make([]float64, div)
  for _, n := range input {
    cum += 1.0
    dist[n] += 1.0
  }
  for n, _ := range dist {
    dist[n] /= cum
  }
  return dist
}

func TestVam(t *testing.T) {
  source := make([]int, SOURCE_COUNT)
  for idx, _ := range source {
    for source[idx] = rand.Intn(_range[rand.Intn(len(_range))]);
        exclude[source[idx]] == 1;
        source[idx] = rand.Intn(_range[rand.Intn(len(_range))]) {
    }
  }
  source_dist := distribution(source, _range[len(_range)-1])
  v := New(source_dist)
  sample := make([]int, SAMPLE_COUNT)
  for idx := 0; idx < len(sample); idx++ {
    sample[idx] = v.Sample()
  }
  sample_dist := distribution(sample, _range[len(_range)-1])
  for i := 0; i < len(sample_dist); i++ {
    diff := 0.00
    if sample_dist[i] > 0 {
      diff = 100 - source_dist[i]/sample_dist[i]*100
    }
    if diff >= 1.0 {
      t.Fail()
    }
    if exclude[i] == 0 {
      fmt.Printf("%2d %.2f%% %.2f%% %5.2f%%\n", i, source_dist[i]*100, sample_dist[i]*100, diff)
    } else {
      if diff > 0.00 {
        t.Fail()
      }
      fmt.Printf("%2d\n", i)
    }
  }
}
