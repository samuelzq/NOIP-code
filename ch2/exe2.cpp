// hanxin
// By LaoZhang
// Date 2020-08-01

#include <iostream>

int main()
{
	bool t = false;
	int a, b, c;

	std::cin >> a >> b >> c;

	for (int i = 7 + c; i < 100; i += 7) {
		if (i < 10)
			continue;
		if (i % 5 != b)
			continue;
		if (i % 3 == a) {
			std::cout << i << '\n';
			t = true;
		}
	}
	if (t == false)
		std::cout << "No answer";
	std::cout << std::endl;
	return 0;
}
