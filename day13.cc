#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using namespace std::placeholders;

struct scanner {
	int d, r;
	bool hit(int delay=0) { return (d + delay) % (2*r - 2) == 0; }
	operator int() { return hit() ? d * r : 0; }
};

int main()
{
	vector<scanner> ss;
	char _;
	for (int d, r; cin >> d >> _ >> r; )
		ss.push_back({d, r});

	cout << std::accumulate(begin(ss), end(ss), 0) << endl;

	for (int d = 0; ; d++)
		if (none_of(ss.begin(), ss.end(), bind(&scanner::hit, _1, d))) {
			cout << d << endl;
			break;
		}
}
