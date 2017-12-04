#include <cmath>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

class SpiralIterator : public std::iterator<std::input_iterator_tag, int> {
public:
	pair<int, int> p;
	int i, j, d;

	SpiralIterator() : p{0,1}, i{2}, j{1}, d{-1}
	{ }

	auto begin() { return *this; }
	auto end() { return SpiralIterator{}; }
	bool operator!=(SpiralIterator &) const { return true; }   // infinite

	auto operator*() { return p; }
	auto operator++() {
		switch (d) {
		case 0: p.first--; break;
		case 1: p.second--; break;
		case 2: p.first++; break;
		case 3: p.second++; break;
		}

		if (--j == 0) {
			if (++d == 4) {
				i += 2;
				d = 0;
			}

			j = i;
			if (d == 0) j--;
			if (d == 3) j++;
		}
	}
};

int
manhattan(pair<int, int> c)
{
	return abs(c.first) + abs(c.second);
}

int
main() {
	int i;
	cin >> i;

	// part 1
	SpiralIterator p1;
	advance(p1, i-1);
	cout << manhattan(*p1) << endl;

	// part 2
	const int N = 20;
	vector<vector<int>> m(N, vector<int>(N, 0));
	m[N/2][N/2] = 1;

	for (auto [x,y] : SpiralIterator{}) {
		x += N/2; y += N/2;

		m[x][y] = m[x+1][y+1] + m[x+1][y] + m[x+1][y-1] +
		          m[ x ][y+1] +	            m[ x ][y-1] +
		          m[x-1][y+1] + m[x-1][y] + m[x-1][y-1];

		if (m[x][y] > i) {
			cout << m[x][y] << endl;
			break;
		}
	}
}
