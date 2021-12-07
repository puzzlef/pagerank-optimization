#pragma once
#include <cmath>
#include <vector>
#include <algorithm>
#include "_main.hxx"
#include "vertices.hxx"
#include "edges.hxx"
#include "csr.hxx"
#include "chains.hxx"
#include "pagerank.hxx"

using std::vector;
using std::swap;
using std::abs;




// PAGERANK-CHAINS
// ---------------

template <class G, class H, class J, class T>
auto pagerankChains(const G& x, const H& xt, const J& ks, const PagerankOptions<T>& o) {
  if (!o.skipChains) return vector2d<int>();
  auto id = indices(ks);
  auto a  = chains(x, xt);
  for (auto& vs : a) {
    for (int i=0; i<vs.size(); i++)
      vs[i] = id[vs[i]];
  }
  return a;
}


void pagerankMarkChains(vector<int>& vfrom, const vector2d<int>& vchin) {
  for (const auto& vs : vchin) {
    for (int i=1; i<vs.size(); i++)
      vfrom[vs[i]] = -abs(vfrom[vs[i]]);
  }
}



// PAGERANK-FACTOR
// ---------------
// For contribution factors of vertices (unchanging).

template <class T>
void pagerankFactor(vector<T>& a, const vector<int>& vdata, int i, int n, T p) {
  for (int u=i; u<i+n; u++) {
    int d = vdata[u];
    a[u] = d>0? p/d : 0;
  }
}




// PAGERANK-TELEPORT
// -----------------
// For teleport contribution from vertices (inc. dead ends).

template <class T>
T pagerankTeleport(const vector<T>& r, const vector<int>& vdata, int N, T p) {
  T a = (1-p)/N;
  for (int u=0; u<N; u++)
    if (vdata[u] == 0) a += p*r[u]/N;
  return a;
}




// PAGERANK-CALCULATE
// ------------------
// For rank calculation from in-edges.

template <class T>
void pagerankCalculate(vector<T>& a, const vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, int i, int n, T c0) {
  for (int v=i; v<i+n; v++) {
    if (vfrom[v]<0) continue;
    a[v] = c0 + sumAt(c, sliceIter(efrom, abs(vfrom[v]), abs(vfrom[v+1])));
  }
}


template <class T>
void pagerankCalculateChains(vector<T>& a, const vector<T>& r, const vector2d<int>& vchin, T p, T c0) {
  for (const auto& vs : vchin) {
    for (int i=1; i<vs.size(); i++) {
      T pi = pow(p, i);
      a[vs[i]] = ((1-pi)/(1-p)) * c0 + pi * r[vs[0]];
    }
  }
}




// PAGERANK-ERROR
// --------------
// For convergence check.

template <class T>
T pagerankError(const vector<T>& x, const vector<T>& y, int i, int N, int EF) {
  switch (EF) {
    case 1:  return l1Norm(x, y, i, N);
    case 2:  return l2Norm(x, y, i, N);
    default: return liNorm(x, y, i, N);
  }
}




// PAGERANK
// --------
// For Monolithic / Levelwise PageRank.

template <class G, class H, class J, class M, class FL, class T=float>
PagerankResult<T> pagerankSeq(const G& x, const H& xt, const J& ks, int i, const M& ns, FL fl, const vector<T> *q, const PagerankOptions<T>& o) {
  int  N  = xt.order();
  T    p  = o.damping;
  T    E  = o.tolerance;
  int  L  = o.maxIterations, l = 0;
  int  EF = o.toleranceNorm;
  auto vfrom = sourceOffsets(xt, ks);
  auto efrom = destinationIndices(xt, ks);
  auto vdata = vertexData(xt, ks);
  auto vchin = pagerankChains(x, xt, ks, o);
  pagerankMarkChains(vfrom, vchin);
  vector<T> a(N), r(N), c(N), f(N), qc;
  if (q) qc = compressContainer(xt, *q, ks);
  float t = measureDurationMarked([&](auto mark) {
    if (q) copy(r, qc);    // copy old ranks (qc), if given
    else fill(r, T(1)/N);
    copy(a, r);
    mark([&] { pagerankFactor(f, vdata, 0, N, p); multiply(c, a, f, 0, N); });             // calculate factors (f) and contributions (c)
    mark([&] { l = fl(a, r, c, f, vfrom, efrom, vdata, vchin, i, ns, N, p, E, L, EF); });  // calculate ranks of vertices
  }, o.repeat);
  return {decompressContainer(xt, a, ks), l, t};
}
