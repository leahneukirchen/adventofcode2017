#include <algorithm>
#include <iostream>
#include <functional>

int main()
{
	std::string d;
	std::cin >> d;

	d.push_back(d[0]);
	int s = 0;
	for (auto i{d.cbegin()};
	     (i = std::adjacent_find(i, d.cend())) != d.cend();
	     i++) {
		s += *i - '0';
	}
        std::cout << s << std::endl;

	auto d1{d.cbegin()};
	auto mid{d1 + d.size()/2 - 1};
	auto d2{mid + 1};
	s = 0;
	for (auto p{std::mismatch(d1, mid, d2, std::not_equal_to<char>())};
	     p.first != mid;
	     p = std::mismatch(++p.first, mid, ++p.second, std::not_equal_to<char>()))
		s += *p.first - '0';
        std::cout << 2*s << std::endl;

	return 0;
}
