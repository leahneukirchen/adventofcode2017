#include <string>
#include <vector>
#include <iostream>

using namespace std;

int
main()
{
	vector<string> d;

	for (string l; getline(cin, l); )
		d.push_back(l);

	int y = 0;
	int x = d[y].find('|');

	string p1;
	int p2 = 0;

	for (int dx = 0, dy = 1; d[y][x] != ' '; x += dx, y += dy, p2++) {
		if (isupper(d[y][x]))
			p1.push_back(d[y][x]);

		if (d[y][x] == '+') {
			if (dx) {
				dx = 0;
				dy = (d[y+1][x] != ' ') ? 1 : -1;
			} else {
				dx = (d[y][x+1] != ' ') ? 1 : -1;
				dy = 0;
			}
		}
	}

	cout << p1 << endl << p2 << endl;
}
