#include "bits/stdc++.h"
#define LOCAL
using namespace std;
#define sim template <class c
#define ris return *this
#define dor > debug &operator<<
#define eni(x)       \
  template <class c> \
  typename enable_if<sizeof dud<c>(0) x 1, debug &>::type operator<<(c i) {
template <class c>
struct rge {
  c b, e;
};

template <class c>
rge<c> range(c i, c j) {
  return rge<c>{i, j};
}
template <class c>
auto dud(c *x) -> decltype(cerr << *x, 0);
template <class c>
char dud(...);

struct debug {
#ifdef LOCAL
  ~debug() { cerr << endl; }
  template <class c>
  typename enable_if<sizeof dud<c>(0) != 1, debug &>::type operator<<(c i) {
    cerr << boolalpha << i;
    return *this;
  }
  template <class c>
  typename enable_if<sizeof dud<c>(0) == 1, debug &>::type operator<<(c i) {
    return *this << range(begin(i), end(i));
  }

  template <class c, class b>
  debug &operator<<(pair<b, c> d) {
    return *this << "(" << d.first << ", " << d.second << ")";
  }
  template <class c>
  debug &operator<<(rge<c> d) {
    *this << "[";
    for (auto it = d.b; it != d.e; ++it) *this << ", " + 2 * (it == d.b) << *it;
    return *this << "]";
  }
#else
  template <class c>
  debug &operator<<(const c &) {
    return *this;
  }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define fo(i, n) for (i = 0; i < n; i++)
#define Fo(i, k, n) for (i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define si(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(s) scanf("%s", s)
#define pi(x) printf("%d\n", x)
#define pl(x) printf("%lld\n", x)
#define ps(s) printf("%s\n", s)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto &it : a)
#define PI 3.1415926535897932384626

using ul = unsigned long;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using pii = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpii = vector<pii>;
using vpl = vector<pl>;
using vvi = vector<vi>;
using vvl = vector<vl>;

/******************************************************************************/
void solve() {
  int i, j, n, m;
  int lines;

  cin >> lines;
  vector<string> grid;
  grid.reserve(lines);
  char buf[10000];

  m = 0;
  fo(i, lines) {
    cin >> buf;
    string s(buf);
    memset(buf, 0, 1000);
    m += count(s.begin(), s.end(), 'C');
    if (count(s.begin(), s.end(), 'P')) cout << "line: " << i << endl;
    grid.push_back(s);
    cout << i << ": " << grid.back() << endl;
  }
  debug() << imie(m);
  int posx, posy;
  cin >> posy;
  cin >> posx;
  --posx;
  --posy;

  debug() << imie(posy) << imie(posx);
  assert(posy < grid.size());
  debug() << imie(grid[0].size());
  assert(grid[posy][posx] == 'P');
  debug() << imie(grid[posy].c_str());
  debug() << imie(grid[posy][posx]);

  int l;
  int coins;
  cin >> l;
  fo(i, l) {
    assert(posx < grid[posy].size());
    char d;
    cin >> d;
    if (d == 'D') ++posy;
    if (d == 'U') --posy;
    if (d == 'L') --posx;
    if (d == 'R') ++posx;
    debug() << imie(grid[posy][posx]) << imie(posy) << imie(posx);
    if (grid[posy][posx] == 'C') {
      ++coins;
      grid[posy][posx] = '+';
    }
  }

  for (auto l : grid) {
    cout << l << endl;
  }

  ofstream outdata;               // outdata is like cin
  outdata.open("output/output");  // opens the file
  if (!outdata) {                 // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  outdata << coins << endl;
  outdata.close();
}

/******************************************************************************/
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());

  solve();

  return 0;
}
