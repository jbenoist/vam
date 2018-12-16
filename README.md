# C/Go implem of Vose's Alias algorithm

O(1) discrete distribution sampling

source:  http://www.keithschwarz.com/darts-dice-coins

## Usage
See tests.

```
v := vam.New([]float64{0.3, 0.5, 0.2})
                       ^^^^^^^^^^^^^
                         SUM()=1.0
for {
             # 30% -> 0
  v.Sample() # 50% -> 1
             # 20% -> 2
}
```
