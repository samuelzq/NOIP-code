// UVa232
// By LaoZhang
// Date 2020-08-04

#include <iostream>
#include <string>

using namespace std;

struct puzzle {
	int r = 0, c = 0;
	char code[10][10];
	struct {
		int x = 10;
		int y = 10;
	} lb[100];
	int n = 0;
};

bool is_eligible(struct puzzle &p, int x, int y)
{
	if (p.code[y][x] == '*')
		return false;
	if (y == 0 || x == 0)
		return true;
	if (p.code[y - 1][x] == '*' || p.code[y][x - 1] == '*')
		return true;
	return false;
}

void get_puzzle(struct puzzle &p)
{
	bool e = true;
	int n, c, r, t = 1;
	string s;

	cin >> r >> c;
	p.r = r;
	p.c = c;

	for (int i = 0; i < r; i++) {
		cin >> s;
		for (int j = 0; j < c; j++) {
			p.code[i][j] = s[j];
			if (is_eligible(p, j, i)) {
				p.lb[p.n].x = j;
				p.lb[p.n].y = i;
				p.n += 1;
			}
		}
	}
}

void resolve_puzzle(struct puzzle &p)
{
	int x = 0, y = 0;
	bool e = true;
	cout << "Across";
	for (int i = 0; i < p.n; i++) {
		x = p.lb[i].x;
		y = p.lb[i].y;
		if (x > 0 && p.code[y][x - 1] != '*') {
			continue;
		}
		e = true;
		for (; x < p.c; x++) {
			if (e == true) {
				cout << '\n' << ' ' << i + 1 << '.';
				cout << p.code[y][x];
				e = false;
			} else {
				if (p.code[y][x] != '*')
					cout << p.code[y][x];
				else
					break;
			}
		}
	}
	e = true;
	cout << "\nDown";
	for (int i = 0; i < p.n; i++) {
		x = p.lb[i].x;
		y = p.lb[i].y;
		if (y > 0 && p.code[y - 1][x] != '*')
			continue;
		e = true;
		for (; y < p.r; y++) {
			if (e == true) {
				cout << '\n' << ' ' << i + 1 << '.';
				cout << p.code[y][x];
				e = false;
			} else {
				if (p.code[y][x] != '*')
					cout << p.code[y][x];
				else
					break;
			}
		}
	}
	cout << endl;
}

int main()
{
	struct puzzle p;
	get_puzzle(p);
	resolve_puzzle(p);
	return 0;
}
