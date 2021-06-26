Performance benefit of **skipping converged vertices** for PageRank ([pull], [CSR]).

This experiment was for comparing performance between:
1. Find pagerank **without optimization**.
2. Find pagerank *skipping converged vertices* **with re-check** (in `2`-`16` turns).
3. Find pagerank *skipping converged vertices* **after several turns** (in `2`-`64` turns).

Each approach was attempted on a number of graphs, running each approach 5
times to get a good time measure. **Skip with re-check** (`skip-check`) is
done every `2`-`16` turns. **Skip after turns** (`skip-after`) is done after
`2`-`64` turns. On average, *neither* `skip-check`, nor `skip-after` gives
**better speed** than the **default (unoptimized) approach**. This could be
due to the unnessary iterations added by `skip-check` (mistakenly skipped),
and increased memory accesses performed by `skip-after` (tracking converged
count).

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [11758.935 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq
# [11929.016 ms; 051 iters.] [5.4765e-09 err.] pagerankSeq [skip-check=2]
# [11915.469 ms; 051 iters.] [4.9866e-09 err.] pagerankSeq [skip-check=3]
# [11933.364 ms; 051 iters.] [9.5208e-09 err.] pagerankSeq [skip-check=4]
# [11929.006 ms; 051 iters.] [1.5914e-08 err.] pagerankSeq [skip-check=6]
# [11925.780 ms; 051 iters.] [1.9535e-08 err.] pagerankSeq [skip-check=8]
# [11928.582 ms; 051 iters.] [5.3770e-08 err.] pagerankSeq [skip-check=11]
# [11936.512 ms; 051 iters.] [9.3082e-08 err.] pagerankSeq [skip-check=14]
# [12292.967 ms; 051 iters.] [1.3980e-08 err.] pagerankSeq [skip-after=2]
# [12328.237 ms; 051 iters.] [5.1652e-09 err.] pagerankSeq [skip-after=3]
# [12313.705 ms; 051 iters.] [3.5257e-09 err.] pagerankSeq [skip-after=4]
# [12321.404 ms; 051 iters.] [9.6918e-11 err.] pagerankSeq [skip-after=6]
# [12326.011 ms; 051 iters.] [9.0026e-12 err.] pagerankSeq [skip-after=8]
# [12307.333 ms; 051 iters.] [1.4921e-13 err.] pagerankSeq [skip-after=11]
# [12334.150 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=14]
# [12290.369 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=17]
# [12349.979 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=21]
# [12283.471 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=25]
# [12371.266 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=29]
# [12305.829 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=33]
# [12340.425 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=38]
# [12329.927 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=43]
# [12302.537 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=48]
# [12344.922 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=53]
# [12297.962 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=58]
# [12339.748 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=63]
#
# ...
```

[![](https://i.imgur.com/HabTid9.gif)][sheets]
[![](https://i.imgur.com/R8JBilv.gif)][sheets]
[![](https://i.imgur.com/eqFrj7d.gif)][sheets]
[![](https://i.imgur.com/pAC9diq.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/KExwVG1.jpg)](https://www.youtube.com/watch?v=A7TKQKAFIi4)

[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/p6YDtgaxBgbMGSGx7
[sheets]: https://docs.google.com/spreadsheets/d/1g8AkDolNHqvvabhX0KYIaOwc5h-lLRUnCgJ8an-uewQ/edit?usp=sharing
