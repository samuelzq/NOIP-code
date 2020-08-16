// UVa201 Square
// By LaoZhang
// Date 2020-08-16

#include <iostream>
#include <cstring>

using namespace std;

const int N = 10;


struct square{
	bool cn = false;  // whether counted
	short y = 0;   // max horizontal conections (RIght side)
	short x = 0;   // max vertical connections (Down side)
} vec[N][N];

bool no_square = true; // flag for no square exists
short cnt[N];  // counts of squares in different size
int n = 0;  // size of the square

void out(int idx)
{
	cout << "Problem #" << idx << "\n\n";
	if (no_square)
		cout << "No completed squares can be found.\n";
	else {
		for (int i = 0; i < n; i++) {
			if (cnt[i])
				cout << cnt[i] << " square (s) of size " << i << '\n';
		}
	}
	cout << '\n';
}

// update conected length
void update_con(char d, int i, int j)
{
	if (d == 'V') {
		vec[j + 1][i].y += vec[j][i].y + 1;

		for (int k = j + 2; k <= n; k++) {
			if (vec[k][i].y == 0)
				break;
			vec[k][i].y += vec[j][i].y + 1;
		}
	} else {
		vec[i][j + 1].x += vec[i][j].x + 1;

		for (int k = j + 2; k <= n; k++) {
			if (vec[i][k].x == 0)
				break;
			vec[i][k].x += vec[i][j].x + 1;
		}
	}
	return;
}

#define MIN(x, y) ((x) > (y) ? (y) : (x))
// do stats using bfs
void stats_sqr(int x, int y)
{
	if (x == 1 || y == 1 || vec[y][x].cn == true)
		return;

	// count square which takes (x, y) as a vertex
	int i;
	i = MIN(vec[y][x].x, vec[y][x].y);
	while (i) {
		if (vec[y - i][x].x >= i && vec[y][x - i].y >= i) {
			no_square = false;
			cnt[i]++;
		}
		i--;
	}

	// BFS
	stats_sqr(x, y - 1);
	stats_sqr(x - 1, y);
	vec[y][x].cn = true;
}

int main()
{
	int kase = 0;
	while (cin >> n) {
		int l = 0;
		char d;
		int s, w;

		no_square = true;
		memset(vec, 0, sizeof(vec));
		memset(cnt, 0, sizeof(cnt));

		cin >> l;
		for (int i = 0; i < l; i++) {
			cin >> d >> s >> w;
			update_con(d, s, w);
		}

		stats_sqr(n, n);
		if (kase > 0)
			cout << "**********************************\n\n";
		out(++kase);
	}
	return 0;
}

