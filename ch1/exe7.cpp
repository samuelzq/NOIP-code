// exe 1-7 (leap year)
// By LaoZhang
// Date: 2020-07-31

#include <cstdio>

int main()
{
	int a;
	bool l = false;

	scanf("%d", &a);

	if (a % 4 == 0) {
		l = true;
		if ((a % 100 == 0) && (a % 400 != 0))
			l = false;
	}

	printf("Year %d is%s a leap year.\n", a, (l == true) ? "" : " not");
	return 0;
}
