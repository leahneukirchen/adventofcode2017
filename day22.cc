#include <iostream>
#include <vector>
#include <string>

using namespace std;

void
rotate(int& dy, int &dx)
{
	if (dy) {
		dx = (dy == -1) ? 1 : -1;
		dy = 0;
	} else {
		dy = (dx == -1) ? -1 : 1;
		dx = 0;
	}
}

int
main() {
	const int pad = 400;
	vector<vector<char>> d1;

	string p(pad, '.');
	for (string line; getline(cin, line); ) {
		line = p + line + p;
		d1.emplace_back(begin(line), end(line));
	}
	vector<char> padding(2 * pad + size(d1), '.');
	d1.insert(begin(d1), pad, padding);
	d1.insert(end(d1), pad, padding);

	vector d2 = d1;

	int p1 = 0, p2 = 0;

	for (int i=0, y=size(d1)/2, x=y, dy=-1, dx=0;
	     i < 10'000;
	     i++, y += dy, x += dx) {
		if (d1[y][x] == '#') { // turn right;
			rotate(dy, dx);
		} else { // turn left;
			rotate(dy, dx);
			dy = -dy;
			dx = -dx;
		}

		if (d1[y][x] == '#') {
			d1[y][x] = '.';
		} else {
			p1++;
			d1[y][x] = '#';
		}
	}

	cout << p1 << endl;   // 5462

	for (int i=0, y=size(d2)/2, x=y, dy=-1, dx=0;
	     i < 10'000'000;
	     i++, y += dy, x += dx) {
		if (d2[y][x] == '#') { // turn right;
			rotate(dy, dx);
		} else if (d2[y][x] == '.') { // turn left;
			rotate(dy, dx);
			dy = -dy;
			dx = -dx;
		} else if (d2[y][x] == 'F') {
			dy = -dy;
			dx = -dx;
		}

		if (d2[y][x] == '#') {
			d2[y][x] = 'F';
		} else if (d2[y][x] == '.') {
			d2[y][x] = 'W';
		} else if (d2[y][x] == 'W') {
			p2++;
			d2[y][x] = '#';
		} else if (d2[y][x] == 'F') {
			d2[y][x] = '.';
		}
	}

	cout << p2 << endl;   // 2512135
}
