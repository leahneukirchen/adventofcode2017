#include <algorithm>
#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	string line;
	int s1 = 0, s2 = 0;

	while (getline(cin, line)) {
		// slurp it for part 2
		istringstream is{line};
		vector<int> v{istream_iterator<int>(is), {}};

		auto [min, max] = minmax_element(begin(v), end(v));
		s1 += *max - *min;

		for (int a : v)
			for (int b : v)
				if (a > b && a % b == 0)
					s2 += a / b;
	}

	cout << s1 << endl << s2 << endl;
	return 0;
}
