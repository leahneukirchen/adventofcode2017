#include <iostream>

using namespace std;

template <int const n=0>
struct lrng {
	uint64_t m, s;
	uint16_t operator*() const { return s; }
	auto operator++() { do s = s * m % 2147483647; while (n && s % n != 0); }
};

int
main() {
	int p1{0}, p2{0};

	lrng<> a1{16807, 634};
	lrng<> b1{48271, 301};
	for (long i{0}; i < 40'000'000; ++i, ++a1, ++b1)
		if (*a1 == *b1)
			p1++;

	lrng<4> a2{16807, 634};
	lrng<8> b2{48271, 301};
	for (long i{0}; i < 5'000'000; ++i, ++a2, ++b2)
		if (*a2 == *b2)
			p2++;

	cout << p1 << endl << p2 << endl;	// 573 294
}
