// UVa1368
// By Lao Zhang
// Date 2020-08-05

#include <cstdio>

const int M = 51;
const int N = 1005;

struct seq {
	int m = 0, n = 0, d = 0, h = 0x1ffffff;
	char buf[M][N];
	int hamming[M];
};

int get_seq(struct seq &s)
{
	int m, h, n;

	m = s.m;
	n = s.n;
	for (int i = 0; i < m; i++)
		scanf("%s", s.buf[i]);
	for (int i = 0; i < m; i++) {
		h = 0;
		for (int j = 0; j < m; j++) {
			if (j == i)
				continue;
			for (int k = 0; k < n; k++) {
				if (s.buf[i][k] != s.buf[j][k])
					h++;
			}
		}
		s.hamming[i] = h;
		if (s.h > h) {
			s.h = h;
			s.d = i;
		}
	}
	return 0;
}

void output_cstr(struct seq &s)
{
	printf("%s\n%d\n", s.buf[s.d], s.h);
}

struct seq s;

int main()
{
	int m, n;

	scanf("%d%d", &m, &n);
	s.m = m;
	s.n = n;
	get_seq(s);
	output_cstr(s);
	return 0;
}