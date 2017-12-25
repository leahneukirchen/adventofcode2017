#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct trans;
using state = pair<trans,trans>;
struct trans {
	int w, m;
	state *n;
};

enum {
	L = -1,
	R = +1
};

int main() {
	int l = 12399302;

	state A, B, C, D, E, F;
	A = {{1, R, &B}, {0, R, &C}};
	B = {{0, L, &A}, {0, R, &D}};
	C = {{1, R, &D}, {1, R, &A}};
	D = {{1, L, &E}, {0, L, &D}};
	E = {{1, R, &F}, {1, L, &B}};
	F = {{1, R, &A}, {1, R, &E}};

	state *s = &A;

	vector<int> v(20'000, 0);
	auto head = begin(v) + 10'000;

	for (int i = 0; i < l; i++) {
		trans &t = *head == 0 ? s->first : s->second;
		*head = t.w;
		head += t.m;
		s = t.n;
	}

	cout << accumulate(begin(v), end(v), 0) << endl;	// 2794
}
