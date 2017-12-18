#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int
main()
{
	int d;
	cin >> d;

	vector<int> v{0};
	v.reserve(2018);
	for (int i = 1; i <= 2017; i++) {
		rotate(begin(v), begin(v) + d % size(v), end(v));
		v.push_back(i);
	}

	long p2;
	for (long l = 1, p = 0; l < 50'000'000; p = (p + 1 + d) % ++l)
		if (p == 0)
			p2 = l;

	cout << v[0] << endl << p2 << endl;	// 1306 20430489
}
