// UVa1339
// By LaoZhang
// Date 2020-08-07
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 105;
char s1[N], s2[N];
int c1[26], c2[26];

// sort using a custom function object
struct {
	bool operator()(int a, int b) const {return a > b;}
} customBig;

int main()
{
	while (cin >> s1 >> s2) {
		bool is_match = true;
		int i, l;
		for (i = 0; i < 26; i++)
			c1[i] = c2[i] = 0;
		l = strlen(s1);
		if (l != strlen(s2)) {
			cout << "NO." << endl;
			continue;
		}

		for (i = 0; i < l; i++) {
			c1[s1[i] - 'A']++;
			c2[s2[i] - 'A']++;
		}

		sort(c1, c1 + 26, customBig);
		sort(c2, c2 + 26, customBig);

		for (i = 0; i < 26; i++) {
			if (c1[i] != c2[i]) {
				is_match = false;
				break;
			}
			else if (c1[i] == 0)
				break;
		}
		if (is_match == true)
			cout << "YES";
		else
			cout << "NO";
		cout << endl;
	}
	return 0;
}
