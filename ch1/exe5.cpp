// exe 1-5 (discount)
// By LaoZhang
// Date: 2020-07-31

#include <cstdio>

int main()
{
	int n;
	float ans;

	scanf("%d", &n);
	ans = n * 95;
	if (ans >= 300)
		ans *= 0.85;
	printf("%.2f\n", ans);
	return 0;
}
