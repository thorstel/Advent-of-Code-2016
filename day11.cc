// https://adventofcode.com/2016/day/11

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
using namespace std;

// even index = generator, odd index = microchip
// Always in pairs, e.g. index 0 and 1 have a compatible type.
template<int N>
using state_t = bitset<(4 * N) + 2>;

template<int N>
constexpr void set_bit(state_t<N>& bs, int r, int c, bool val)
{
	bs[(r * N) + c] = val;
}

template<int N>
constexpr bool get_bit(state_t<N>& bs, int r, int c)
{
	return bs[(r * N) + c];
}

template<int N>
constexpr int get_floor(state_t<N>& bs)
{
	return (int)(bs >> (N * 4)).to_ullong();
}

template<int N>
constexpr void set_floor(state_t<N>& bs, int floor)
{
	bs[N * 4] = (floor & 1) != 0;
	bs[(N * 4) + 1] = (floor & 2) != 0;
}

template<int N>
bool is_legal(state_t<N>& floors, int row)
{
	int gen_cnt = 0, chip_cnt = 0;
	for (int i = 0; i < N; i += 2) {
		bool x = get_bit<N>(floors, row, i);
		bool y = get_bit<N>(floors, row, i + 1);
		if (x != y) {
			if (x) ++gen_cnt;
			if (y) ++chip_cnt;
		}
	}
	return gen_cnt == 0 || chip_cnt == 0;
}

template<int N>
int solve(state_t<N> init)
{
	state_t<N> target;
	for (int i = 0; i < N; ++i)
		set_bit<N>(target, 3, i, true);
	set_floor<N>(target, 3);

	int current_depth = 0;
	deque<pair<int, state_t<N>>> Q;
	unordered_set<state_t<N>> seen;
	Q.emplace_back(make_pair(0, init));
	seen.insert(init);
	while (!Q.empty()) {
		auto [steps, floors] = Q.front();
		Q.pop_front();
		if (current_depth < steps) {
			current_depth = steps;
			cerr << "current depth = " << current_depth << '\n';
		}
		if (floors == target)
			return steps;
		++steps;
		int f = get_floor<N>(floors);
		for (int i = 0; i < N; ++i) {
			if (!get_bit<N>(floors, f, i))
				continue;
			if (f > 0) {
				auto nfloors = floors;
				set_bit<N>(nfloors, f, i, false);
				set_bit<N>(nfloors, f - 1, i, true);
				set_floor<N>(nfloors, f - 1);
				if (is_legal<N>(nfloors, f - 1) && seen.insert(nfloors).second)
					Q.emplace_back(make_pair(steps, nfloors));
			}
			if (f < 3) {
				auto nfloors = floors;
				set_bit<N>(nfloors, f, i, false);
				set_bit<N>(nfloors, f + 1, i, true);
				set_floor<N>(nfloors, f + 1);
				if (is_legal<N>(nfloors, f + 1) && seen.insert(nfloors).second)
					Q.emplace_back(make_pair(steps, nfloors));
			}
			for (int j = 0; j < N; ++j) {
				if (j == i || !get_bit<N>(floors, f, j))
					continue;
				if (f > 0) {
					auto nfloors = floors;
					set_bit<N>(nfloors, f, i, false);
					set_bit<N>(nfloors, f, j, false);
					set_bit<N>(nfloors, f - 1, i, true);
					set_bit<N>(nfloors, f - 1, j, true);
					set_floor<N>(nfloors, f - 1);
					if (is_legal<N>(nfloors, f - 1) && seen.insert(nfloors).second)
						Q.emplace_back(make_pair(steps, nfloors));
				}
				if (f < 3) {
					auto nfloors = floors;
					set_bit<N>(nfloors, f, i, false);
					set_bit<N>(nfloors, f, j, false);
					set_bit<N>(nfloors, f + 1, i, true);
					set_bit<N>(nfloors, f + 1, j, true);
					set_floor<N>(nfloors, f + 1);
					if (is_legal<N>(nfloors, f + 1) && seen.insert(nfloors).second)
						Q.emplace_back(make_pair(steps, nfloors));
				}
			}
		}
	}
	return -1;
}

template<int N>
void init_input(state_t<N>& floors)
{
	// The first floor contains
	set_bit<N>(floors, 0, 0, true); // a polonium generator,
	set_bit<N>(floors, 0, 2, true); // a thulium generator,
	set_bit<N>(floors, 0, 3, true); // a thulium-compatible microchip,
	set_bit<N>(floors, 0, 4, true); // a promethium generator,
	set_bit<N>(floors, 0, 6, true); // a ruthenium generator,
	set_bit<N>(floors, 0, 7, true); // a ruthenium-compatible microchip,
	set_bit<N>(floors, 0, 8, true); // a cobalt generator,
	set_bit<N>(floors, 0, 9, true); // and a cobalt-compatible microchip.
	// The second floor contains
	set_bit<N>(floors, 1, 1, true); // a polonium-compatible microchip
	set_bit<N>(floors, 1, 5, true); // and a promethium-compatible microchip.
	// The third floor contains nothing relevant.
	// The fourth floor contains nothing relevant.
}

int main()
{
	state_t<10> part1;
	init_input<10>(part1);
	cout << solve<10>(part1) << '\n';

	state_t<14> part2;
	init_input<14>(part2);
	set_bit<14>(part2, 0, 10, true);
	set_bit<14>(part2, 0, 11, true);
	set_bit<14>(part2, 0, 12, true);
	set_bit<14>(part2, 0, 13, true);
	cout << solve<14>(part2) << '\n';
	return 0;
}
