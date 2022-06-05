#pragma once

#include <algorithm>
#include <queue>
#include <vector>

#include "argument.h"
#include "define.h"
#include "edge.h"

// const int wpl = 5;

class Spade {
 private:
  struct Edge {
    int to;
    wt_t wt;
  };
  struct Node {
    int id;
    wt_t wt;
    bool operator<(const Node &b) const {
      if (wt != b.wt) return wt > b.wt;
      if (id != b.id) return id > b.id;
      return false;
    }
  };
  int n_;
  bool grouping_;
  std::vector<std::vector<Edge>> edge_;
  std::vector<int> cnt_;
  std::vector<wt_t> val_;
  std::vector<int> pos_;
  std::vector<int> seq_;
  std::vector<int> vtx_;
  std::vector<int> deg_;

  std::vector<wt_t> sus_;
  wt_t res_;
  std::vector<::Edge> buff_;

  e_arg_t e_arg;
  v_arg_t v_arg;

  wt_t (*e_ptr)(const e_arg_t &) = e_susp_def;
  wt_t (*v_ptr)(const v_arg_t &) = v_susp_def;

  wt_t insert(const ::Edge &edge) {
    int u = edge.u, v = edge.v;
    e_arg.deg_from = deg_[u];
    e_arg.deg_to = deg_[v];
    e_arg.weight = edge.w;
    return e_ptr(e_arg);
  }

 public:
  void detect(int n, const std::vector<::Edge> &edge) {
    n_ = n;
    grouping_ = false;
    edge_.assign(n_ + 1, {});
    cnt_.assign(n_ + 1, 0);
    val_.assign(n_ + 1, 0);
    pos_.assign(n_ + 1, -1);
    seq_.clear();
    seq_.reserve(n_ + 1);
    vtx_.clear();
    vtx_.reserve(n_ + 1);
    deg_.assign(n_ + 1, 0);
    sus_.assign(n_ + 1, 0);
    buff_.clear();
    // buff_.reserve(n_);
    // wt_t wt_sum = 0;
    for (const auto &ed : edge) {
      int u = ed.u, v = ed.v;
      // deg_[u]++; deg_[v]++;
      // e_arg.deg_from = deg_[u];
      // e_arg.deg_to = deg_[v];

      wt_t w = insert(ed);
      val_[u] += w;
      edge_[u].push_back({v, w});
      val_[v] += w;
      edge_[v].push_back({u, w});
    }
    std::priority_queue<Node> que;
    for (int i = 1; i <= n_; ++i) que.push({i, val_[i]});
    // wt_t dl_sum = 0;
    while (!que.empty()) {
      int u = que.top().id;
      que.pop();
      if (~pos_[u]) continue;
      pos_[u] = seq_.size();
      seq_.push_back(u);
      for (const auto &ed : edge_[u]) {
        int v = ed.to;
        wt_t w = ed.wt;
        if (pos_[v] == -1) {
          // dl_sum += w;
          val_[v] -= w;
          que.push({v, val_[v]});
        }
      }
    }
    seq_.push_back(0);
    val_[0] = inf;
    wt_t sum = 0;
    res_ = 0;
    for (int i = n_ - 1; i >= 0; i--) {
      sum += val_[seq_[i]];
      res_ = std::max(res_, sum / (n_ - i));
    }
  }
  void inque(int u, int &ptl, int &ptr, std::vector<int> &vtx_,
             std::priority_queue<Node> &que) {
    if (vtx_.size() && vtx_.back() == u) vtx_.pop_back();
    for (const auto &ed : edge_[u]) {
      int v = ed.to;
      wt_t w = ed.wt;
      if (pos_[v] > pos_[u])
        cnt_[v]++;
      else if (pos_[v] == -1)
        val_[u] += w;
    }
    pos_[u] = -1;
    que.push({u, val_[u]});
    cnt_[u] = 0;
    ptr++;
    if (ptr > n_) puts("ERROR");
  }
  void outque(int u, int &ptl, int &ptr, std::vector<int> &vtx_,
              std::priority_queue<Node> &que) {
    if (u != que.top().id) puts("Outque ERROR!");
    que.pop();
    seq_[ptl] = u;
    pos_[u] = ptl;
    ptl++;
    for (const auto &ed : edge_[u]) {
      int v = ed.to;
      wt_t w = ed.wt;
      if (pos_[v] > pos_[u])
        cnt_[v]--;
      else if (pos_[v] == -1)
        que.push({v, val_[v] = val_[v] - w});
    }
    if (ptl > n_) puts("ERROR");
  }
  void insertbatchedges(const std::vector<::Edge> &edge) {
    if (grouping_){
        for (const auto &ed : edge) {
            delay(ed);
        }
    } else {
        for (const auto &ed: edge) {
            int u = ed.u, v = ed.v;
            wt_t w = insert(ed);
            if (pos_[u] > pos_[v]) std::swap(u, v);
            vtx_.push_back(u);
            val_[u] += w;
            edge_[u].push_back({v, w});
            edge_[v].push_back({u, w});
        }
        std::sort(vtx_.begin(), vtx_.end(),
                  [this](int u, int v) { return pos_[u] > pos_[v]; });
        vtx_.resize(unique(vtx_.begin(), vtx_.end()) - vtx_.begin());
        while (vtx_.size()) {
            std::priority_queue<Node> que;
            int ptl = pos_[vtx_.back()], ptr = pos_[vtx_.back()];
            inque(vtx_.back(), ptl, ptr, vtx_, que);
            while (true) {
                while (!que.empty()) {
                    if (pos_[que.top().id] == -1) break;
                    que.pop();
                }
                if (que.empty()) break;
                int u = seq_[ptr];
                int v = que.top().id;
                if (cnt_[u] || vtx_.size() && u == vtx_.back())
                    inque(u, ptl, ptr, vtx_, que);
                else if (val_[v] < val_[u] || val_[v] == val_[u] && v < u)
                    outque(v, ptl, ptr, vtx_, que);
                else {
                    seq_[ptl] = u;
                    pos_[u] = ptl;
                    ptl++;
                    ptr++;
                }
            }
        }
    }
    // for (int i = 1; i <= n_; i++)
    //   if (cnt_[i]) puts("Cnt not recovered!");
  }
  void TurnOnEdgeGrouping(){
      grouping_ = true;
  }
  void delay(const ::Edge &e) {
    buff_.push_back(e);
    wt_t w=insert(e);
    sus_[e.u] += w;
    sus_[e.v] += w;
    if (sus_[e.u] > res_ || sus_[e.v] > res_) {
      printf("Delay add Edge Size = %lu\n", buff_.size());
      clock_t tst1 = clock();
      insertbatchedges(buff_);
      clock_t tst2 = clock();
      printf("Time Spent: %.6f\n", (tst2 - tst1) * 1.0 / CLOCKS_PER_SEC);
      buff_.clear();
      sus_.assign(n_ + 1, 0);
      wt_t sum = 0;
      res_ = 0;
      for (int i = n_ - 1; i >= 0; i--) {
        sum += val_[seq_[i]];
        res_ = std::max(res_, sum / (n_ - i));
      }
      printf("New Density: %.6f\n", res_);
    }
  }
  void writeMax() {
    std::vector<wt_t> sum;
    sum.assign(n_ + 1, 0);
//     for (int i = 0; i < n_; i++) printf("%lld ", val_[seq_[i]]);
    puts("");
    for (int i = n_ - 1; i >= 0; i--) sum[i] = sum[i + 1] + val_[seq_[i]];
    double mx = 0;
    int pos;
    for (int i = 0; i < n_; i++)
      if (sum[i] / (n_ - i) > mx) {
        mx = sum[i] / (n_ - i);
        pos = i;
      }
    printf("sequence\t");
    for (int i = 0; i < n_; i++) printf("%d ", seq_[i]);
    printf("\n");
    printf("density = %.5f, %d Nodes\n", mx, n_ - pos);
  }
  void eSusp(wt_t (*susp)(const e_arg_t &arg)){
    e_ptr=susp;
  }
  void vSusp(wt_t (*susp)(const v_arg_t &arg)){
    v_ptr=susp;
  }
};