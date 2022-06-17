```dot
digraph {
  1 [color=red];
  1 [label="1\nlength=0"];
  1 -> 2 [label="a"];
  1 -> 7 [label="b"];
  2 [label="2\nlength=1"];
  2 -> 1 [color=blue];
  2 -> 3 [label="a"];
  2 -> 7 [label="b"];
  3 [label="3\nlength=2"];
  3 -> 2 [color=blue];
  3 -> 4 [label="b"];
  4 [label="4\nlength=3"];
  4 -> 7 [color=blue];
  4 -> 5 [label="a"];
  5 [label="5\nlength=4"];
  5 -> 9 [color=blue];
  5 -> 6 [label="b"];
  6 [label="6\nlength=5"];
  6 -> 7 [color=blue];
  6 -> 8 [label="a"];
  7 [label="7\nlength=2"];
  7 -> 1 [color=blue];
  7 -> 9 [label="a"];
  8 [label="8\nlength=6"];
  8 -> 9 [color=blue];
  9 [label="9\nlength=3"];
  9 -> 2 [color=blue];
  9 -> 6 [label="b"];
}
```