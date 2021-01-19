// https://adventofcode.com/2016/day/15

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
using ll = long long;
using namespace std;

void solve(istream& ins)
{
	assert(ins.good());
	regex pat {R"(Disc #\d+ has (\d+) positions; at time=0, it is at position (\d+).)"};
	ll ans = 0, inc = 1, disc_no = 1;
	for (string line; getline(ins, line); ++disc_no) {
		smatch m;
		if (!regex_match(line, m, pat))
			assert(0);
		ll num_pos = stoll(m[1]);
		ll offset = stoll(m[2]) + disc_no;
		while (((ans + offset) % num_pos) != 0)
			ans += inc;
		inc *= num_pos;
	}
	cout << ans << '\n';

	// Part 2
	while (((ans + disc_no) % 11) != 0)
		ans += inc;
	cout << ans << '\n';
}

////////////////////////////////////////////////////////////////////////
//                            SETUP STUFF                             //
////////////////////////////////////////////////////////////////////////

static const string sample_input =
R"""(Disc #1 has 5 positions; at time=0, it is at position 4.
Disc #2 has 2 positions; at time=0, it is at position 1.)""";

static const string actual_input =
R"""(Disc #1 has 13 positions; at time=0, it is at position 10.
Disc #2 has 17 positions; at time=0, it is at position 15.
Disc #3 has 19 positions; at time=0, it is at position 17.
Disc #4 has 7 positions; at time=0, it is at position 1.
Disc #5 has 5 positions; at time=0, it is at position 0.
Disc #6 has 3 positions; at time=0, it is at position 1.)""";

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
