// https://adventofcode.com/2016/day/16

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
using namespace std;

string dragon_checksum(const string& init, int disc_len)
{
	string a = init;
	while (sz(a) < disc_len) {
		string b = a;
		reverse(all(b));
		for (int i = 0; i < sz(b); ++i)
			b[i] = b[i] == '0' ? '1' : '0';
		a += '0' + b;
	}
	a = a.substr(0, disc_len);

	while (sz(a) % 2 == 0) {
		stringstream ss;
		for (int i = 0; i < sz(a); i += 2)
			ss << (a[i] == a[i + 1] ? '1' : '0');
		a = ss.str();
	}
	return a;
}

void solve(istream& ins)
{
	assert(ins.good());
	string data;
	ins >> data;
	cout << dragon_checksum(data, 272) << '\n';
	cout << dragon_checksum(data, 35651584) << '\n';
}

////////////////////////////////////////////////////////////////////////
//                            SETUP STUFF                             //
////////////////////////////////////////////////////////////////////////

static const string actual_input = R"""(00111101111101000)""";

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
