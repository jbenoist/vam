package vam

type stack struct {
  head int
  data []int
}

func new_stack(depth int) *stack {
  return &stack{
    head: 0,
    data: make([]int, depth),
  }
}

func (s *stack) empty() bool {
  return s.head == 0
}

func (s *stack) pop() int {
  s.head--
  return s.data[s.head]
}

func (s *stack) push(v int) {
  s.data[s.head] = v
  s.head++
}
