Performance benefit of **skipping chain vertices** for PageRank ([pull], [CSR]).

This experiment was for comparing performance between:
1. Find PageRank **without optimization**.
2. Find PageRank **skipping rank calculation of chain vertices**.

Each approach was attempted on a number of graphs, running each approach 5 times
to get a good time measure. The minimum size of *chains* is varied from 2-256,
with 2 being the default (`skip2`), and the best among them is also picked
(`skipbest`). A **chain** here means a set of *uni-directional* *links*
connecting one vertex to the next, without any additional edges. *Bi-directional
links* are **not** considered as **chains**. Note that most graphs don't have
enough chains to provide an advantage. Road networks do have chains, but they
are *bi-directional*, and thus not considered here. It seems **skipping all
chains** *(skip2)* **decreases execution time by -7 to 11%**, while **skipping
chains with best group size or more** *(skipbest)* **decreases execution time by
0 to 11%**, when compared to no optimization. Please note that some other these
small speedups can be attributed to randomness (execution time has small
variations). With respect to **GM-RATIO**, *skipping chains (skip2)* and
*skipping best chains (skipbest)* completes in **1% less time (1.01x)** than
using default approach. With respect to **AM-RATIO**, *skipping chains (skip2)*
completes in **2% less time (1.02x)**, and *skipping best chains (skipbest)*
completes in **3% less time (1.03x)**, than using default approach. It therefore
makes sense to apply this optimization only when the graph has a large number of
chains.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -std=c++17 -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00443.403 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq
# [00436.523 ms; 063 iters.] [1.7376e-09 err.] pagerankSeq [skip-chains=002; chain-vertices=00001265; chains=00000575]
# [00445.141 ms; 063 iters.] [1.1369e-11 err.] pagerankSeq [skip-chains=004; chain-vertices=00000051; chains=00000002]
# [00433.567 ms; 063 iters.] [1.1369e-11 err.] pagerankSeq [skip-chains=008; chain-vertices=00000051; chains=00000002]
# [00438.725 ms; 063 iters.] [1.1369e-11 err.] pagerankSeq [skip-chains=016; chain-vertices=00000051; chains=00000002]
# [00435.385 ms; 063 iters.] [1.0004e-11 err.] pagerankSeq [skip-chains=032; chain-vertices=00000034; chains=00000001]
# [00437.912 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=064; chain-vertices=00000000; chains=00000000]
# [00435.215 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=128; chain-vertices=00000000; chains=00000000]
# [00438.292 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=256; chain-vertices=00000000; chains=00000000]
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [12951.940 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq
# [12891.713 ms; 051 iters.] [4.0809e-09 err.] pagerankSeq [skip-chains=002; chain-vertices=00015182; chains=00007435]
# [12888.291 ms; 051 iters.] [3.2955e-11 err.] pagerankSeq [skip-chains=004; chain-vertices=00000008; chains=00000002]
# [12854.885 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=008; chain-vertices=00000000; chains=00000000]
# [12844.854 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=016; chain-vertices=00000000; chains=00000000]
# [12837.034 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=032; chain-vertices=00000000; chains=00000000]
# [12882.533 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=064; chain-vertices=00000000; chains=00000000]
# [12927.814 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=128; chain-vertices=00000000; chains=00000000]
# [13207.755 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-chains=256; chain-vertices=00000000; chains=00000000]
#
# ...
```

[![](https://i.imgur.com/LA07pcz.png)][sheetp]
[![](https://i.imgur.com/dfAruEl.png)][sheetp]
[![](https://i.imgur.com/eMpt8BD.png)][sheetp]
[![](https://i.imgur.com/ekbLFXm.png)][sheetp]
[![](https://i.imgur.com/QhIw85H.png)][sheetp]

<br>
<br>


## References

- [STIC-D: Algorithmic Techniques For Efficient Parallel Pagerank Computation on Real-World Graphs](https://gist.github.com/wolfram77/bb09968cc0e592583c4b180243697d5a)
- [Adjusting PageRank parameters and Comparing results](https://arxiv.org/abs/2108.02997)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/CB5t3WL.jpg)](https://www.youtube.com/watch?v=gUHejU7qyv8)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/MzFcwNV4JZL4vD1Z6
[sheets]: https://docs.google.com/spreadsheets/d/1OduhKKKTMbsKY4LamQuy3EkFT7SiADyVBR4xRu-4CI0/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vTkud1vbis8RhIIHZiboiejE9Rkuya3Uiz1WrSN3wkIXg7K6-foj9-2qxBuj8YBNNF7W2Gt8DOnzXAw/pubhtml
