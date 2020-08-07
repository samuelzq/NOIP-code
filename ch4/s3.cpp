// UVa133
// By LaoZhang
// Date 2020-08-07

#include <iostream>
#include <iomanip>

using namespace std;

const int N = 21;

bool is_out[N];

int main()
{
	int n; // peaple count
	int k; // counter-clock
	int m; // clockwise

	while (cin >> n >> k >> m) {
		int c = n;
		int l = n, r = 1;
		if (n == 0 && k == 0 && m ==0)
			break;

		for (int i = 1; i <= n; i++)
			is_out[i] = false;


		while (c) {
			for (int i = 0; i < k;) {
				i++;
				do {
					l = (l == n) ? 1 : l + 1;
				} while (is_out[l] == true);
			}
			for (int i = 0; i < m; i++) {
				do {
					r = (r == 1) ? n : r - 1;
				} while (is_out[r] == true);
			}
			if (r == l) {
				c -= 1;
				is_out[l] = true;
				cout << setw(3) << l;
			} else {
				c -= 2;
				is_out[l] = true;
				is_out[r] = true;
				cout << setw(3) << l << setw(3)<< r;
			}
				if (c >= 1)
					cout << ',';
		}
		cout << endl;
	}

	return 0;
}
