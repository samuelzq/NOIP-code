// UVa1225
// By LaoZhang
// Date 2020-08-03

#include <iostream>

using namespace std;
int ans[10];

int main()
{
	int t;

	cin >> t;
	while (t--) {
		int n;
		cin >> n;

		for (int i = 0; i < 10; i++)
			ans[i] = 0;
		for (int i = 1; i <= n; i++) {
			int tmp = i;
			while (tmp) {
				ans[tmp % 10]++;
				tmp /= 10;
			}
		}

		for (int i = 0; i < 9; i++)
			cout << ans[i] << ' ';
		cout << ans[9] << endl;
	}
	return 0;
}
