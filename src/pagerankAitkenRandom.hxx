#pragma once
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include "_main.hxx"
#include "transpose.hxx"
#include "dynamic.hxx"
#include "pagerank.hxx"
#include "pagerankSeq.hxx"
#include "pagerankAitken.hxx"

using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::vector;
using std::swap;
using std::abs;
using std::min;
using std::max;




// PAGERANK-LOOP
// -------------

template <class T>
int pagerankAitkenRandomLoop(vector<T>& r2, vector<T>& r1, vector<T>& r0, vector<T>& c, const vector<T>& f, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int i, int n, int N, T p, T E, int L, int EF, int AS) {
  int l = 0, lp = 0;
  random_device dev;
  default_random_engine rnd(dev());
  uniform_int_distribution<> dis(0, AS-1);
  while (l<L) {
    T c0 = pagerankTeleport(r1, vdata, N, p);
    if (lp>0 && dis(rnd)==0) { pagerankAitkenCalculate(r0, r2, r1, r0, c, vfrom, efrom, i, n, c0); swap(r1, r2); swap(r2, r0); lp = 0; }
    else { pagerankCalculate(r2, c, vfrom, efrom, i, n, c0); ++lp; }  // assume contribtions (c) is precalculated
    T el = pagerankError(r2, r1, i, n, EF); ++l;                      // one iteration complete
    if (el<E || l>=L) break;                                          // check tolerance, iteration limit
    multiply(c, r2, f, i, n);                                         // update partial contributions (c)
    swap(r0, r1); swap(r1, r2);                                       // final ranks always in (r2)
  }
  return l;
}




// PAGERANK (STATIC / INCREMENTAL)
// -------------------------------

// Find pagerank using a single thread (pull, CSR).
// @param x  original graph
// @param xt transpose graph (with vertex-data=out-degree)
// @param q  initial ranks (optional)
// @param o  options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class H, class T=float>
PagerankResult<T> pagerankAitkenRandom(const G& x, const H& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  int  N  = xt.order();    if (N==0) return PagerankResult<T>::initial(xt, q);
  auto ks = vertices(xt);
  return pagerankSeq(xt, ks, 0, N, pagerankAitkenRandomLoop<T>, q, o);
}

template <class G, class T=float>
PagerankResult<T> pagerankAitkenRandom(const G& x, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  auto xt = transposeWithDegree(x);
  return pagerankAitkenRandom(x, xt, q, o);
}




// PAGERANK (DYNAMIC)
// ------------------

template <class G, class H, class T=float>
PagerankResult<T> pagerankAitkenRandomDynamic(const G& x, const H& xt, const G& y, const H& yt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  int  N = yt.order();                           if (N==0) return PagerankResult<T>::initial(yt, q);
  auto [ks, n] = dynamicVertices(x, xt, y, yt);  if (n==0) return PagerankResult<T>::initial(yt, q);
  return pagerankSeq(yt, ks, 0, n, pagerankAitkenRandomLoop<T>, q, o);
}

template <class G, class T=float>
PagerankResult<T> pagerankAitkenRandomDynamic(const G& x, const G& y, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  auto xt = transposeWithDegree(x);
  auto yt = transposeWithDegree(y);
  return pagerankAitkenRandomDynamic(x, xt, y, yt, q, o);
}
