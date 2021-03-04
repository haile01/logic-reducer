#include "Solver.h"

#include <bits/stdc++.h>
using namespace std;

int main () {
  Solver *s = new Solver();
  s->input();
  s->solve();
  s->print();
  //s.output;
  delete s;
}
