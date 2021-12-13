Performance benefit of **skipping converged vertices** for PageRank ([pull], [CSR]).

This experiment was for comparing performance between:
1. Find PageRank **without optimization**.
2. Find PageRank *skipping converged vertices* **with re-check** (in `2`-`16` turns).
3. Find PageRank *skipping converged vertices* **after several turns** (in `2`-`64` turns).

Each approach was attempted on a number of graphs, running each approach 5
times to get a good time measure. **Skip with re-check** (`skip-check`) is
done every `2`-`16` turns. **Skip after turns** (`skip-after`) is done after
`2`-`64` turns.

Results indicate that the optimizations provide an improvement on only a
few graphs (without introducing too much error):
- For `web-BerkStan`, a `skip-check` of `11`/`14` appears to work best.
- For `indochina-2004`, a `skip-check` of `8`/`11`/`14`.
- For `coPapersDBLP`, a `skip-after` of `3+`.
- For other graphs, there is no improvement.

On average however, *neither* `skip-check`, nor `skip-after` gives
**better speed** than the **default (unoptimized) approach** (considering
the error introduced due to skipping). This could be due to the unnecessary
iterations added by `skip-check` (mistakenly skipped), and increased memory
accesses performed by `skip-after` (tracking converged count).

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
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [12334.815 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq
# [13071.717 ms; 051 iters.] [1.8342e-09 err.] pagerankSeq [skip-check=2]
# [13173.417 ms; 051 iters.] [7.7644e-09 err.] pagerankSeq [skip-check=3]
# [13119.878 ms; 051 iters.] [9.4246e-09 err.] pagerankSeq [skip-check=4]
# [13170.339 ms; 051 iters.] [1.7640e-08 err.] pagerankSeq [skip-check=6]
# [13161.589 ms; 051 iters.] [1.8983e-08 err.] pagerankSeq [skip-check=8]
# [13112.315 ms; 051 iters.] [5.4536e-08 err.] pagerankSeq [skip-check=11]
# [13147.400 ms; 051 iters.] [9.0132e-08 err.] pagerankSeq [skip-check=14]
# [13430.245 ms; 051 iters.] [1.3980e-08 err.] pagerankSeq [skip-after=2]
# [13484.869 ms; 051 iters.] [5.1652e-09 err.] pagerankSeq [skip-after=3]
# [13511.294 ms; 051 iters.] [3.5257e-09 err.] pagerankSeq [skip-after=4]
# [13437.141 ms; 051 iters.] [9.6918e-11 err.] pagerankSeq [skip-after=6]
# [13463.552 ms; 051 iters.] [9.0026e-12 err.] pagerankSeq [skip-after=8]
# [13505.490 ms; 051 iters.] [1.4921e-13 err.] pagerankSeq [skip-after=11]
# [13493.994 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=14]
# [13480.716 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=17]
# [13435.205 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=21]
# [13534.815 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=25]
# [13455.775 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=29]
# [13500.775 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=33]
# [13406.586 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=38]
# [13490.662 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=43]
# [13479.828 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=48]
# [13523.175 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=53]
# [13463.850 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=58]
# [14234.748 ms; 051 iters.] [0.0000e+00 err.] pagerankSeq [skip-after=63]
#
# ...
```

[![](https://i.imgur.com/YJ0aDrD.png)][sheetp]
[![](https://i.imgur.com/cOxymFd.png)][sheetp]
[![](https://i.imgur.com/v6jamNO.png)][sheetp]
[![](https://i.imgur.com/sy7cz0R.png)][sheetp]
[![](https://i.imgur.com/lA5j0sw.png)][sheetp]
[![](https://i.imgur.com/ks0rnz4.png)][sheetp]
[![](https://i.imgur.com/biPXzHg.png)][sheetp]
[![](https://i.imgur.com/R8bjJjp.png)][sheetp]
[![](https://i.imgur.com/HxMpA3n.png)][sheetp]
[![](https://i.imgur.com/FJ0kXQA.png)][sheetp]
[![](https://i.imgur.com/Z2vpeiY.png)][sheetp]
[![](https://i.imgur.com/LlzD1i3.png)][sheetp]
[![](https://i.imgur.com/IwB4u95.png)][sheetp]
[![](https://i.imgur.com/5q0PtWe.png)][sheetp]
[![](https://i.imgur.com/DAo4Aij.png)][sheetp]
[![](https://i.imgur.com/pDfLM8C.png)][sheetp]
[![](https://i.imgur.com/eLlq9WT.png)][sheetp]
[![](https://i.imgur.com/snpxNKs.png)][sheetp]
[![](https://i.imgur.com/u34XgO9.png)][sheetp]
[![](https://i.imgur.com/RFpD0S1.png)][sheetp]
[![](https://i.imgur.com/i37D992.png)][sheetp]
[![](https://i.imgur.com/H8DS3NF.png)][sheetp]
[![](https://i.imgur.com/sh5t6Hd.png)][sheetp]
[![](https://i.imgur.com/GdFu7Bm.png)][sheetp]
[![](https://i.imgur.com/mljyVRF.png)][sheetp]
[![](https://i.imgur.com/CW8APTG.png)][sheetp]
[![](https://i.imgur.com/MoSHrBC.png)][sheetp]
[![](https://i.imgur.com/F2yqTf5.png)][sheetp]
[![](https://i.imgur.com/gqa1kGQ.png)][sheetp]
[![](https://i.imgur.com/P2IPbdA.png)][sheetp]
[![](https://i.imgur.com/v4IroAl.png)][sheetp]
[![](https://i.imgur.com/wBUpfTI.png)][sheetp]
[![](https://i.imgur.com/RjXtjkd.png)][sheetp]
[![](https://i.imgur.com/0mWVL8C.png)][sheetp]

[![](https://i.imgur.com/zq7G4SE.png)][sheetp]
[![](https://i.imgur.com/073rnPX.png)][sheetp]
[![](https://i.imgur.com/tZt7WFP.png)][sheetp]

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
[![DOI](https://zenodo.org/badge/380470344.svg)](https://zenodo.org/badge/latestdoi/380470344)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://www.iiit.ac.in/people/faculty/kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/p6YDtgaxBgbMGSGx7
[sheets]: https://docs.google.com/spreadsheets/d/1g8AkDolNHqvvabhX0KYIaOwc5h-lLRUnCgJ8an-uewQ/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vRSPTTcoZOi7bscVuSxt3tZkv_6K7ruE8IMPaspO_blfKNdRltiujFrz3w2me1QVmbtA-aCvXNDNC6g/pubhtml
