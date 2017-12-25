#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <deque>
#include <utility>

using namespace std;


int
main()
{
	vector<pair<int,int>> d;

	int a, b;
	char _;
	while (cin >> a >> _ >> b)
		d.emplace_back(a, b);

	deque<pair<int,vector<pair<int,int>>>> q{ {0,{}} };

	int p1 = 0;
	int p2 = 0, p2l = 0;
	while (!empty(q)) {
		auto [s, v] = q.front();
		q.pop_front();

		int sum = accumulate(begin(v), end(v), 0,
		    [](int i, auto &g) { return i + g.first + g.second; });
		p1 = max(p1, sum);
		if (size(v) > p2l) {
			p2 = 0;
			p2l = size(v);
		}
		if (p2l == size(v))
			p2 = max(p2, sum);

		for (auto p : d)
			if (p.first == s || p.second == s) {
				if (find(begin(v), end(v), p) != end(v))
					continue;
			
				vector v2 = v;
				v2.emplace_back(p);
				q.emplace_back(p.first == s ? p.second : p.first, v2);
			}
	}

	cout << p1 << endl << p2 << endl;	// 2006 1994
}
