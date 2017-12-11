#include <algorithm>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct CommaInts : string {
	friend istream& operator>>(istream& is, CommaInts& line) {
		return getline(is, line, ',');
	}
	operator int() const { return stoi(*this); }
};
auto begin(istream_iterator<CommaInts>& l) { return l; }
auto end(istream_iterator<CommaInts>&) { return istream_iterator<CommaInts>{}; }

template <typename T>
auto knothash(T iter, int n)
{
	vector<int> v(256);
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

	istringstream iss{line};
	vector<int> v1{knothash(istream_iterator<CommaInts>(iss), 1)};
	cout << v1[0] * v1[1] << endl;

	line.append({17,31,73,47,23});
	vector<int> v2{knothash(line, 64)};
	for (auto b = begin(v2); b != end(v2); advance(b, 16))
		cout << setfill('0') << setw(2) << hex <<
		    accumulate(b, b + 16, 0, bit_xor<uint8_t>());
	cout << endl;
}
