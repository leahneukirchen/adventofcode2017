#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<string,int> weights;
map<string,bool> onbottom;
map<string,vector<string>> ontop;

int weighing(string s) {
	const auto &children = ontop[s];
	vector<int> sw;

	transform(begin(children), end(children), back_inserter(sw), weighing);

	auto [min, max] = minmax_element(begin(sw), end(sw));
	if (min != end(sw) && *min != *max) {
		auto another = begin(sw);
		while (another != end(sw) && (another == max || another == min))
			another++;

		auto wrong = *min == *another ? max : min;
		auto wrongid = ontop[s][distance(sw.begin(), wrong)];

		cout << weights[wrongid] + (*another - *wrong) << endl;
		exit(0);  // lame
	}

	return accumulate(begin(sw), end(sw), weights[s]);
}

int
main()
{
	string line;

	while (getline(cin, line)) {
		istringstream is1{line};
		string name;
		int weight;

		is1 >> name; is1.ignore(5, '(');
		is1 >> weight; is1.ignore(5, '>');

		vector<string> v;
		string item;

		while (getline(is1, item, ',')) {
			item.erase(0, 1);
			v.push_back(item);
			onbottom[item] = 1;
		}

		weights[name] = weight;
		ontop[name] = v;
	}

	auto top = find_if_not(begin(weights), end(weights),
	    [](auto v) { return onbottom.count(v.first); })->first;
	
	cout << top << "\n";
	weighing(top);
}
