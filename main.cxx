#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, int repeat) {
  enum NormFunction { L0=0, L1=1, L2=2, Li=3 };
  vector<float> *init = nullptr;

  // Find pagerank using plain power-iteration based PageRank.
  auto a1 = pagerankPlain(x, xt, init, {repeat, L1});
  auto e1 = l1Norm(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankPlain\n", a1.time, a1.iterations, e1);

  // Find pagerank using power-iteration based PageRank with Aitken extrapolation.
  for (int AS=1; AS<=16; AS*=2) {
    auto a2 = pagerankAitken(xt, init, {repeat, L1, AS});
    auto e2 = l1Norm(a2.ranks, a1.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankAitken [aitken-step=%d]\n", a2.time, a2.iterations, e2, AS);
  }
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
