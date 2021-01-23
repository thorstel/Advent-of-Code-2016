// https://adventofcode.com/2016/day/18

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
using namespace std;

bool is_trap(const string& row, int i)
{
	char l = i > 0 ? row[i - 1] : '.';
	char c = row[i];
	char r = i < sz(row) - 1 ? row[i + 1] : '.';
	return
		(l == '^' && c == '^' && r == '.') ||
		(l == '.' && c == '^' && r == '^') ||
		(l == '^' && c == '.' && r == '.') ||
		(l == '.' && c == '.' && r == '^');
}

void solve(istream& ins)
{
	assert(ins.good());
	string row;
	getline(ins, row);
	int safe_tiles = 0;
	for (int n = 0; n < 400000; ++n) {
		if (n == 40)
			cout << safe_tiles << endl; // Part 1
		safe_tiles += count(all(row), '.');
		string r {row};
		for (int i = 0; i < sz(row); ++i)
			r[i] = is_trap(row, i) ? '^' : '.';
		row = r;
	}
	cout << safe_tiles << endl;
}

////////////////////////////////////////////////////////////////////////
//                            SETUP STUFF                             //
////////////////////////////////////////////////////////////////////////

static const string actual_input =
R"""(.^^..^...^..^^.^^^.^^^.^^^^^^.^.^^^^.^^.^^^^^^.^...^......^...^^^..^^^.....^^^^^^^^^....^^...^^^^..^)""";

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
