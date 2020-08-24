// UVa 815 - Flooded!
// By LaoZhang
// Date 2020-08-25

#include <iostream>
#include <iomanip>

using namespace std;

#define LL long long
const int N = 31;

int cnt = 0;
LL h[N * N]; // the elevations of the squares

// the elevations of the squares are sorted
// from low to high
void insert_elevation(LL e)
{
	int i;
	for (i = cnt; i > 0; i--) {
		if (e >= h[i - 1])
			break;
		else
			h[i] = h[i - 1];
	}
	h[i] = e;
	cnt++;
}

int main(void)
{
	int  m, n, reg = 1;

	while (cin >> m >> n && m != 0 && n != 0) {
		LL volumn = 0, dv = 0;
		int l = m * n, s = 1;
		double cl;
		cnt = 0;
		for (int i = 0; i < l; i++) {
			int e;
			cin >> e;
			insert_elevation(e);
		}
		cin >> volumn;
		cl = h[0];

		for (int i = 1; i < l; i++) {
			dv = (h[i] - h[i - 1]) * s * 100;
			if (volumn > dv) {
				volumn -= dv;
				cl = h[i];
				s += 1;
			} else {
				break;
			}
		}

		cl += (double)volumn / (100 * s);
		cout << "Region " << reg++ << '\n';
		cout << fixed << setprecision(2);
		cout << "Water level is " << cl << " meters.\n";
		cout << ((float)s * 100.00) / cnt << " percent of the region is under water.\n\n";
	}
	return 0;
}
