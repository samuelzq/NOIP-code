// UVa1586
// By LaoZhang
// Date 2020-08-02

#include <iostream>
#include <string>

enum Molar {
	C = 0,
	H,
	O,
	N,
	Max
};

const float mm[4] = {12.01, 1.008, 16.00, 14.01};

using namespace std;

int next_tok(string s, int cur)
{
	int n = s.length();

	for (int i = cur + 1; i < n; i++) {
		switch (s[i]) {
			case 'C':
			case 'H':
			case 'O':
			case 'N':
				return i;
		}
	}
	return n;
}

float get_mass(char c)
{
	switch (c) {
		case 'O':
			return mm[O];
		case 'H':
			return mm[H];
		case 'C':
			return mm[C];
		case 'N':
			return mm[N];
	}
	return 0;
}

int main()
{
	string s;
	int t;

	cin >> t;

	while (t--) {
		cin >> s;
		float ans = 0, m = 0;
		int n, cc = 0;
		n = s.length();
		for (int i = 0; i < n;) {
			int p = next_tok(s, i);
			if ((p - i) <= 1) {
				ans += get_mass(s[i]);
				i++;
			} else {
				int tmp = 0;
				
				for (int j = i + 1; j < p; j++) {
					tmp = tmp * 10 + s[j] - '0';
				}
				ans += tmp * get_mass(s[i]);
				i = p;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
