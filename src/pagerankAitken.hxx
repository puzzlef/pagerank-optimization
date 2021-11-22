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




// PAGERANK-CALCULATE
// ------------------
// For rank calculation from in-edges.

template <class T>
void pagerankAitkenCalculate(vector<T>& a, const vector<T>& r, const vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, int i, int n, T c0) {
  const T DE = 1e-16;                                 // if denominator smaller than this, dont use aitken interpolation!
  for (int v=i; v<i+n; v++) {
    T x0 = a[v], x1 = r[v], x2 = c0 + sumAt(c, sliceIter(efrom, vfrom[v], vfrom[v+1]));
    T de = (x2-x1) - (x1-x0);                         // aitken denominator
    a[v] = abs(de)<DE? x2 : x2 - (x2-x1)*(x2-x1)/de;  // aitken interpolate, only if denominator not too small!
  }
}




// PAGERANK-LOOP
// -------------

template <class T>
int pagerankAitkenLoop(vector<T>& a, vector<T>& r, vector<T>& c, const vector<T>& f, const vector<int>& vfrom, const vector<int>& efrom, int i, int n, int N, T p, T E, int L, int EF, int AS) {
  T  c0 = (1-p)/N;
  int l = 0;
  while (l<L) {
    if (l==0 || l%AS!=0) pagerankCalculate(a, c, vfrom, efrom, i, n, c0);
    else pagerankAitkenCalculate(a, r, c, vfrom, efrom, i, n, c0);  // assume contribtions (c) is precalculated
    T el = pagerankError(a, r, i, n, EF); ++l;                      // one iteration complete
    if (el<E || l>=L) break;                                        // check tolerance, iteration limit
    multiply(c, a, f, i, n);                                        // update partial contributions (c)
    swap(a, r);                                                     // final ranks always in (a)
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
