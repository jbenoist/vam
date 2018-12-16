/*
 * For discrete distribution sampling in constant time.
 *
 * Based on Vose's Alias algorithm:
 * http://www.keithschwarz.com/darts-dice-coins/
 */

package vam

import (
  "math/rand"
)

type Vam struct {
  alias []int
  prob []float64
}

func New(dist []float64) *Vam {
  v := &Vam{}
  v.prob = make([]float64, len(dist), len(dist))
  v.alias = make([]int, len(dist), len(dist))
  prob := make([]float64, len(dist), len(dist))
  small, large := new_stack(len(dist)), new_stack(len(dist))
  for idx, d := range dist {
    prob[idx] = d * float64(len(dist))
    if prob[idx] < 1.0 {
      small.push(idx)
    } else {
      large.push(idx)
    }
  }
  for !small.empty() && !large.empty() {
    s := small.pop()
    l := large.pop()
    v.prob[s] = prob[s]
    v.alias[s] = l
    prob[l] = prob[l] + prob[s] - 1.0
    if prob[l] < 1.0 {
      small.push(l)
    } else {
      large.push(l)
    }
  }
  for !small.empty() {
    v.prob[small.pop()] = 1.0
  }
  for !large.empty() {
    v.prob[large.pop()] = 1.0
  }
  return v
}

func (v *Vam) Sample() int {
  fair := rand.Intn(len(v.prob))
  biased := rand.Float64()
  if biased < v.prob[fair]  {
    return fair
  }
  return v.alias[fair]
}
