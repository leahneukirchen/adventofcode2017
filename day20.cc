#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

struct particle {
	struct v3 { int x, y, z; };
	v3 p, v, a;
	bool operator<(const particle &o) const {
		return tie(p.x, p.y, p.z) < tie(o.p.x, o.p.y, o.p.z);
	}
	int dist() const {
		return abs(p.x) + abs(p.y) + abs(p.z);
	}
	void move() {
		v.x += a.x; v.y += a.y; v.z += a.z;
		p.x += v.x; p.y += v.y; p.z += v.z;
	}
};

int
main() {
	
	vector<particle> particles;

	for (string line; getline(cin, line); ) {
		replace_if(begin(line), end(line),
		    [](char c1) { return !(isdigit(c1) || c1 == '-'); }, ' ');

		particle t;
		istringstream{line} >> t.p.x >> t.p.y >> t.p.z
				    >> t.v.x >> t.v.y >> t.v.z
				    >> t.a.x >> t.a.y >> t.a.z;
		particles.push_back(t);
	}

	vector<particle> particles1 = particles;
	for (auto &p : particles1)
		for (int i = 0; i < 1000; i++)
			p.move();
	auto x = min_element(begin(particles1), end(particles1), 
	    [](auto& p1, auto& p2) { return p1.dist() < p2.dist(); });
	cout << distance(begin(particles1), x) << endl;

	vector<particle> new_particles;
	for (int i = 0; i < 1000; i++) {
		new_particles.clear();
	
		sort(begin(particles), end(particles));

		for (auto i = begin(particles); i != end(particles); ) {
			auto j = upper_bound(i, end(particles), *i);
			if (distance(i, j) == 1) {
				i->move();
				new_particles.push_back(*i);
			}
			i = j;
		}

		particles.swap(new_particles);
	}
	cout << size(particles) << endl;
}
