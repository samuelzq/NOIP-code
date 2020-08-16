// UVa1589 - Xiangqi
// By LaoZhang
// Date 2020-08-15

#include <iostream>
#include <cstring>

const int N = 10;
const int w = 10;
const int l = 11;

using namespace std;

// General's possible move
enum {
	CUR = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

char board[l][w];
char gen_pos[5][2];  // general has 4 possible position in next step
char horse_pos[9][2]; // horse has 8 possible position in next step
char pos[N][2];
int pcnt = 0;

// possible postion for the next move
void general_pos(int x, int y)
{
	gen_pos[CUR][0] = x;
	gen_pos[CUR][1] = y;

	if (x == 4) {
		gen_pos[LEFT][0] = gen_pos[LEFT][1] = -1; // cannot move to the left
		gen_pos[UP][0] = x; gen_pos[UP][1] = y - 1;
		gen_pos[DOWN][0] = x; gen_pos[DOWN][1] = y + 1;
		gen_pos[RIGHT][0] = 5; gen_pos[RIGHT][1] = y;
		if (y == 1 || y == 8) {
			gen_pos[UP][0] = gen_pos[UP][1] = -1; // cannot move up
		} else if (y == 3 || y == 10) {
			gen_pos[DOWN][0] = gen_pos[DOWN][1] = -1;  // cannot move down
		}
	} else if (x == 6) {
		gen_pos[RIGHT][0] = gen_pos[RIGHT][1] = -1; // cannot move to the right
		gen_pos[UP][0] = x; gen_pos[UP][1] = y - 1;
		gen_pos[DOWN][0] = x; gen_pos[DOWN][1] = y + 1;
		gen_pos[LEFT][0] = 5; gen_pos[LEFT][1] = y;
		if (y == 1 || y == 8) {
			gen_pos[UP][0] = gen_pos[UP][1] = -1; // cannot move up
		} else if (y == 3 || y == 10) {
			gen_pos[DOWN][0] = gen_pos[DOWN][1] = -1;  // cannot move down
		}
	} else if (x == 5) {
		gen_pos[LEFT][0] = 4; gen_pos[LEFT][1] = y;
		gen_pos[RIGHT][0] = 6; gen_pos[RIGHT][1] = y;
		gen_pos[UP][0] = x; gen_pos[UP][1] = y - 1;
		gen_pos[DOWN][0] = x; gen_pos[DOWN][1] = y + 1;
		if (y == 1 || y == 8) {
			gen_pos[UP][0] = gen_pos[UP][1] = -1; // cannot move up
		} else if (y == 3 || y == 10) {
			gen_pos[DOWN][0] = gen_pos[DOWN][1] = -1;  // cannot move down
		}
	}
}

enum {
	CURR = 0,
	L_UP,      // left up/down
	L_DOWN,
	R_UP,
	R_DOWN,
	U_LEFT,
	U_RIGHT,
	D_LEFT,
	D_RIGHT
};

// whether be checked by a horse
bool horse_detected(int gx, int gy)
{
	int x, y;
	int hx, hy;

	// up left
	x = gx - 1; y = gy - 2;
	hx = gx - 1; hy = gy - 1; // hoggling position
	if (board[y][x] == 'H' && board[hy][hx] == 0)
		return true;

	// up right
	x = gx + 1; y = gy - 2;
	hx = gx + 1; hy = gy - 1; // hoggling position
	if (board[y][x] == 'H' && board[hy][hx] == 0)
		return true;

	// right up
	x = gx + 2; y = gy - 1;
	hx = gx + 1; hy = gy - 1; // hoggling position
	if (board[y][x] == 'H' && board[hy][hx] == 0)
		return true;

	// right down
	x = gx + 2; y = gy + 1;
	hx = gx + 1; hy = gy + 1; // hoggling position
	if (board[y][x] == 'H' && board[hy][hx] == 0)
		return true;

	// down right
	x = gx + 1; y = gy + 2;
	hx = gx + 1; hy = gy + 1; // hoggling position
	if (board[y][x] == 'H' && board[hy][hx] == 0)
		return true;

	// down left
	x = gx - 1; y = gy + 2;
	hx = gx - 1; hy = gy + 1; // hoggling position
	if (board[y][x] == 'H' && board[hy][hx] == 0)
		return true;

	// left down
	x = gx - 2; y = gy + 1;
	hx = gx - 1; hy = gy + 1; // hoggling position
	if (board[y][x] == 'H' && board[hy][hx] == 0)
		return true;

	// left up
	x = gx - 2; y = gy - 1;
	hx = gx - 1; hy = gy - 1; // hoggling position
	if (board[y][x] == 'H' && board[hy][hx] == 0)
		return true;

	return false;
}

// Check whether the target position is available
bool check_pos(int x, int y)
{
	int i, p;
	if (x == -1) // cannot move to that position
		return true;

	p = 0;
	i = x - 1;
	while (i >= 1) {
		if ((board[y][i] == 'R' || board[y][i] == 'G') && p == 0)
			return true;
		else if (board[y][i] == 'C' && p == 1)
			return true;
		else if (board[y][i] != 0)
			p++;
		i--;
	}
	i = x;
	p = 0;
	while (++i <= 9) {
		if (board[y][i] == 'R' && p == 0)
			return true;
		else if (board[y][i] == 'C' && p == 1)
			return true;
		else if (board[y][i] != 0)
			p++;
	}
	p = 0;
	i = y;
	while (i-- >= 1) {
		if ((board[i][x] == 'R' || board[i][x] == 'G') && p == 0)
			return true;
		else if (board[i][x] == 'C' && p == 1)
			return true;
		else if (board[i][x] != 0)
			p++;
	}
	p = 0;
	i = y;
	while (i++ <= 10) {
		if ((board[i][x] == 'R' || board[i][x] == 'G') && p == 0)
			return true;
		else if (board[i][x] == 'C' && p == 1)
			return true;
		else if (board[i][x] != 0)
			p++;
	}

	// no Cannon nor Chariot. Now check horse
	return horse_detected(x, y);
}

int main()
{
	int i, x, y;
	char c;

	while (cin >> pcnt >> y >> x) {
		int g_x = 0, g_y = 0;
		memset(board, 0, sizeof(board));
		if (pcnt == 0)
			break;

		general_pos(x, y);

		for (i = 0; i < pcnt; i++) {
			cin >> c >> y >> x;
			board[y][x] = c;
			if (c == 'G') {
				g_x = x;
				g_y = y;
			}
		}

		if (g_x == gen_pos[CUR][0]) {
			for (i = gen_pos[CUR][1]; i < g_y; i++) {
				if (board[i][g_x] != 0)
					break;
			}
			// Check whether there is any other piece between two generals
			if (i == g_y) {
				// Red general is "Flying general"
				cout << "NO\n";
				continue;
			}
		}
		for (i = 1; i < 5; i++) {
			if (check_pos(gen_pos[i][0], gen_pos[i][1]) == false)
				break;
		}
		if (i == 5) // all possible position are not avalible "Checkmate"
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
