// https://adventofcode.com/2016/day/19

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
using namespace std;

void solve(istream& ins)
{
	assert(ins.good());
	int num_elves;
	ins >> num_elves;

	// Part 1: https://en.wikipedia.org/wiki/Josephus_problem#Bitwise
	bitset<32> bs(num_elves);
	for (int i = 31; i >= 0; --i) {
		if (bs[i]) {
			bs[i] = false;
			break;
		}
	}
	bs <<= 1;
	bs[0] = true;
	cout << bs.to_ulong() << endl;

	// Part 2
	int n = 1, max_n = 1;
	for (int i = 0; i <= num_elves; ++i) {
		if (n + 2 > i) {
			max_n = n;
			n = 1;
		} else if (n < max_n) {
			++n;
		} else {
			n += 2;
		}
	}
	cout << n << endl;
}

////////////////////////////////////////////////////////////////////////
//                            SETUP STUFF                             //
////////////////////////////////////////////////////////////////////////

static const string sample_input =
R"""(5)""";

static const string actual_input =
R"""(3017957)""";

int main(int argc, const char *argv[])
{
	if (argc > 1) {
		ifstream ifs {argv[1]};
		solve(ifs);
	} else {
		cout << "=== SAMPLE ===\n";
		istringstream iss {sample_input};
		solve(iss);
		cout << "=== ACTUAL ===\n";
		iss = istringstream {actual_input};
		solve(iss);
	}
	return 0;
}
