Performance benefit of **skipping chain vertices** for PageRank ([pull], [CSR]).

`TODO!`

This experiment was for comparing performance between:
1. Find pagerank **without optimization**.
2. Find pagerank **skipping rank calculation of chain vertices**.

Each approach was attempted on a number of graphs, running each approach 5
times to get a good time measure. On average, **skipping chain vertices**
provides **no speedup**. A **chain** here means a set of *uni-directional*
*links* connecting one vertex to the next, without any additonal edges.
*Bi-directional links* are **not** considered as **chains**. Note that most
graphs don't have enough chains to provide an advantage. Road networks do
have chains, but they are *bi-directional*, and thus not considered here.

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
# chains: 3618 chain-vertices: 3885 {}
# [00466.614 ms; 063 iters.] [0.0000e+00 err.] pagerankSeq
# [00466.725 ms; 063 iters.] [1.6226e-09 err.] pagerankSeq [skip]
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# chains: 15788 chain-vertices: 16297 {}
# [13037.498 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq
# [12704.751 ms; 051 iters.] [5.1436e-11 err.] pagerankSeq [skip]
#
# ...
```

[![](https://i.imgur.com/ocpNyOs.png)][sheetp]
[![](https://i.imgur.com/R1QVC7D.png)][sheetp]
[![](https://i.imgur.com/TgS8I4z.png)][sheetp]
[![](https://i.imgur.com/aznJUSc.png)][sheetp]
[![](https://i.imgur.com/xBrorxU.png)][sheetp]

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
