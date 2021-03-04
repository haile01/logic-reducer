//19CTT2
//19125006
//Le Dinh Hai

#ifndef Solver_h
#define Solver_h

#define fi first
#define se second

#include <bits/stdc++.h>
using namespace std;

class Solver {
private:
  int n;
  vector < pair <int*, vector <int> > > *a;
public:
  Solver (): n(0), a(nullptr) {};
  
  void input () {
    cout << "Input number of variables n (1 <= n <= 4): ";
    cin >> n;
    cout << "input number of distinct positive states q (0 <= q <= 2^n): ";
    int q;
    cin >> q;
    a = new vector <pair <int*, vector<int> > > [n];
    for (int i = 0; i < q; i++) {
      cout << "Input the " << i + 1 << "th state (variables are separated): ";
      a[0].push_back(make_pair(new int[4], vector <int> (1, i)));
      for (int j = 0; j < n; j++)
        cin >> a[0][i].fi[j];
    }
  }

  bool check (int* a, int* b) {
    bool res = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] != b[i]) {
        if (res) {
          return 0;
        }
        else
          res = 1;
      }
    }
    return res;
  }

  pair<int*, vector<int> > merge (pair<int*, vector<int> > a, pair<int*, vector<int> > b) {
    pair <int*, vector<int> > res;

    // Merge int array
    res.fi = new int[n];
    for (int i = 0; i < n; i++)
      if (a.fi[i] == b.fi[i])
        res.fi[i] = a.fi[i];
      else
        res.fi[i] = -1;

    // Merge vector
    int i = 0, j = 0;
    while (i < a.se.size() && j < b.se.size()) {
      if (a.se[i] < b.se[j])
        res.se.push_back(a.se[i++]);
      else if (a.se[i] > b.se[j])
        res.se.push_back(b.se[j++]);
      else {
        res.se.push_back(a.se[i]);
        i++;
        j++;
      }
    }
    while (i < a.se.size()) res.se.push_back(a.se[i++]);
    while (j < b.se.size()) res.se.push_back(b.se[j++]);

    return res;
  }

  bool search (int t, int* tmp) {
    for (auto _ : a[t]) {
      int *v = _.fi;
      bool equal = 1;
      for (int i = 0; i < n; i++)
        equal &= v[i] == tmp[i];
      if (equal)
        return 1;
    }
    return 0;
  }

  void solve () {
    for (int t = 0; t < n - 1; t++) {
      for (int i = 0; i < (int)a[t].size() - 1; i++) 
        for (int j = i + 1; j < a[t].size(); j++) {
          if (check(a[t][i].fi, a[t][j].fi)) {
            pair <int*, vector<int> > tmp = merge(a[t][i], a[t][j]);
            if (!search(t + 1, tmp.fi))
              a[t + 1].push_back(tmp);
            else {
              delete[] tmp.fi;
            }
          }
        }
    }
  }

  void print () {
    for (int t = 0; t < n; t++) {
      cout << "Step " << t << "\n";
      for (int i = 0; i < a[t].size(); i++) {
        for (int j = 0; j < n; j++)
          cout << a[t][i].fi[j] << " ";
        cout << "( ";
        for (int j : a[t][i].se)
          cout << j << " ";
        cout << ")\n";
      }
    }
  }

  ~Solver () {
    for (int i = 0; i < n; i++) {
      for (auto b : a[i]) {
        delete[] b.fi;
      }
    }
    delete[] a;
  }
};

#endif /* Solver_h */
