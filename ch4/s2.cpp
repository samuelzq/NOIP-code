// UVa489
// By LaoZhang
// Date 2020-08-07

#include <iostream>
#include <string>

using namespace std;

int c1[26];

int main()
{
	int kase = 0, c, e, l1, l2;
	string s1, s2;

	while (cin >> kase && kase != -1) {
		cin >> s1 >> s2;
		l1 = s1.length();
		l2 = s2.length();

		c = 0;
		e = 0;
		for (int i = 0; i < 26; i++)
			c1[i] = 0;

		for (int i = 0; i < l1; i++) {
			if (!c1[s1[i] - 'a']++)
				c++;
		}

		for (int i = 0; i < l2 && c > 0; i++) {
			if (c1[s2[i] - 'a'] == 0) {
				c1[s2[i] - 'a'] = -1;
				e++;
			} else if (c1[s2[i] - 'a'] == -1)
				continue;
			else {
				c1[s2[i] - 'a'] = -1;
				c--;
			}
		}
		cout << "Round " << kase << '\n';
		if (e >= 7)
			cout << "You lose." << endl;
		else if (c <= 0)
			cout << "You win." << endl;
		else
			cout << "You chickened out." << endl;
	}
	return 0;
}
