Performance of **C++ DiGraph class** based vs **CSR** based PageRank ([pull]).

This experiment was for comparing the performance between:
1. Find pagerank using C++ `DiGraph` **class** directly.
2. Find pagerank using **CSR** representation of DiGraph.

Both these approaches were tried on a number of different graphs, running
each approach 5 times per graph to get a good time measure. Using a **CSR**
(Compressed Sparse Row) representation has the potential for **performance**
**improvement** for both the methods due to information on vertices and edges
being stored contiguously. Note that neither approach makes use of *SIMD*
*instructions* which are available on all modern hardware.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00801.153 ms; 062 iters.] [0.0000e+00 err.] pagerankClass
# [00404.061 ms; 062 iters.] [0.0000e+00 err.] pagerankCsr
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [23022.873 ms; 050 iters.] [0.0000e+00 err.] pagerankClass
# [11676.849 ms; 050 iters.] [0.0000e+00 err.] pagerankCsr
#
# ...
```

[![](https://i.imgur.com/pZnaYdR.png)][sheets]
[![](https://i.imgur.com/xEV1x06.png)][sheets]

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/MwsC9Av.jpg)](https://www.youtube.com/watch?v=GRvZnN0iiwo)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[charts]: https://photos.app.goo.gl/6YFy7DhgBLhsX3HC9
[sheets]: https://docs.google.com/spreadsheets/d/1W3I60JMLTfzR64GzEWJx6Kzp9R9AaiQLepHE3JqGWeM/edit?usp=sharing
