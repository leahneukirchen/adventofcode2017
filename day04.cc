#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

namespace anagram {
	struct is_anagram {
		bool operator()(const string &a, const string &b) const {
			return is_permutation(begin(a), end(a), begin(b));
		}
	};

	struct unordered_hash {
		size_t operator()(const string &a) const {
			return accumulate(begin(a), end(a), 0);
		}
	};

	using set = unordered_set<string,unordered_hash,is_anagram>;
}

int
main()
{
	string line;
	int p1 = 0, p2 = 0;

	while (getline(cin, line)) {
		istringstream is1{line}, is2{line};
		set<string> words{istream_iterator<string>(is1),
		    istream_iterator<string>()};
		anagram::set awords{words.cbegin(), words.cend()};
		size_t wcount = distance(istream_iterator<string>(is2),
		    istream_iterator<std::string>());

		if (words.size() == wcount) p1++;
		if (awords.size() == wcount) p2++;
	}

	cout << p1 << endl << p2 << endl;
}
