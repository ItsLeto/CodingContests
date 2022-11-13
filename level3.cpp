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

vector<string> grid;
enum class Dir { U, D, L, R };
struct G {
  bool isPac{false};
  int coins{0};
  vector<Dir> m;
  int x, y;
  void move(Dir d) {
    if (d == Dir::D) {
      ++y;
      if (isPac) cout << "moving Dir::D\n";
    }
    if (d == Dir::U) {
      --y;
      if (isPac) cout << "moving Dir::U\n";
    }
    if (d == Dir::L) {
      --x;
      if (isPac) cout << "moving Dir::L\n";
    }
    if (d == Dir::R) {
      ++x;
      if (isPac) cout << "moving Dir::R\n";
    }

    if (!isPac) {
      if (grid[y][x] == 'W') {
        cout << "inside wall\n";
      }
    } else {
      debug() << imie(x) << imie(y) << imie(coins);
    }
  }
  void collectCoin() {
    if (grid[y][x] == 'C') {
      grid[y][x] = '_';
      ++coins;
    }
  }
  bool collides(vector<G> gs) {
    if (grid[y][x] == 'W') {
      cout << "collision with wall\n";
      return true;
    }
    for (auto g : gs) {
      if (g.x == x && g.y == y) {
        cout << "collision with ghost\n";
        return true;
      }
    }
    return false;
  }
};
/******************************************************************************/
void solve() {
  int i, j, n, m;
  int lines;
  bool survived = true;

  cin >> lines;
  grid.reserve(lines);
  char buf[10000];

  m = 0;
  fo(i, lines) {
    cin >> buf;
    string s(buf);
    memset(buf, 0, 1000);
    m += count(s.begin(), s.end(), 'C');
    grid.push_back(s);
  }
  debug() << imie(m);

  G pac;
  pac.isPac = true;
  cin >> pac.y;
  cin >> pac.x;
  --pac.x;
  --pac.y;

  assert(pac.y < grid.size());
  assert(grid[pac.y][pac.x] == 'P');
  int l;
  int coins;
  cin >> l;
  fo(i, l) {
    assert(pac.x < grid[pac.y].size());
    char d;
    cin >> d;
    if (d == 'D') pac.m.push_back(Dir::D);
    if (d == 'U') pac.m.push_back(Dir::U);
    if (d == 'L') pac.m.push_back(Dir::L);
    if (d == 'R') pac.m.push_back(Dir::R);
  }

  int numGs;  // ghosts
  cin >> numGs;
  vector<G> gs(numGs);
  assert(numGs == gs.size());

  for (auto &g : gs) {
    cin >> g.y;
    cin >> g.x;
    --g.x;
    --g.y;
    cin >> l;
    fo(i, l) {
      char d;
      cin >> d;
      if (d == 'D') g.m.push_back(Dir::D);
      if (d == 'U') g.m.push_back(Dir::U);
      if (d == 'L') g.m.push_back(Dir::L);
      if (d == 'R') g.m.push_back(Dir::R);
    }
  }

  string path = "";
  fo(i, l) {
    pac.move(pac.m[i]);

    for (auto &g : gs) {
      g.move(g.m[i]);
    }

    if (pac.collides(gs)) {
      survived = false;
      break;
    };

    path += grid[pac.y][pac.x];
    pac.collectCoin();
  }
  cout << path << endl << count(all(path), 'C') << endl;

  ofstream outdata;               // outdata is like cin
  outdata.open("output/output");  // opens the file
  if (!outdata) {                 // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  outdata << pac.coins << " " << (survived ? "YES" : "NO") << endl;
  outdata.close();
}

/******************************************************************************/
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());

  solve();

  return 0;
}
