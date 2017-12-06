#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int
main() {
	vector<int> v{istream_iterator<int>(cin), {}};
	auto w = v;
	int p1 = 0, p2 = 0;

	for (unsigned int pc = 0; pc < v.size(); p1++)
		pc += v[pc]++;

	for (unsigned int pc = 0; pc < v.size(); p2++)
		pc += w[pc] >= 3 ? w[pc]-- : w[pc]++;

	cout << p1 << endl << p2 << endl;
}
