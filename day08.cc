#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <map>

using namespace std;

const map<string,bool(*)(int,int)> cmps {{
	{"<",  [](int x, int y) { return x <  y; }},
	{">",  [](int x, int y) { return x >  y; }},
	{"<=", [](int x, int y) { return x <= y; }},
	{">=", [](int x, int y) { return x >= y; }},
	{"==", [](int x, int y) { return x == y; }},
	{"!=", [](int x, int y) { return x != y; }},
}};

const map<string,int(*)(int&,int)> actions {{
	{"inc", [](int &x, int y) { return x += y; }},
	{"dec", [](int &x, int y) { return x -= y; }},
}};

int
main()
{
	map<string,int> reg;
	int maxval = 0;

	string name, action, _, v1, cmp;
	int k1, k2;
	
	while (cin >> name >> action >> k1 >> _ >> v1 >> cmp >> k2)
		if (cmps.at(cmp)(reg[v1], k2))
			maxval = max(maxval, actions.at(action)(reg[name], k1));

	auto maxreg = max_element(reg.begin(), reg.end(),
	    [](auto &p1, auto &p2) { return p1.second < p2.second; });

	cout << maxreg->second << endl << maxval << endl;
}
