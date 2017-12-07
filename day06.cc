#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <map>

using namespace std;

int
main() {
	map<vector<int>, int> seen;
	int p1, i;

	vector<int> v{istream_iterator<int>(cin), {}};

	for (p1 = 0; seen.emplace(v, p1).second; p1++) {
		auto m = max_element(begin(v), end(v));
		for (i = *m, *m = 0; i-- > 0; ++*m)
			if (++m == end(v))
				m = begin(v);
	}

	cout << p1 << endl << p1 - seen[v] << endl;
}
