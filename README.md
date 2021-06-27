Performance benefit of **skipping in-identical vertices** for PageRank ([pull], [CSR]).

This experiment was for comparing performance between:
1. Find pagerank **without optimization**.
2. Find pagerank **skipping rank calculation of in-identical vertices**.

Each approach was attempted on a number of graphs, running each approach 5
times to get a good time measure. On `indochina-2004` graph, **skipping**
**in-identicals** provides a **speedup** of `~1.8`, but on average provides
*no speedup* for other graphs. This could be due to the fact that the graph
`indochina-2004` has a large number of **inidenticals** and **inidentical**
**groups**. Although, it doesnt have the highest **inidentials %** or the
highest **avg. inidentical group size**, so i am not so sure.

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
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# inidenticals: 80096 inidentical-groups: 13684 {}
# [00442.164 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq
# [00441.829 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip]
#
# ...
#
# Loading graph /home/subhajit/data/indochina-2004.mtx ...
# order: 7414866 size: 194109311 {}
# order: 7414866 size: 194109311 {} (transposeWithDegree)
# inidenticals: 3812336 inidentical-groups: 536482 {}
# [20319.572 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq
# [11503.846 ms; 061 iters.] [7.3308e-07 err.] pagerankSeq [skip]
#
# ...
```

[![](https://i.imgur.com/Cjq3BKI.png)][sheets]
[![](https://i.imgur.com/RI0Q7ES.png)][sheets]
[![](https://i.imgur.com/ekeZyhE.png)][sheets]
[![](https://i.imgur.com/kOmJCOM.png)][sheets]
[![](https://i.imgur.com/eIvOCUz.png)][sheets]
[![](https://i.imgur.com/lInkJTo.png)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/Z7oiZSS.jpg)](https://www.youtube.com/watch?v=rKv_l1RnSqs)

[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/8xjqrsB6jqFAxGWF7
[sheets]: https://docs.google.com/spreadsheets/d/1FyOjUSpAlpZdx1Pf0DzzS2gzkv9aU8HJtLsW8XkITrs/edit?usp=sharing
