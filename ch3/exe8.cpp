// UVa202
// By LaoZhang
// Date 2020-08-05

#include <iostream>

const int N = 55;
char digt[N];

using namespace std;

int main()
{
	int i, n, m, d, fr = 0,r = 0, q = 0;

	cin >> n >> d;

	m = n;
	q = n / d;
	r = n - q * d;
	fr = r;
	i = 0;
	n = r * 10;

	do {
		r = n / d;
		if (i < 50)
			digt[i] = r + '0';
		i++;
		r = n - r * d;
		n = r * 10;
	} while (r > 0 && r != fr);
	if (i >= 50) {
		digt[50] = digt[51] = digt[52] = '.';
		digt[53] = 0;
	} else {
		digt[i] = 0;
	}

	cout << m << '/' << d << " = "  << q;
	if (i > 0) {
		cout << ".";
		if (r != 0)
			cout << '(' << digt << ')';
		else
			cout << digt << "(0)";
	}
	cout << "\n\t" << i << " = number of digits in repeating cycle";
	cout << endl;
	return 0;
}