// https://adventofcode.com/2016/day/21

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
using namespace std;

static const regex swap_pattern1 {R"(swap position (\d+) with position (\d+))"};
static const regex swap_pattern2 {R"(swap letter (\w) with letter (\w))"};
static const regex rotate_pattern1 {R"(rotate (left|right) (\d+) steps?)"};
static const regex rotate_pattern2 {R"(rotate based on position of letter (\w))"};
static const regex reverse_pattern {R"(reverse positions (\d+) through (\d+))"};
static const regex move_pattern {R"(move position (\d+) to position (\d+))"};

string scramble(string pw, const vector<string>& rules)
{
	for (const string& rule : rules) {
		smatch m;
		if (regex_match(rule, m, swap_pattern1)) {
			int x = stoi(m[1]), y = stoi(m[2]);
			char c = pw[x];
			pw[x] = pw[y];
			pw[y] = c;
		} else if (regex_match(rule, m, swap_pattern2)) {
			char x = m[1].str()[0];
			char y = m[2].str()[0];
			for (int i = 0; i < sz(pw); ++i) {
				if (pw[i] == x)
					pw[i] = y;
				else if (pw[i] == y)
					pw[i] = x;
			}
		} else if (regex_match(rule, m, rotate_pattern1)) {
			string dir = m[1];
			int x = stoi(m[2]);
			if (dir == "left")
				rotate(begin(pw), begin(pw) + x, end(pw));
			else if (dir == "right")
				rotate(rbegin(pw), rbegin(pw) + x, rend(pw));
			else
				assert(false);
		} else if (regex_match(rule, m, rotate_pattern2)) {
			char x = m[1].str()[0];
			int r = pw.find(x);
			if (r >= 4)
				++r;
			for (int i = 0; i < 1 + r; ++i)
				rotate(rbegin(pw), rbegin(pw) + 1, rend(pw));
		} else if (regex_match(rule, m, reverse_pattern)) {
			int x = stoi(m[1]), y = stoi(m[2]);
			assert(x < y);
			reverse(begin(pw) + x, begin(pw) + y + 1);
		} else if (regex_match(rule, m, move_pattern)) {
			int x = stoi(m[1]), y = stoi(m[2]);
			if (x < y) {
				char c = pw[x];
				for (int i = x; i < y; ++i)
					pw[i] = pw[i + 1];
				pw[y] = c;
			} else {
				char c = pw[x];
				for (int i = x; i > y; --i)
					pw[i] = pw[i - 1];
				pw[y] = c;
			}
		} else {
			assert(false);
		}
	}
	return pw;
}

void solve(istream& ins)
{
	assert(ins.good());
	vector<string> rules;
	for (string line; getline(ins, line);)
		rules.push_back(line);

	// Part 1
	string pw = "abcdefgh";
	cout << scramble(pw, rules) << endl;

	// Part 2
	do {
		if (scramble(pw, rules) == "fbgdceah") {
			cout << pw << endl;
			break;
		}
	} while (next_permutation(all(pw)));
}

////////////////////////////////////////////////////////////////////////
//                            SETUP STUFF                             //
////////////////////////////////////////////////////////////////////////

static const string actual_input =
R"""(rotate left 2 steps
rotate right 0 steps
rotate based on position of letter a
rotate based on position of letter f
swap letter g with letter b
rotate left 4 steps
swap letter e with letter f
reverse positions 1 through 6
swap letter b with letter d
swap letter b with letter c
move position 7 to position 5
rotate based on position of letter h
swap position 6 with position 5
reverse positions 2 through 7
move position 5 to position 0
rotate based on position of letter e
rotate based on position of letter c
rotate right 4 steps
reverse positions 3 through 7
rotate left 4 steps
rotate based on position of letter f
rotate left 3 steps
swap letter d with letter a
swap position 0 with position 1
rotate based on position of letter a
move position 3 to position 6
swap letter e with letter g
move position 6 to position 2
reverse positions 1 through 2
rotate right 1 step
reverse positions 0 through 6
swap letter e with letter h
swap letter f with letter a
rotate based on position of letter a
swap position 7 with position 4
reverse positions 2 through 5
swap position 1 with position 2
rotate right 0 steps
reverse positions 5 through 7
rotate based on position of letter a
swap letter f with letter h
swap letter a with letter f
rotate right 4 steps
move position 7 to position 5
rotate based on position of letter a
reverse positions 0 through 6
swap letter g with letter c
reverse positions 5 through 6
reverse positions 3 through 5
reverse positions 4 through 6
swap position 3 with position 4
move position 4 to position 2
reverse positions 3 through 4
rotate left 0 steps
reverse positions 3 through 6
swap position 6 with position 7
reverse positions 2 through 5
swap position 2 with position 0
reverse positions 0 through 3
reverse positions 3 through 5
rotate based on position of letter d
move position 1 to position 2
rotate based on position of letter c
swap letter e with letter a
move position 4 to position 1
reverse positions 5 through 7
rotate left 1 step
rotate based on position of letter h
reverse positions 1 through 7
rotate based on position of letter f
move position 1 to position 5
reverse positions 1 through 4
rotate based on position of letter a
swap letter b with letter c
rotate based on position of letter g
swap letter a with letter g
swap position 1 with position 0
rotate right 2 steps
rotate based on position of letter f
swap position 5 with position 4
move position 1 to position 0
swap letter f with letter b
swap letter f with letter h
move position 1 to position 7
swap letter c with letter b
reverse positions 5 through 7
rotate left 6 steps
swap letter d with letter b
rotate left 3 steps
swap position 1 with position 4
rotate based on position of letter a
rotate based on position of letter a
swap letter b with letter c
swap letter e with letter f
reverse positions 4 through 7
rotate right 0 steps
reverse positions 2 through 3
rotate based on position of letter a
reverse positions 1 through 4
rotate right 1 step)""";

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
