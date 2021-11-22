#pragma once
#include <cmath>
#include <vector>
#include <algorithm>
#include "_main.hxx"
#include "transpose.hxx"
#include "dynamic.hxx"
#include "pagerank.hxx"
#include "pagerankSeq.hxx"

using std::vector;
using std::swap;
using std::abs;
using std::min;
using std::max;




// PAGERANK-CALCULATE
// ------------------
// For rank calculation from in-edges.

template <class T>
T extrapolateAitken(T x2, T x1, T x0, T DE) {
  T de = (x2-x1)-(x1-x0);                           // aitken denominator
  return abs(de)<DE? x2 : x2 - (x2-x1)*(x2-x1)/de;  // aitken extrapolate, only if denominator not too small!
}

template <class T>
void pagerankAitkenCalculate(vector<T>& a, vector<T>& x2, const vector<T>& x1, const vector<T>& x0, const vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, int i, int n, T c0) {
  const T DE = 1e-16;                                                          // if denominator smaller than this, dont use aitken extrapolation!
  for (int v=i; v<i+n; v++) {
    x2[v] = c0 + sumAt(c, sliceIter(efrom, vfrom[v], vfrom[v+1]));
    a[v]  = min(max(extrapolateAitken(x2[v], x1[v], x0[v], DE), T(0)), T(1));  // ranks must be within limit!
  }
  // printf("x2: "); println(x2);
  // printf("a:  "); println(a);
}




// PAGERANK-LOOP
// -------------

template <class T>
int pagerankAitkenLoop(vector<T>& a, vector<T>& r, vector<T>& x2, vector<T>& x1, vector<T>& x0, vector<T>& c, const vector<T>& f, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, int i, int n, int N, T p, T E, int L, int EF, int AS) {
  int l = 0;
  while (l<L) {
    T c0 = pagerankTeleport(r, vdata, N, p);
    if (l<2 || l%AS!=0) { pagerankCalculate(x2, c, vfrom, efrom, i, n, c0); copy(a, x2); }
    else pagerankAitkenCalculate(a, x2, x1, x0, c, vfrom, efrom, i, n, c0);  // assume contribtions (c) is precalculated
    T el = pagerankError(a, r, i, n, EF); ++l;                               // one iteration complete
    if (el<E || l>=L) break;                                                 // check tolerance, iteration limit
    multiply(c, a, f, i, n);                                                 // update partial contributions (c)
    swap(a, r); swap(x0, x1); swap(x1, x2);                                  // final ranks always in (a)
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
PagerankResult<T> pagerankAitken(const G& x, const H& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  int  N  = xt.order();    if (N==0) return PagerankResult<T>::initial(xt, q);
  auto ks = vertices(xt);
  return pagerankSeq(xt, ks, 0, N, pagerankAitkenLoop<T>, q, o);
}

template <class G, class T=float>
PagerankResult<T> pagerankAitken(const G& x, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  auto xt = transposeWithDegree(x);
  return pagerankAitken(x, xt, q, o);
}




// PAGERANK (DYNAMIC)
// ------------------

template <class G, class H, class T=float>
PagerankResult<T> pagerankAitkenDynamic(const G& x, const H& xt, const G& y, const H& yt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  int  N = yt.order();                           if (N==0) return PagerankResult<T>::initial(yt, q);
  auto [ks, n] = dynamicVertices(x, xt, y, yt);  if (n==0) return PagerankResult<T>::initial(yt, q);
  return pagerankSeq(yt, ks, 0, n, pagerankAitkenLoop<T>, q, o);
}

template <class G, class T=float>
PagerankResult<T> pagerankAitkenDynamic(const G& x, const G& y, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  auto xt = transposeWithDegree(x);
  auto yt = transposeWithDegree(y);
  return pagerankAitkenDynamic(x, xt, y, yt, q, o);
}
