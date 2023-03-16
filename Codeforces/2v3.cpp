#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define endl "\n"
#define int long long int
#define all(p) p.begin(), p.end()
#define debug(x) cout << #x << " " << x << endl;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
using namespace __gnu_pbds;
using namespace std;
const int Mod = 1000000007;
struct custom_hash
{
	static uint64_t splitmix64(uint64_t x)
	{
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	size_t operator()(uint64_t x) const
	{
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};
int power(int x, int p)
{
	if (p == 0)
		return 1;
	int ans = power((x * x) % Mod, p / 2) % Mod;
	if (p & 1)
		return (ans * x) % Mod;
	else
		return ans % Mod;
}
int max(int a, int b)
{
	return a > b ? a : b;
}
int min(int a, int b)
{
	return a < b ? a : b;
}
struct segment_tree
{
	vector<int> st;
	vector<int> lazy;
	int n;
	segment_tree() {}
	void init(int n)
	{
		this->n = n;
		st.resize(4 * n); // maximum size of array required to represent segment tree
		lazy.resize(4 * n);
	}
	void build(vector<int> ip)
	{
		build(ip, 0, n - 1, 0);
	}
	int query(int start, int ending)
	{
		return query(start, ending, 0, n - 1, 0);
	}
	void update(int left, int right, int value)
	{
		update(left, right, value, 0, n - 1, 0);
	}

private:
	void build(vector<int> &ip, int l, int r, int node)
	{
		if (l == r)
		{
			st[node] = ip[l];
			return;
		}
		int mid = (l + r) / 2;
		// building left and right subtree
		build(ip, l, mid, 2 * node + 1);
		build(ip, mid + 1, r, 2 * node + 2);
		// putting value of current node from its children
		st[node] = st[2 * node + 1] + st[2 * node + 2];
	}
	int query(int start, int ending, int l, int r, int node)
	{
		// no overlap case
		if (r < start || l > ending)
			return 0;
		if (lazy[node] != 0)
		{
			if (lazy[node] & 1)
				st[node] = ((r - l + 1) - st[node]);
			if (l != r)
			{
				lazy[2 * node + 1] += lazy[node];
				lazy[2 * node + 2] += lazy[node];
			}
			lazy[node] = 0;
		}
		// full overlap
		if (l >= start && r <= ending)
		{
			return st[node];
		}
		int mid = (l + r) / 2;
		// rest all cases to be handled by recusrion
		return query(start, ending, l, mid, 2 * node + 1) + query(start, ending, mid + 1, r, 2 * node + 2);
	}
	void update(int start, int end, int value, int l, int r, int node)
	{
		if (lazy[node] != 0)
		{
			if ((lazy[node] & 1) == 1)
				st[node] = ((r - l + 1) - st[node]);
			if (l != r)
			{
				lazy[2 * node + 1] += lazy[node];
				lazy[2 * node + 2] += lazy[node];
			}
			lazy[node] = 0;
		}
		if (l >= start && r <= end)
		{
			// cout<<l<<' '<<r<<" "<<st[node]<<" "<<lazy[node]<<endl;
			if ((value & 1) == 1)
				st[node] = ((r - l + 1) - st[node]);
			// cout << l << ' ' << r << " " << st[node] << " " << lazy[node] << endl;
			if (l != r)
			{
				lazy[2 * node + 1] += value;
				lazy[2 * node + 2] += value;
				// cout << l << ' ' << r << " " << st[2 * node + 1] << " " << lazy[2 * node + 1] << endl;
				// cout << l << ' ' << r << " " << st[2 * node + 2] << " " << lazy[2 * node + 2] << endl;
			}
			return;
		}
		if (end < l || start > r)
			return;
		int mid = (l + r) / 2;
		update(start, end, value, l, mid, 2 * node + 1);
		update(start, end, value, mid + 1, r, 2 * node + 2);
		st[node] = st[2 * node + 1] + st[2 * node + 2];
	}
};
/*-------------------------------------------------------------------------------------*/
void solve()
{
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	segment_tree *tree = new segment_tree();
	tree->init(n);
	tree->build(arr);
	for (int i = 1; i <= q; i++)
	{
		int a;
		cin >> a;
		if (a == 0)
		{
			// flip
			int l, r;
			cin >> l >> r;
			tree->update(l, r, 1);
		}
		else
		{
			// query
			int l, r;
			cin >> l >> r;
			cout << tree->query(l, r) << endl;
		}
	}
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
}