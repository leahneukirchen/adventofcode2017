#ifdef BOOST

#include <iostream>
#include <optional>

// Using boost-1.65.1
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/tokenizer.hpp>

using namespace std;

using undirected_graph =
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;

int
main()
{
	undirected_graph G;

	for (string line; getline(cin, line); ) {
		optional<int> last;
		for (string s : boost::tokenizer<>(line)) {
			int i = stoi(s);
			if (last)
				add_edge(*last, i, G);
			last = i;
		}
	}

	vector<int> component(num_vertices(G));
	int n = connected_components(G, &component[0]);
	cout << count(begin(component), end(component), component[0]) << endl;
	cout << n << endl;
}

// 134
// 193

#else //////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// bfs approach without recursion
// adapted from https://www.reddit.com/r/adventofcode/comments/7j89tr/x/dr4iya8/

int main()
{
	vector<vector<int>> edges;

	for (string line; getline(cin, line); ) {		
		istringstream line_stream{line};
		int vertex_a, vertex_b;
		string _;
		line_stream >> vertex_a >> _;
		for (edges.emplace_back();  // assumes lines arrive in order
		     line_stream >> vertex_b;
		     line_stream >> _)
			edges[vertex_a].emplace_back(vertex_b);
	}

	vector<int> comp(size(edges), -1);
	int n = 0;

	for (auto vertex = begin(comp);
	     vertex != end(comp);
	     ++n, vertex = find(begin(comp), end(comp), -1)) {
		deque<long> queue{distance(begin(comp), vertex)};
		while (!empty(queue)) {
			int v = queue.front();
			queue.pop_front();
			comp[v] = n;
			copy_if(begin(edges[v]), end(edges[v]),
			    back_inserter(queue),
			    [&](int v){ return comp[v] == -1; });
		}
	}

	cout << count(begin(comp), end(comp), 0) << endl;
	cout << n << endl;
}

#endif
