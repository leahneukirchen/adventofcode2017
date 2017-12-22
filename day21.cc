#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

using pic = vector<vector<char>>;

pic parse(string s) {
	int n = s.find("/");
	pic p(n, vector<char>(n, '?'));
	int y = 0, x = 0;
	for (char c : s)
		if (c == '/') {
			y++;
			x = 0;
		} else {
			p[y][x++] = c;
		}
	return p;
}

pic rotate(pic p) {
	pic np = p;
	const int s = size(p);
	for (int y = 0; y < s; y++)
		for (int x = 0; x < s; x++)
			np[x][s-1-y] = p[y][x];
	return np;
}

int
main() {
	string line;

	vector<pair<pic, pic>> book;

	while (getline(cin, line)) {
		int i = line.find(" => ");
		pic k = parse(line.substr(0, i));
		pic v = parse(line.substr(i + 4));

		for (int i = 0; i < 4; i++, k = rotate(k)) {
			book.emplace_back(k, v);
			reverse(begin(k), end(k));
			book.emplace_back(k, v);
			reverse(begin(k), end(k));
		}
	}

	pic p{{'.','#','.'}, {'.','.','#'}, {'#','#','#'}};

	for (int n = 1; n <= 18; n++) {
		int s = 2 + size(p) % 2;

		pic np{(size(p)/s)*(s+1), vector<char>((size(p)/s)*(s+1), '?')};

		for (int y = 0; y < size(p); y += s) {
		for (int x = 0; x < size(p); x += s) {
			for (auto &[k, v] : book) {
				if (size(k) != s)
					goto next;

				for (int iy = 0; iy < s; iy++)
				for (int ix = 0; ix < s; ix++)
					if (p[y+iy][x+ix] != k[iy][ix])
						goto next;

				for (int iy = 0; iy < size(v); iy++)
				for (int ix = 0; ix < size(v); ix++)
					np[(y/s)*(s+1)+iy][(x/s)*(s+1)+ix] = v[iy][ix];
				goto done;
			next:;
			}
		done:;
		}
		}

		if (n == 5 || n == 18) {
			int cnt = 0;
			for (auto row : np)
				cnt += count(begin(row), end(row), '#');
			cout << cnt << endl;
		}

		p.swap(np);
	}

}
