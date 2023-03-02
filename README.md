Exploration of **optimizations** to *PageRank algorithm* for link analysis.

<br>


### Splitting Components

This experiment ([split-components]) was for comparing performance between
finding PageRank **without optimization**, finding PageRank with vertices
**split by components**, and finding PageRank with components **sorted in**
**topological order**. Each approach was attempted on a number of graphs, running
each approach 5 times to get a good time measure.

It seems **splitting vertices by components decreases execution time by**
**0-38%**, when compared to no optimization. This speedup is mostly observed on
**road networks** and **web graphs**. However, sorting components in topological
order seems to provide negligible additional speedup. With respect to
**GM-RATIO**, *splitting vertices by components* completes in **13% less time**
**(1.15x)** than using default vertex order. Sorting components in topological
order provides no additional improvement. With respect to **AM-RATIO**,
*splitting vertices by components* completes in **14% less time (1.16x)** than
using default vertex order. *Sorting components in topological order*  completes
in **15% less time (1.18x)** than using default vertex order. The speedup
associated with *splitting of vertices by components* could be attributed to an
*increase in cache hit ratio* when accessing the rank vector for PageRank
computation. This is because when vertices are grouped by components, the ranks
of vertices in each component would be close together. As edges within a
component tend to be higher than cross component edges, ranks of in-edge
vertices are more likely to be found in the cache. For road networks, like
`germany_osm` which only have *one connected component*, the speedup is possibly
because of the *vertex reordering* caused by `dfs()` which is required for
splitting by components.

[split-components]: https://github.com/puzzlef/pagerank-optimization/tree/split-components

<br>


### Skipping In-identical vertices

This experiment ([skip-inidenticals]) was for comparing performance between
finding PageRank **without optimization**, and finding PageRank **skipping rank**
**calculation of in-identical vertices**. Each approach was attempted on a number
of graphs, running each approach 5 times to get a good time measure. The minimum
size of *in-identical groups* is varied from 2-256, with 2 being the default
(`skip2`), and the best among them is also picked (`skipbest`).

It seems **skipping all in-identicals** *(skip2)* **decreases execution time by**
**-36 to 34%**, while **skipping in-identicals with best group size or more**
*(skipbest)* **decreases execution time by 0 to 34%**, when compared to no
optimization. This speedup is mainly observed on `indochina-2004`, and hardly
any on the other graphs. This speedup could be due to the fact that the graph
`indochina-2004` has a large number of **in-identicals** and **in-identical**
**groups**, although it doesn't have the highest **in-identicals %** or the
highest **avg. in-identical group size**. With respect to **GM-RATIO**,
*skipping in-identicals (skip2)* completes in **4% more time (0.96x)**, and
*skipping best in-identicals (skipbest)* completes in **4% less time (1.04x)**,
than using default approach. With respect to **AM-RATIO**, *skipping*
*in-identicals (skip2)* completes in **4% less time (1.04x)**, and *skipping best*
*in-identicals (skipbest)* completes in **10% less time (1.11x)**, than using
default approach. It therefore makes sense to apply this optimization only when
the graph has a large number of in-identicals.

[skip-inidenticals]: https://github.com/puzzlef/pagerank-optimization/tree/skip-inidenticals

<br>


### Skipping Chain vertices

This experiment ([skip-chains]) was for comparing performance between finding
PageRank **without optimization**, and finding PageRank **skipping rank**
**calculation of chain vertices**. Each approach was attempted on a number of
graphs, running each approach 5 times to get a good time measure. The minimum
size of *chains* is varied from 2-256, with 2 being the default (`skip2`), and
the best among them is also picked (`skipbest`). A **chain** here means a set of
*uni-directional* *links* connecting one vertex to the next, without any
additional edges. *Bi-directional links* are **not** considered as **chains**.
Note that most graphs don't have enough chains to provide an advantage. Road
networks do have chains, but they are *bi-directional*, and thus not considered
here.

It seems **skipping all chains** *(skip2)* **decreases execution time by -7 to**
**11%**, while **skipping chains with best group size or more** *(skipbest)*
**decreases execution time by 0 to 11%**, when compared to no optimization.
Please note that some other these small speedups can be attributed to randomness
(execution time has small variations). With respect to **GM-RATIO**, *skipping*
*chains (skip2)* and *skipping best chains (skipbest)* completes in **1% less**
**time (1.01x)** than using default approach. With respect to **AM-RATIO**,
*skipping chains (skip2)* completes in **2% less time (1.02x)**, and *skipping*
*best chains (skipbest)* completes in **3% less time (1.03x)**, than using
default approach. It therefore makes sense to apply this optimization only when
the graph has a large number of chains.

[skip-chains]: https://github.com/puzzlef/pagerank-optimization/tree/skip-chains

<br>


### Skipping Converged vertices

This experiment ([skip-converged]) was for comparing performance between:
1. Find PageRank **without optimization**.
2. Find PageRank *skipping converged vertices* **with re-check** (in `2`-`16` turns).
3. Find PageRank *skipping converged vertices* **after several turns** (in `2`-`64` turns).

Each approach was attempted on a number of graphs, running each approach 5
times to get a good time measure. **Skip with re-check** (`skip-check`) is
done every `2`-`16` turns. **Skip after turns** (`skip-after`) is done after
`2`-`64` turns.

Results indicate that the optimizations provide an improvement on
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

[skip-converged]: https://github.com/puzzlef/pagerank-optimization/tree/skip-converged

<br>


### Other experiments

- [iteration-aitken-extrapolation](https://github.com/puzzlef/pagerank-optimization/tree/iteration-aitken-extrapolation)

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
