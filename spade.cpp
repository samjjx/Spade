#include <cstdio>
#include <fstream>
#include <iostream>

#include "header/argument.h"
#include "header/define.h"
#include "header/spade.h"

using namespace std;

typedef pair<int, int> pii;

Spade spd;



// g++ main.cpp -std=c++17 -O3
double sec(clock_t tst) { return (tst + 0.0) / CLOCKS_PER_SEC; }

void loadgraph(string base, vector<Edge>& edg, vector<Edge>& inc, int &n){
    ifstream fin_gra(base + ".gra");
    ifstream fin_inc(base + ".inc");
    clock_t tst1, tst2;
    int m;
    fin_gra >> n >> m;
    int u, v;
    double w;

    while (fin_gra >> u >> v >> w) edg.push_back({u, v, w});
    fin_inc >> m;
    while (fin_inc >> u >> v >> w) inc.push_back({u, v, w});
}

wt_t e_susp_dg(const e_arg_t& e_arg) {
    return 1;
}

wt_t e_susp_fd(const e_arg_t& e_arg) {
    return 1.0/(e_arg.deg_to + 5);
}

wt_t e_susp_dw(const e_arg_t& e_arg) {
    return e_arg.weight;
}

int main(int argc, char* argv[]) {
  int n;
  string base = argv[1];
  vector<Edge> edg, inc;
  loadgraph(base, edg, inc, n);
  spd.eSusp(e_susp_dw);
  spd.detect(n, edg);
  spd.writeMax();

  // Preparing batches
  int k = atoi(argv[2]);
  for (int i = 0; i < inc.size(); i += k) {
    vector<Edge> arr;
    for (int j = i; j < inc.size() && j < i + k; j++) arr.push_back(inc[j]);
    spd.insertbatchedges(arr);
  }
  spd.writeMax();
  return 0;
}