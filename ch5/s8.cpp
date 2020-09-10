// UVa400 - Unix ls
// By LaoZhang
// Date 2020-08-29

#include <iostream>
#include <iomanip>
#include <array>
#include <algorithm>

using namespace std;

array<string, 101> files;

int main(void)
{
	int n;

	while (cin >> n && n != 0) {
		string name;
		int max_len = 0, k = 0, g;

		for (int i = 0; i < n; i++) {
			cin >> name;
			max_len = max_len > name.length() ? max_len : name.length();
			files[i] = name;
		}
		sort(files.begin(), files.begin() + n);
		k = (60 - max_len) / (max_len + 2) + 1;
		g = (n + k - 1) / k;
		cout << "------------------------------------------------------------\n";
		for (int i = 0; i < g; i ++) {
			int j;
			for (j = 0; j < k - 1; j++) {
				if (i + j * g >= n)
					break;
				if (j > 0)
					cout << "  ";
				cout << setw(max_len) << left << files[i + j * g];
			}
			if (i * k + j >= n) {
				cout << '\n';
				break;
			} else {
				if (i + j * g >= n) {
					cout << '\n';
					continue;
				}
				if (j > 0)
					cout << "  ";
				cout << setw(max_len) << left;
				cout << files[i + j * g] << '\n';
			}
		}
	}
	return 0;
}
