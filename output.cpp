#include <bits/stdc++.h>
#define pb push_back
#define REP(i, n) for (signed long long i = 0; i < (n); i++)
#define MOD 1000000007
#define INF 98765431219876543
#define bitcnt(a) (ll) __builtin_popcount((a))
#define lb(a, b) lower_bound((a).begin(), (a).end(), (b))
#define ub(a, b) upper_bound((a).begin(), (a).end(), (b))

using namespace std;

typedef long long ll;
typedef pair<ll, ll> P;
typedef pair<ll, P> TP;
typedef pair<string, string> PS;

class calc {
public:
  char c;

  void solve() {
    cin >> c;
    switch (c) {
    case 'A':
      cout << 'T';
      break;
    case 'T':
      cout << 'A';
      break;
    case 'C':
      cout << 'G';
      break;
    case 'G':
      cout << 'C';
      break;
    };
  };
};
int main() {
  calc t;
  t.solve();
  cout << endl;
};
