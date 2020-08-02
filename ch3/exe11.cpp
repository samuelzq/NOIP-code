// UVa1588
// By Zhang Qian
// Date 2020-08-06

#include <cstdio>
#include <cstring>

const int N = 105;

char mb[N];
char db[N];

int main()
{
	bool t = false;
	char *m, *d;
	int s, lm, ld, ans;
	scanf("%s%s", mb, db);
	lm = strlen(mb);
	ld = strlen(db);

	if (lm >= ld) {
		s = lm;
		lm = ld;
		ld = s;
		m = db;
		d = mb;
	} else {
		m = mb;
		d = db;
	}

	s = 0;

	while (t == false && s < ld) {
		int i = 0;
		for (i = 0; i < lm && i + s < ld; i++) {
			if (m[i] + d[s + i] - '0' > '3')
				break;
		}
		if (i == lm || i + s == ld)
			t = true;
		else {
			int j = i;
			while (i-- > 0 && m[i] == '2');
			s += (j - i);
		}
	}

	if (s + lm < ld)
		ans = ld;
	else 
		ans = s + lm;

	printf("%d\n", ans);
	return 0;
}
