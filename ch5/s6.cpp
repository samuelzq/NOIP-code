// UVa1592 - Database
// By LaoZhang
// Date 2020-08-29

#include <iostream>
#include <iomanip>
#include <string>
#include <cstddef>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
int id[10001][11];

typedef struct entry {
	int x = 0, y = 0;
}Entry;

map<string, int> IDString;   // map string in database to ID

struct cmp {
	bool operator () (const Entry a, const Entry b) const {
		if (a.x != b.x)
			return a.x < b.x;
		else
			return a.y < b.y;
	}
};
map<Entry, int, cmp> idx;

int main(void)
{
	int r, c;

	while (cin >> r >> c) {
		string line;
		string substr;
		size_t lpos = 0, pos = 0;
		cin.get();
		IDString.clear();
		idx.clear();
		for (int i = 0; i < r; i++) {
			getline(cin, line);
			for (int j = 0; j < c; j++) {
				pos = line.find(',', lpos);
				substr = line.substr(lpos, pos - lpos);
				lpos = pos + 1;
				if (!IDString.count(substr))
					IDString[substr] = i * c + j;
				id[i][j] = IDString[substr];
			}
		}

		bool is_pnf = true;
		int x1 = 0, x2 = 0, y1 = -1, y2 = 0, e = c;
		for (int i = 0; i < c - 1; i++) {
			for (int j = i + 1; j < c; j++) {
				idx.clear();
				for (int k = 0; k < r; k++) {
					Entry en;
					en.x = id[k][i];
					en.y = id[k][j];
					if (idx.count(en) != 0) {
						cout << "NO\n";
						cout << idx[en] + 1 << ' ' << k + 1 << '\n';
						cout << i + 1 << ' ' << j + 1 << '\n';
						is_pnf = false;
						goto next;
					}
					idx[en] = k;
				}
			}
		}

next:
		if (is_pnf == true)
			cout << "YES\n";
	}
	return 0;
}
