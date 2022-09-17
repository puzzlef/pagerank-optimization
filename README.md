Performance benefit of **skipping in-identical vertices** for PageRank ([pull], [CSR]).

This experiment was for comparing performance between:
1. Find PageRank **without optimization**.
2. Find PageRank **skipping rank calculation of in-identical vertices**.

Each approach was attempted on a number of graphs, running each approach 5 times
to get a good time measure. The minimum size of *in-identical groups* is varied
from 2-256, with 2 being the default (`skip2`), and the best among them is also
picked (`skipbest`). It seems **skipping all in-identicals** *(skip2)*
**decreases execution time by -36 to 34%**, while **skipping in-identicals with
best group size or more** *(skipbest)* **decreases execution time by 0 to 34%**,
when compared to no optimization. This speedup is mainly observed on
`indochina-2004`, and hardly any on the other graphs. This speedup could be due
to the fact that the graph `indochina-2004` has a large number of
**in-identicals** and **in-identical groups**, although it doesn't have the
highest **in-identicals %** or the highest **avg. in-identical group size**.
With respect to **GM-RATIO**, *skipping in-identicals (skip2)* completes in **4%
more time (0.96x)**, and *skipping best in-identicals (skipbest)* completes in
**4% less time (1.04x)**, than using default approach. With respect to
**AM-RATIO**, *skipping in-identicals (skip2)* completes in **4% less time
(1.04x)**, and *skipping best in-identicals (skipbest)* completes in **10% less
time (1.11x)**, than using default approach. It therefore makes sense to apply
this optimization only when the graph has a large number of in-identicals.

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
# [00454.346 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq
# [00515.258 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=002; inidenticals=00100411; inidentical-groups=00013685]
# [00478.698 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=004; inidenticals=00081602; inidentical-groups=00005358]
# [00469.105 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=008; inidenticals=00068989; inidentical-groups=00002814]
# [00454.380 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=016; inidenticals=00042289; inidentical-groups=00000621]
# [00453.333 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=032; inidenticals=00033030; inidentical-groups=00000210]
# [00451.667 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=064; inidenticals=00026535; inidentical-groups=00000066]
# [00452.077 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=128; inidenticals=00022136; inidentical-groups=00000013]
# [00452.819 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=256; inidenticals=00020315; inidentical-groups=00000001]
#
# ...
#
# Loading graph /home/subhajit/data/indochina-2004.mtx ...
# order: 7414866 size: 194109311 {}
# order: 7414866 size: 194109311 {} (transposeWithDegree)
# [20659.361 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq
# [13675.594 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=002; inidenticals=03812478; inidentical-groups=00536411]
# [13248.308 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=004; inidenticals=03158460; inidentical-groups=00248667]
# [13628.869 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=008; inidenticals=02526184; inidentical-groups=00125764]
# [14506.956 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=016; inidenticals=01740972; inidentical-groups=00050013]
# [15115.612 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=032; inidenticals=00902774; inidentical-groups=00012522]
# [15973.252 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=064; inidenticals=00520148; inidentical-groups=00003583]
# [16777.990 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=128; inidenticals=00298452; inidentical-groups=00001067]
# [18722.801 ms; 061 iters.] [0.0000e+00 err.] pagerankSeq [skip-indenticals=256; inidenticals=00174415; inidentical-groups=00000341]
#
# ...
```

[![](https://i.imgur.com/6FHGlfe.png)][sheetp]
[![](https://i.imgur.com/Ti2UxC6.png)][sheetp]
[![](https://i.imgur.com/gpegImP.png)][sheetp]
[![](https://i.imgur.com/4ECJNtM.png)][sheetp]
[![](https://i.imgur.com/SBgCMEF.png)][sheetp]

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
[![ORG](https://img.shields.io/badge/org-puzzlef-green?logo=Org)](https://puzzlef.github.io)
[![DOI](https://zenodo.org/badge/380669270.svg)](https://zenodo.org/badge/latestdoi/380669270)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/8xjqrsB6jqFAxGWF7
[sheets]: https://docs.google.com/spreadsheets/d/1FyOjUSpAlpZdx1Pf0DzzS2gzkv9aU8HJtLsW8XkITrs/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vQd9LVv2chGd7pY6LtQXRcZL-HKKj3HvN6Z-VUulKmuxSFuSyWzwi_sawnNka0FLpff5SZaw98L4tTW/pubhtml
