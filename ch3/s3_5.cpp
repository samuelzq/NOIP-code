// UVa1583
// By LaoZhang
// Date 2020-08-02

#include <cstring>
#include <cstdio>

const int N = 1000005;

int m[N];

int main()
{
	int n;

	memset(m, 0, sizeof(m));

	for (int i = 1; i < N; i++) {
		int r, t;

		r = t = i;

		while (r) {
			t += r % 10;
			r = r / 10;
		}
		if (!m[t])
			m[t] = i;
	}

	scanf("%d", &n);
	printf("%d\n", m[n]);
	return 0;
}
