// decimal
// By LaoZhang
// Date 2020-08-01

#include <iostream>

const int N = 105;
int r[N];

using namespace std;

int main()
{
	int a, b , c;

	while (cin >> a >> b >> c) {
		int d = 0;
		int i = 0;
		if (a + b + c == 0)
			break;

		d = a / b;
		cout << d << '.';
		a = a * 10 - d * b * 10;
		for (i = 0; i < c && a != d * b; i++) {
			r[i] = a / b;
			a = a * 10 - r[i] * b * 10;
		}

		for (int j = 0; j < i; j++)
			cout << r[j];
		cout << endl;
	}
}
