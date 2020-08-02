// UVa1585
// By LaoZhang
// Date 2020-08-02

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int t, n, ans = 0;
	string s;

	cin >> t;
	while (t--) {
		cin >> s;
		n = s.length();

		int t = -1;
		ans = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] != 'O')
				t = i;
			ans += i - t;
		}
		cout << ans << endl;
	}
	return 0;
}
