#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int
main() {
	string sym;
	int x{0}, y{0}, d{0}, maxd{0};

	while (getline(cin, sym, ',')) {
		if (cin.eof()) sym.pop_back();

		if      (sym == "n" ) x--;
		else if (sym == "s" ) x++;
		else if (sym == "se")      y++;
		else if (sym == "nw")      y--;
		else if (sym == "ne") x--, y++;
		else if (sym == "sw") x++, y--;

		maxd = max(maxd, d = max({x,-x,y,-y,x+y,-x-y}));
	}

	cout << d << endl << maxd << endl;
}
