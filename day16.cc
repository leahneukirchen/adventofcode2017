#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>

using namespace std;

int
main() {
	string d;
	cin >> d;

	string s(16, ' ');
	iota(begin(s), end(s), 'a');
	
	map<string, int> seen;

        for (int p1 = 0; seen.emplace(s, p1).second; p1++) {
		char c;
		istringstream iss{d};
		while (iss >> c) {
			if (c == 's') {
				int r;
				iss >> r >> c;
				rotate(begin(s), end(s) - r, end(s));
			} else if (c == 'x') {
				int x, y;
				iss >> x >> c >> y >> c;
				swap(s[x], s[y]);
			} else if (c == 'p') {
				char x, y;
				iss >> x >> c >> y >> c;
				swap(s[s.find(x)], s[s.find(y)]);
			}
		}
	}

	for (auto &[k, v] : seen) if (v == 1) cout << k << endl;

	int n = 1'000'000'000UL % size(seen);
	for (auto &[k, v] : seen) if (v == n) cout << k << endl;
}
