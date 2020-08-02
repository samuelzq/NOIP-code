// UVa1584
// By LaoZhang
// Date 2020-08-02

#include <iostream>
#include <string>

using namespace std;
bool str_less(string s, int p1, int p2)
{
	if (p1 == p2)
		return false;

	int n = s.length();

	for (int i = 0; i < n; i++) {
		if (s[(p1 + i) % n] != s[(p2 + i) % n])
			return s[(p1 + i) % n] < s[(p2 + i) % n];
	}

	return false;
}

int main()
{
	int n;
	string s;


	cin >> n;
	while (n--) {
		cin >> s;
		int ans = 0;
		int n = s.length();

		for (int i = 1; i < n; i++) {
			if (str_less(s, i, ans))
				ans = i;
		}

		for (int i = 0; i < n; i++)
			cout << s[(i + ans) % n];
		cout << endl;
	}
	return 0;
}
