Performance benefit of PageRank with vertices **split by components** ([pull], [CSR]).

`TODO!`

This experiment was for comparing performance between:
1. Find pagerank **without optimization**.
2. Find pagerank with vertices **split by components**.
3. Find pagerank with components **sorted in topological order**.

Each approach was attempted on a number of graphs, running each approach 5
times to get a good time measure. On **road networks** and **web graphs**,
**splitting vertices by components** provides a **speedup**, but *sorting*
*components in topological order* provides *no additional speedup*. For road
networks, like `germany_osm` which only have *one component*, the speedup is
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

[![](https://i.imgur.com/8oT4ZeQ.png)][sheetp]
[![](https://i.imgur.com/vngyBjn.png)][sheetp]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/z8RKUMF.jpg)](https://www.youtube.com/watch?v=ocTgFXPnTgQ)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/HqQHJ2twRK7Ge1Xc6
[sheets]: https://docs.google.com/spreadsheets/d/1YmY_KYo9cDe2YCuwTgiiT0fFnyPS9-WScDIO9n-zRSY/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vTuCCFA1zalH4-a-N45W1pd-lUyi6IoqhHWfxRcxuGz2NZei034msrjcbisQ7oOKsa-8i4MWr3YClu-/pubhtml
