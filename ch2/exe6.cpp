// permutation
// By LaoZhang
// Date 2020-08-01

#include <cstdio>

int main()
{
	int a[10];
	for (int i = 129; i < 333; i += 9) {
		int b, c, tmp;
		int l, n, m;
		b = i * 2;
		c = i * 3;

		for (int j = 1; j <= 9; j++)
			a[j] = 0;

		l = i / 100;
		n = (i - l * 100) / 10;
		m = i % 10;
		tmp = l + n + m;
		if (tmp != 12 || n == 0 || m == 0 || l == n || n == m)
			continue;

		a[l] = a[n] = a[m] = 1;

		l = b / 100;
		n = (b - l * 100) / 10;
		m = b % 10;
		tmp += l + n + m;

		if (tmp != 27 || n == 0 || m == 0 || l == n || n == m)
			continue;
		if (a[l] || a[n] || a[m])
			continue;
		a[l] = a[n] = a[m] = 1;

		l = c / 100;
		n = (c - l * 100) / 10;
		m = c % 10;
		tmp += l + n + m;

		if (tmp != 45 || n == 0 || m == 0 || l == n || n == m)
			continue;
		if (a[l] || a[n] || a[m])
			continue;
		a[l] = a[n] = a[m] = 1;

		printf("%d %d %d\n", i, b ,c);
	}
	return 0;
}
