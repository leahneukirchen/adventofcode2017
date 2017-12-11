#include <iostream>

using namespace std;

int
main()
{
	char c;
	int l{0}, t{0}, g{0};

	while (cin >> c)
		if (c == '{') l++;
		else if (c == '}') t += l--;
		else if (c == '<')
			while (cin >> c && c != '>')
				c == '!' ? cin.get() : g++;

	cout << t << endl << g << endl;   // 17390 7825
}
