// https://adventofcode.com/2016/day/13

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
using namespace std;

void solve(istream& ins)
{
	assert(ins.good());
	const vector<pair<int, int>> offsets {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int fav_num;
	ins >> fav_num;
	auto is_wall = [&](int x, int y) {
		uint32_t val = (x * x) + (3 * x) + (2 * x * y) + y + (y * y);
		val += fav_num;
		return bitset<32>(val).count() % 2 != 0;
	};

	optional<int> ans1, ans2;
	deque<tuple<int, int, int>> Q;
	set<pair<int, int>> seen;
	Q.push_back(make_tuple(0, 1, 1));
	seen.insert(make_pair(1, 1));
	while (!Q.empty() && (!ans1 || !ans2)) {
		auto [steps, x, y] = Q.front();
		Q.pop_front();
		if (!ans1 && x == 31 && y == 39)
			ans1 = steps;
		if (!ans2 && steps == 50)
			ans2 = sz(seen);
		++steps;
		for (auto [dx, dy] : offsets) {
			int xn = x + dx;
			int yn = y + dy;
			if (xn < 0 || yn < 0 || is_wall(xn, yn))
				continue;
			if (seen.insert(make_pair(xn, yn)).second)
				Q.push_back(make_tuple(steps, xn, yn));
		}
	}
	cout << *ans1 << '\n';
	cout << *ans2 << '\n';
}

////////////////////////////////////////////////////////////////////////
//                            SETUP STUFF                             //
////////////////////////////////////////////////////////////////////////

static const string actual_input = R"""(1350)""";

int main(int argc, const char *argv[])
{
	if (argc > 1) {
		ifstream ifs {argv[1]};
		solve(ifs);
	} else {
		istringstream iss {actual_input};
		solve(iss);
	}
	return 0;
}
