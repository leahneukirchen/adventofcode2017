#include <array>
#include <iostream>
#include <string>
#include <algorithm>
#include <variant>
#include <vector>
#include <deque>
#include <memory>

using namespace std;

int
main() {
        vector<string> code;
        for (string line; getline(cin, line); )
                code.push_back(line);

	array<long, 256> reg{ 0 };

        long p1 = 0, p2 = 0;

        for (auto ip = begin(code); ip != end(code); ip++) {
                auto is_op = [&](string p) {
                        return equal(begin(p), end(p), begin(*ip));
                };

                long tmp;
                auto r = [&](int i) -> long& {
                        if (islower((*ip)[i]))
                                return reg[uint8_t((*ip)[i])];
                        else {
                                tmp = stol(&(*ip)[i]);
                                return tmp;
                        }
                };

                if (is_op("set")) r(4) = r(6);
                if (is_op("sub")) r(4) -= r(6);
                if (is_op("mul")) r(4) *= r(6), p1++;
                if (is_op("jnz") && r(4)) advance(ip, r(6) - 1);
        }

	int c = 100'000 + 100 * stol(&code[0][6]);
	for (int x = c; x <= c + 17'000; x += 17)
		for (int i = 2; i < x; i++)
			if (x % i == 0) {
				p2++;
				break;
			}

        cout << p1 << endl << p2 << endl;	// 8281 911
}
