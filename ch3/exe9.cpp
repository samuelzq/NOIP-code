// UVa 10340
// By Lao Zhang
// Date 2020-08-05

#include <iostream>
#include <string>

using namespace std;

int main()
{
	bool match = false;
	int n, m;
	string s, t;

	cin >> s >> t;
	n = s.length();
	m = t.length();

	for (int l = 0, i = 0; i < n; i++) {
		for (int j = l; j < m; j++) {
			if (s[i] == t[j]) {
				l = j;
				match = true;
				break;
			}
		}
		if ((match == false) || (i == n - 1))
			break;
		else
			match = false;
	}
	cout << (match ? "Yes" : "No") << endl;
	return 0;
}