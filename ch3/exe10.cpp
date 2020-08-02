// UVa1587
// By LaoZhang
// Date 2020-08-05

#include <iostream>

using namespace std;

struct side {
	int d, w, c = 0;
};

inline void swap(int &x, int &y)
{
	int t;
	if (x > y)
		return;
	t = x;
	x = y;
	y = t;
	return;
}

int main()
{
	int i, d, w;
	struct side side[6];
	

	while (1) {
		bool p = true;
		int c = 0, j = 0;
		i = 0;
		for (i = 0; i < 6; i++) {
			if (!(cin >> d >> w))
				return 0;

			// get input and do statistics
			swap(d, w);
			for (j = 0; j < c; j++) {
				if (side[j].d == d && side[j].w == w) {
					side[j].c++;
					break;
				}
			}
			if (j == c) {
				side[j].d = d;
				side[j].w = w;
				side[j].c = 1;
				c += 1;
			}
		}

		if (c == 1) {
			// only 1 kind of rectangle, so it must be square
			if (side[0].d == side[0].w)
				p = true;
			else
				p = false;
		} else if (c == 2) {
			// 2 kinds of rectangles, one kind should be two squares
			// with the same side length
			if (side[0].c == 4 && side[1].c == 2) {
				if (side[1].d != side[1].w)
					p = false;
				else if (side[0].d != side[1].d && side[0].w != side[1].w)
					p = false;
			} else if (side[1].c == 4 && side[0].c == 2) {
				if (side[0].d != side[0].w)
					p = false;
				else if (side[1].d != side[0].d && side[1].w != side[0].w)
					p = false;
			} else {
				p = false;
			}
		} else if (c == 3) {
			// 3 kinds of rectangles
			if (side[0].c != 2 || side[1].c != 2 || side[2].c != 2)
				p = false;
			else {
				if (side[0].d == side[1].d) {
					d = side[0].w;
					w = side[1].w;
				} else if (side[0].w == side[1].d) {
					d = side[0].d;
					w = side[1].w;
				} else if (side[0].d == side[1].w) {
					d = side[0].w;
					w = side[1].d;
				} else {
					d = side[0].d;
					w = side[1].d;
				}
				swap(d, w);
				if (side[2].d == d && side[2].w == w)
					p = true;
				else
					p = false;
			}

		} else {
			p = false;
		}

		if (p == false)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << "POSSIBLE" << endl;

	}
	return 0;
}
