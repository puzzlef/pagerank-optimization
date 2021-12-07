Performance benefit of **skipping converged vertices** for PageRank ([pull], [CSR]).

`TODO!`

This experiment was for comparing performance between:
1. Find pagerank **without optimization**.
2. Find pagerank *skipping converged vertices* **with re-check** (in `2`-`16` turns).
3. Find pagerank *skipping converged vertices* **after several turns** (in `2`-`64` turns).

Each approach was attempted on a number of graphs, running each approach 5
times to get a good time measure. **Skip with re-check** (`skip-check`) is
done every `2`-`16` turns. **Skip after turns** (`skip-after`) is done after
`2`-`64` turns.

Results indicate that only the `skip-check` optimization is able to provide
a time reduction in some cases (without introducing too much error).
- For **web graphs**, a `skip-check` of `8`/`11` appears to work best.
- For **social networks**, a `skip-check` of `3`/`11` (except for `soc-LiveJournal1`).
- For **collaboration networks**, a `skip-check` of `2`/`11` (except for `coPapersDBLP`).
- For **road networks**, `skip-check` provides no improvemnt.

On average however, *neither* `skip-check`, nor `skip-after` gives
**better speed** than the **default (unoptimized) approach** (considering
the error introduced due to skipping). This could be due to the unnessary
iterations added by `skip-check` (mistakenly skipped), and increased memory
accesses performed by `skip-after` (tracking converged count).

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

[![](https://i.imgur.com/cznle2v.png)][sheetp]
[![](https://i.imgur.com/ZjI78Cs.png)][sheetp]
[![](https://i.imgur.com/tQDyvmt.png)][sheetp]
[![](https://i.imgur.com/YDfdPvT.png)][sheetp]
[![](https://i.imgur.com/gYvoOrR.png)][sheetp]
[![](https://i.imgur.com/ncwjqsF.png)][sheetp]
[![](https://i.imgur.com/CM5O5xk.png)][sheetp]
[![](https://i.imgur.com/K6xwix9.png)][sheetp]
[![](https://i.imgur.com/pPFgvjv.png)][sheetp]
[![](https://i.imgur.com/Zk1e6DK.png)][sheetp]
[![](https://i.imgur.com/IHcNsnD.png)][sheetp]
[![](https://i.imgur.com/JGsaF5V.png)][sheetp]
[![](https://i.imgur.com/y5gM9gl.png)][sheetp]
[![](https://i.imgur.com/ISK2Y2H.png)][sheetp]
[![](https://i.imgur.com/NOR5AXd.png)][sheetp]
[![](https://i.imgur.com/4t2DUj6.png)][sheetp]
[![](https://i.imgur.com/HFj4ekD.png)][sheetp]
[![](https://i.imgur.com/rbFw4qd.png)][sheetp]
[![](https://i.imgur.com/OIDxgPG.png)][sheetp]
[![](https://i.imgur.com/AU6ovly.png)][sheetp]
[![](https://i.imgur.com/whPdc5q.png)][sheetp]
[![](https://i.imgur.com/Pv23ADO.png)][sheetp]
[![](https://i.imgur.com/UcVX2Iw.png)][sheetp]
[![](https://i.imgur.com/uE4xgar.png)][sheetp]
[![](https://i.imgur.com/ksKYoJu.png)][sheetp]
[![](https://i.imgur.com/8XmbumX.png)][sheetp]
[![](https://i.imgur.com/zqaiNHS.png)][sheetp]
[![](https://i.imgur.com/2yyzkCe.png)][sheetp]
[![](https://i.imgur.com/QMhUn6q.png)][sheetp]
[![](https://i.imgur.com/nFZWD2W.png)][sheetp]
[![](https://i.imgur.com/t8WY9Oh.png)][sheetp]
[![](https://i.imgur.com/ayd3Hsy.png)][sheetp]
[![](https://i.imgur.com/n2qsAWp.png)][sheetp]
[![](https://i.imgur.com/2LK8Y9V.png)][sheetp]

[![](https://i.imgur.com/6mwkqae.png)][sheetp]
[![](https://i.imgur.com/nxLuCFX.png)][sheetp]
[![](https://i.imgur.com/4mYngoh.png)][sheetp]

<br>
<br>


## References

- [STIC-D: Algorithmic Techniques For Efficient Parallel Pagerank Computation on Real-World Graphs](https://gist.github.com/wolfram77/bb09968cc0e592583c4b180243697d5a)
- [Adjusting PageRank parameters and Comparing results](https://arxiv.org/abs/2108.02997)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/KExwVG1.jpg)](https://www.youtube.com/watch?v=A7TKQKAFIi4)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/p6YDtgaxBgbMGSGx7
[sheets]: https://docs.google.com/spreadsheets/d/1g8AkDolNHqvvabhX0KYIaOwc5h-lLRUnCgJ8an-uewQ/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vRSPTTcoZOi7bscVuSxt3tZkv_6K7ruE8IMPaspO_blfKNdRltiujFrz3w2me1QVmbtA-aCvXNDNC6g/pubhtml
