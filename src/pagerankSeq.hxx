#pragma once
#include <vector>
#include <algorithm>
#include "_main.hxx"
#include "vertices.hxx"
#include "edges.hxx"
#include "csr.hxx"
#include "pagerank.hxx"

using std::vector;
using std::swap;




template <class G, class H, class T>
auto pagerankComponents(const G& x, const H& xt, const PagerankOptions<T>& o) {
  if (o.sortComponents) return sortedComponents(x, xt);
  else if (o.splitComponents) return components(x, xt);
  return vector2d<int> {vertices(xt)};
}


template <class T>
void pagerankFactor(vector<T>& a, const vector<int>& vdata, int i, int n, T p) {
  for (int u=i; u<i+n; u++) {
    int d = vdata[u];
    a[u] = d>0? p/d : 0;
  }
}


// Default.
template <class T>
void pagerankCalculate(vector<T>& a, const vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, int i, int n, T c0) {
  for (int v=i; v<i+n; v++)
    a[v] = c0 + sumAt(c, slice(efrom, vfrom[v], vfrom[v+1]));
}

// Skip converged for SC-1 turns.
template <class T>
void pagerankCalculate(vector<T>& a, const vector<T>& r, const vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, int i, int n, int l, int SC, T c0) {
  for (int v=i;v<i+n; v++) {
    if (a[v]==r[v] && l%SC!=0) continue;
    a[v] = c0 + sumAt(c, slice(efrom, vfrom[v], vfrom[v+1]));
  }
}

// Skip if converged for SA turns.
template <class T>
void pagerankCalculate(vector<T>& a, vector<int>& s, const vector<T>& r, const vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, int i, int n, int SA, T c0) {
  for (int v=i;v<i+n; v++) {
    if (s[v]>=SA) continue;
    a[v] = c0 + sumAt(c, slice(efrom, vfrom[v], vfrom[v+1]));
    if (a[v]==r[v]) s[v]++;
  }
}


template <class T>
int pagerankSeqLoop(vector<T>& a, vector<T>& r, vector<int>& s, vector<T>& c, const vector<T>& f, const vector<int>& vfrom, const vector<int>& efrom, int i, int n, int N, T p, T E, int L, int SC, int SA) {
  T  c0 = (1-p)/N;
  int l = 1;
  for (; l<L; l++) {
    multiply(c, r, f, i, n);
    if (SC>0) pagerankCalculate(a, r, c, vfrom, efrom, i, n, l, SC, c0);
    else if (SA>0) pagerankCalculate(a, s, r, c, vfrom, efrom, i, n, SA, c0);
    else pagerankCalculate(a, c, vfrom, efrom, i, n, c0);
    T el = l1Norm(a, r, i, n);
    if (el < E) break;
    swap(a, r);
  }
  return l;
}


// Find pagerank using a single thread (pull, CSR).
// @param xt transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class H, class T=float>
PagerankResult<T> pagerankSeq(const H& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  int  N = xt.order();
  T    p = o.damping;
  T    E = o.tolerance;
  int  L = o.maxIterations, l;
  int SC = o.skipCheck;
  int SA = o.skipAfter;
  auto vfrom = sourceOffsets(xt);
  auto efrom = destinationIndices(xt);
  auto vdata = vertexData(xt);
  vector<int> s(N);
  vector<T> a(N), r(N), c(N), f(N);
  float t = measureDurationMarked([&](auto mark) {
    fill(a, T());
    if (q) r = compressContainer(xt, *q);
    else fill(r, T(1)/N);
    fill(s, int());
    mark([&] { pagerankFactor(f, vdata, 0, N, p); });
    mark([&] { l = pagerankSeqLoop(a, r, s, c, f, vfrom, efrom, 0, N, N, p, E, L, SC, SA); });
  }, o.repeat);
  return {decompressContainer(xt, a), l, t};
}
