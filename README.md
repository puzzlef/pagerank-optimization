Performance benefit of **skipping in-identical vertices** for PageRank ([pull], [CSR]).

`TODO!`

This experiment was for comparing performance between:
1. Find pagerank **without optimization**.
2. Find pagerank **skipping rank calculation of in-identical vertices**.

Each approach was attempted on a number of graphs, running each approach 5
times to get a good time measure. On `indochina-2004` graph, **skipping**
**in-identicals** provides a **speedup** of `~1.8`, but on average provides
*no speedup* for other graphs. This could be due to the fact that the graph
`indochina-2004` has a large number of **inidenticals** and **inidentical**
**groups**, although it doesnt have the highest **inidentials %** or the
highest **avg. inidentical group size**.

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
# inidenticals: 80096 inidentical-groups: 13684 {}
# [00430.553 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq
# [00436.046 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip]
#
# ...
#
# Loading graph /home/subhajit/data/indochina-2004.mtx ...
# order: 7414866 size: 194109311 {}
# order: 7414866 size: 194109311 {} (transposeWithDegree)
# inidenticals: 3812336 inidentical-groups: 536482 {}
# [20494.613 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq
# [11604.845 ms; 061 iters.] [7.3308e-07 err.] pagerankSeq [skip]
#
# ...
```

[![](https://i.imgur.com/3Oxkf5S.png)][sheetp]
[![](https://i.imgur.com/VxzsPvV.png)][sheetp]
[![](https://i.imgur.com/3TECQBr.png)][sheetp]
[![](https://i.imgur.com/RDSls8E.png)][sheetp]
[![](https://i.imgur.com/ZspbF1F.png)][sheetp]

<br>
<br>


## References

- [STIC-D: Algorithmic Techniques For Efficient Parallel Pagerank Computation on Real-World Graphs](https://gist.github.com/wolfram77/bb09968cc0e592583c4b180243697d5a)
- [Adjusting PageRank parameters and Comparing results](https://arxiv.org/abs/2108.02997)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/Z7oiZSS.jpg)](https://www.youtube.com/watch?v=rKv_l1RnSqs)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/8xjqrsB6jqFAxGWF7
[sheets]: https://docs.google.com/spreadsheets/d/1FyOjUSpAlpZdx1Pf0DzzS2gzkv9aU8HJtLsW8XkITrs/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vQd9LVv2chGd7pY6LtQXRcZL-HKKj3HvN6Z-VUulKmuxSFuSyWzwi_sawnNka0FLpff5SZaw98L4tTW/pubhtml
