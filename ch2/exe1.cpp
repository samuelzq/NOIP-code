// daffodil
// By LaoZhang
// Data 2020-08-01

#include <iostream>

int main()
{
	int a, b, c;

	for (int i = 100; i < 1000; i++) {
		a = i / 100;
		b = (i - a * 100) / 10;
		c = i - a * 100 - b * 10;

		if (i == (a * a * a + b * b * b + c * c * c))
			std::cout << i << '\n';
	}
	std::cout << std::endl;
	return 0;
}
