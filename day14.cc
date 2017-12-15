#include <array>
#include <bitset>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

template <typename T>
auto knothash(T iter, int n=64)
{
	vector<uint8_t> v(256);
	iota(begin(v), end(v), 0);

	uint8_t skip = 0, pos = 0, delta;

	for (int j = 0; j < n; j++)
		for (auto i : iter) {
			reverse(begin(v), begin(v) + i);
			delta = i + skip++;
			rotate(begin(v), begin(v) + delta, end(v));
			pos += delta;
		}
	rotate(begin(v), end(v) - pos, end(v));

	return move(v);
}

int
main() {
	string line;
	cin >> line;

	int p1{0};
	int p2{0};

	array<array<int, 128>, 128> a;

	for (int i = 0; i < 128; ++i) {
		string s = line + "-" + to_string(i);
		s.append({17,31,73,47,23});

		vector<uint8_t> v{knothash(s)};

		int j = 0;
		for (auto r = begin(v); r != end(v); advance(r, 16)) {
			bitset<8> b =
			    accumulate(r, r + 16, 0, bit_xor<uint8_t>());
			p1 += b.count();
			for (int n = 7; n >= 0; n--)
				a[i][j++] = -b[n];
		}
	}

	std::function<void (int,int,int)> fill = [&](int i, int j, int c) {
		if (i < 0 || i >= size(a) ||
		    j < 0 || j >= size(a) ||
		    a[i][j] >= 0)
			return;
		a[i][j] = c;
		fill(i-1,  j,  c);
		fill(i+1,  j,  c);
		fill( i,  j-1, c);
		fill( i,  j+1, c);
	};

	for (int i = 0; i < size(a); i++)
		for (int j = 0; j < size(a[i]); j++)
			if (a[i][j] < 0)
				fill(i, j, ++p2);

	cout << p1 << endl << p2 << endl;	// 8226 1128
}
