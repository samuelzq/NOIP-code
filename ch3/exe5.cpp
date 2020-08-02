// UVa227
// By LaoZhang
// Date 2020-08-04

#include <iostream>
#include <string>

using namespace std;

struct puzzle {
	int bx = 0, by = 0;
	char code[5][5];
	string move;
};

int process_puzzle(struct puzzle &p)
{
	int x = 0, y = 0, n;

	n = p.move.length();
	for (int i = 0; i < n; i++) {
		switch (p.move[i]) {
			case 'A':
				if (p.by == 0)
					return -1;
				x = p.bx;
				y = p.by - 1;
				p.code[p.by][p.bx] = p.code[y][x];
				p.code[y][x] = ' ';
				p.by = y;
				break;
			case 'B':
				if (p.by == 4)
					return -1;
				x = p.bx;
				y = p.by + 1;
				p.code[p.by][p.bx] = p.code[y][x];
				p.code[y][x] = ' ';
				p.by = y;
				break;
			case 'R':
				if (p.bx == 5)
					return -1;
				x = p.bx + 1;
				y = p.by;
				p.code[p.by][p.bx] = p.code[y][x];
				p.code[y][x] = ' ';
				p.bx = x;
				break;
			case 'L':
				if (p.bx == 0)
					return -1;
				x = p.bx - 1;
				y = p.by;
				p.code[p.by][p.bx] = p.code[y][x];
				p.code[y][x] = ' ';
				p.bx = x;
				break;
			case '0':
				return 0;
		}
	}
	return -1;
}

void get_puzzle(struct puzzle &p)
{
	string tmp;

	for (int i = 0; i < 5; i++) {
		int l;
		getline(cin, tmp);
		l = tmp.length();
		l = (l < 5) ? l : 5;
		if (l < 5) {
			p.code[i][4] = ' ';
			p.bx = 4;
			p.by = i;
		}
		for (int j = 0; j < l; j++) {
			p.code[i][j] = tmp[j];
			if (tmp[j] == ' ') {
				p.bx = j;
				p.by = i;
			}
		}
	}
	cin >> tmp;
	p.move = tmp;
	while (tmp.back() != '0') {
		cin >> tmp;
		p.move = p.move + tmp;
	}
}

void out_puzzle(struct puzzle &p)
{
	for (int i = 0; i < 5; i++) {
		int j = 0;
		for (j = 0; j < 4; j++)
			cout << p.code[i][j] << ' ';
		cout << p.code[i][j] << '\n';
	}
	cout << endl;
}

int main()
{
	struct puzzle p;

	get_puzzle(p);

	if (process_puzzle(p) == 0)
		out_puzzle(p);
	else
		cout << "This puzzle has no final configuration.\n";

	return 0;
}
