#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const string rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const string msg[] = {
	"not a palindrome",
	"a regular palindrome",
	"a mirrored string",
	"a mirrored palindrome"
};

char r(char ch)
{
	if (isalpha(ch))
		return rev[ch - 'A'];

	return rev[ch - '0' + 25];
}

int main()
{
	string s;

	while (cin >> s) {
		int len = s.length();
		int p = 1, m = 1;

		for (int i = 0; i < (len + 1) / 2; i++) {
			if (s[i] != s[len - i - 1])
				p = 0;
			if (r(s[i]) != s[len - i - 1])
				m = 0;
		}
		cout << s << " is " << msg[m * 2 + p] << endl;
	}
	return 0;
}
