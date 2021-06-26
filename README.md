Performance of **static** vs **dynamic** [levelwise] PageRank ([pull], [CSR],
[skip-teleport], [compute-10], [skip-comp], [scaled-fill]).

This experiment was for comparing performance between:
1. Find **static** [monolithic] pagerank of updated graph.
2. Find **dynamic** [monolithic] pagerank of updated graph.
3. Find **static** [levelwise] pagerank of updated graph.
4. Find **dynamic** [levelwise] pagerank of updated graph.

Each approach was attempted on a number of graphs, running each with multiple
batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run with 5
different updates to graph, and each specific update was run 5 times for each
approach to get a good time measure. **Levelwise** pagerank is the
[STIC-D algorithm], without **ICD** optimizations (using single-thread).
Indeed, **dynamic levelwise** pagerank is **faster** than the *static* approach
for many batch sizes.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. For previous experiments, see [branches].

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
# [00401.425 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq
# [00300.418 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [split]
# [00298.443 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq [split; sort]
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [12306.131 ms; 055 iters.] [0.0000e+00 err.] pagerankSeq
# [11595.641 ms; 055 iters.] [0.0000e+00 err.] pagerankSeq [split]
# [12254.420 ms; 055 iters.] [0.0000e+00 err.] pagerankSeq [split; sort]
#
# ...
```

[![](https://i.imgur.com/GXjAjZW.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/pH5CTr2.jpg)](https://www.youtube.com/watch?v=rskLxOHNF3k)

[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
["graphs"]: https://github.com/puzzlef/graphs
[monolithic]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[skip-teleport]: https://github.com/puzzlef/pagerank-levelwise-skip-teleport
[compute-10]: https://github.com/puzzlef/pagerank-levelwise-adjust-compute-size
[skip-comp]: https://github.com/puzzlef/pagerank-levelwise-dynamic-validate-skip-unchanged-components
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[branches]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise/branches
[charts]: https://photos.app.goo.gl/cvr79cUjgicXM5KDA
[sheets]: https://docs.google.com/spreadsheets/d/1sQ1FXmv9rc2liBxnB-2Qf_rfJVZQWKiO_5AO7hu1Rl0/edit?usp=sharing
