// Subsequence
// By LaoZhang
// Date 2020-08-01

#include <iostream>

using namespace std;

int main()
{
	int n, m;

	while (cin >> n >> m){
		float s = 0;

		if (n < m) {
			while (n <= m) {
				s += 1.0 / n / n;
				n++;
			}
		}
		cout << s << '\n';
	}
	cout << endl;
	return 0;
}
