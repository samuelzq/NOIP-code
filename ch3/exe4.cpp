// UVa455
// By LaoZhang
// Date 2020-08-04

#include <cstdio>
#include <cstring>
#include <cmath>

int di[20];   // no more than 20 factors
char s[82];

int get_factores(int n)
{
	int j = 0;
	int f = floor(sqrt(n) + 0.5);

	di[j++] = 1;
	for (int i = 2; i <= f; i++) {
		if (n % i == 0) {
			memcpy(di + j + 2, di + j, j - 1);
			di[j++] = i;
			di[j] = n / i;
		}
	}
	j *= 2;
	di[j - 1] = n;
	return j;
}

int main()
{
	int t;

	scanf("%d", &t);

	while (t--) {
		int i, d, n = 0;
		scanf("%s", s);
		n = strlen(s);
		d = get_factores(n);
		for (i = 0; i < d; i++) {
			bool m = true;
			for (int j = 0; j < n - di[i]; j += di[i]) {
				if (memcmp(s + j, s +j + di[i], di[i])) {
					m = false;
					break;
				}
			}
			if (m == true)
				break;
			else
				m = true;
		}
		printf("%d\n", di[i]);
	}
}
