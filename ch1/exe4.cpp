// exe 1-4 (sin and cos)
// By LaoZhang
// Date: 2020-07-31

#include <cstdio>
#include <cmath>

int main()
{
	int n;
	const double pi = acos(-1);
	double a;

	scanf("%d", &n);
	a = n * pi / 180;
	printf("%f %f\n", sin(a), cos(a));
	return 0;
}
