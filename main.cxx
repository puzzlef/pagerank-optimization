#include <vector>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, int repeat) {
  enum NormFunction { L0=0, L1=1, L2=2, Li=3 };
  vector<float> *init = nullptr;
  bool skipChains = true;

  // Find chains.
  auto ch = chains(x, xt);
  printf("chains: %d chain-vertices: %d {}\n", size(ch), size2d(ch));

  // Find pagerank without optimization.
  auto a1 = pagerankMonolithicSeq(x, xt, init, {repeat, L1});
  auto e1 = l1Norm(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeq\n", a1.time, a1.iterations, e1);

  // Find pagerank skipping rank calculation of chain vertices.
  auto a2 = pagerankMonolithicSeq(x, xt, init, {repeat, L1, skipChains});
  auto e2 = l1Norm(a2.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeq [skip]\n", a2.time, a2.iterations, e2);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 5;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtx(file); println(x);
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, repeat);
  printf("\n");
  return 0;
}
