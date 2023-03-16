// Author: Shivank
//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define tc int t; cin >> t; while(t--)
#define all(v) v.begin(), v.end()

void solve() {
    int n; cin >> n;
    multiset<int> ms;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        ms.insert(x);
    }

    int ans = 0;
    while (!ms.empty()) {
        int a = *ms.begin();
        for (int i = a; ; i++) {
            if (ms.find(i) == ms.end()) {
                break;
            }
            ms.erase(ms.find(i));
        }
        ans++;
    }

    cout << ans << endl;

}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    tc{
        solve();
    }

}
