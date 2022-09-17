Performance benefit of PageRank with vertices **split by components**
([pull], [CSR]).

This experiment was for comparing performance between:
1. Find PageRank **without optimization**.
2. Find PageRank with vertices **split by components**.
3. Find PageRank with components **sorted in topological order**.

Each approach was attempted on a number of graphs, running each approach 5 times
to get a good time measure. It seems **splitting vertices by components**
**decreases execution time by 0-38%**, when compared to no optimization. This
speedup is mostly observed on **road networks** and **web graphs**. However,
sorting components in topological order seems to provide negligible additional
speedup. With respect to **GM-RATIO**, *splitting vertices by components*
completes in **13% less time (1.15x)** than using default vertex order. Sorting
components in topological order provides no additional improvement. With respect
to **AM-RATIO**, *splitting vertices by components* completes in **14% less time
(1.16x)** than using default vertex order. *Sorting components in topological
order*  completes in **15% less time (1.18x)** than using default vertex order.
The speedup associated with *splitting of vertices by components* could be
attributed to an *increase in cache hit ratio* when accessing the rank vector
for PageRank computation. This is because when vertices are grouped by
components, the ranks of vertices in each component would be close together. As
edges within a component tend to be higher than cross component edges, ranks of
in-edge vertices are more likely to be found in the cache. For road networks,
like `germany_osm` which only have *one connected component*, the speedup is
possibly because of the *vertex reordering* caused by `dfs()` which is required
for splitting by components.

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
# [00403.016 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq
# [00300.035 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [split]
# [00298.528 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [split; sort]
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [12250.154 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq
# [11770.011 ms; 051 iters.] [4.5725e-09 err.] pagerankSeq [split]
# [11760.936 ms; 051 iters.] [4.5754e-09 err.] pagerankSeq [split; sort]
#
# ...
```

[![](https://imgur.com/KirV9Rr.png)][sheetp]
[![](https://imgur.com/7BxoMX5.png)][sheetp]

<br>
<br>


## References

- [STIC-D: Algorithmic Techniques For Efficient Parallel Pagerank Computation on Real-World Graphs](https://gist.github.com/wolfram77/bb09968cc0e592583c4b180243697d5a)
- [Adjusting PageRank parameters and Comparing results](https://arxiv.org/abs/2108.02997)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/z8RKUMF.jpg)](https://www.youtube.com/watch?v=ocTgFXPnTgQ)
[![ORG](https://img.shields.io/badge/org-puzzlef-green?logo=Org)](https://puzzlef.github.io)
[![DOI](https://zenodo.org/badge/380449199.svg)](https://zenodo.org/badge/latestdoi/380449199)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/HqQHJ2twRK7Ge1Xc6
[sheets]: https://docs.google.com/spreadsheets/d/1YmY_KYo9cDe2YCuwTgiiT0fFnyPS9-WScDIO9n-zRSY/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vTuCCFA1zalH4-a-N45W1pd-lUyi6IoqhHWfxRcxuGz2NZei034msrjcbisQ7oOKsa-8i4MWr3YClu-/pubhtml
