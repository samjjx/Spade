#pragma once

struct e_arg_t {
  int deg_from, deg_to, weight;
};

struct v_arg_t {
  int attr;
};

double e_susp_def(const e_arg_t &e_arg){ return 0; }
double v_susp_def(const v_arg_t &v_arg){ return 0; }