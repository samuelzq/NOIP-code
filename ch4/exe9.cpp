// UVa1591 - Data Mining
// By LaoZhang
// Date 2020-08-23

#include <iostream>

using namespace std;

int main(void)
{
	unsigned int n = 0, sp = 0, sq = 0;

	while (cin >> n >> sp >> sq) {
		unsigned long long a = 0, b = 0, k = ~0;
		int i, j;

		for (i = 0; i < 32; i++) {
			for (j = 0; j < 32; j++) {
				unsigned long long s = 0;
				s = (n - 1) * sp;
				s = ((s + (s << i)) >> j) + sq;
				// d=Q(i+1)-Q(i)=(P(i+1)-P(i))(1+2^A)/(2^B)=Sp(1+2^A)/(2^B) >= Sq
				// if (s >= n * sq && (sp + (sp << i)) >= (sq << j) && k > s) {
				if (s >= n * sq && k > s) {
					k = s;
					a = i;
					b = j;
				}
			}
		}
		if (k == ~0)
			cout << n * sq << ' ' << 0 << ' ' << 0 << '\n';
		else
			cout << k << ' ' << a << ' ' << b << '\n';
	}

	return 0;
}
