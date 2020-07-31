// exe 1-6 (tirangle)
// By LaoZhang
// Date: 2020-07-31

#include <cstdio>

#define SWP(x, y) do{int t = (y); (y) = (x); (x) = t;}while(0)
void reorder(int &a, int &b, int &c)
{
	// b is the biggest
	if ((b >= a) && (b >= c))
		SWP(a, b);

	// c is the biggest
	if ((c >= a) && (c >= b))
		SWP(a, c);

	// now a is the biggest
	if (b < c)
		SWP(b, c);
	return;
}

int main()
{
	int a, b, c;

	scanf("%d %d %d", &a, &b, &c);

	reorder(a, b, c);
	if (a >= b + c) {
		printf("Not a triangle\n");
		return -1;
	}

	if (a * a == (b * b + c * c))
		printf("It is a right triangle.\n");
	else
		printf("It is not a right triangle.\n");

	return 0;
}
