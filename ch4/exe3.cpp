// UVa220 - Othello
// By LaoZhang
// Date 2020-08-18

#include <cstdlib>
#include <cstdio>
#include <cstring>

const int N = 9;

struct pos {
	int x = 0;
	int y = 0;
};
char board[N + 1][N + 1];
struct pos b[N * N];
struct pos w[N * N];
int b_cnt = 0, w_cnt = 0;
char cmd[4];
char cur_player = 0;
const char f = 1 << 7;  // possible position flag;

#define SPACE                 '-'
#define WHITE                 'W'
#define BLACK                 'B'

#define UP_LEFT                 (1 << 0)      // flag for up left check
#define UP                      (1 << 1)      // flag for up check
#define UP_RIGHT                (1 << 2)      // flag for up right check
#define RIGHT                   (1 << 3)      // flag for right check
#define DOWN_RIGHT              (1 << 4)      // flag for right down check
#define DOWN                    (1 << 5)      // flag for down check
#define DOWN_LEFT               (1 << 6)      // flag for down left check
#define LEFT                    (1 << 7)      // flag for left check
#define DEFAULT_CHECK           (UP_LEFT | UP | UP_RIGHT | RIGHT | DOWN_RIGHT | DOWN | DOWN_LEFT | LEFT)
#define FIRST_ROW_CHECK         (DOWN | DOWN_RIGHT | DOWN_LEFT | LEFT | RIGHT)
#define FIRST_COL_CHECK         (RIGHT | UP_RIGHT | DOWN_RIGHT | UP | DOWN)
#define LAST_ROW_CHECK          (UP | UP_LEFT | UP_RIGHT | LEFT | RIGHT)
#define LAST_COL_CHECK          (LEFT | UP_LEFT | DOWN_LEFT | UP | DOWN)
#define IS_SPACE(x)             ((x) == SPACE || (x) == (f | SPACE))

void do_stats(void)
{
	w_cnt = b_cnt = 0;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j <  9; j++) {
			if (board[i][j] == 'B') {
				b[b_cnt].x = j;
				b[b_cnt].y = i;
				b_cnt += 1;
			} else if (board[i][j] == 'W') {
				w[w_cnt].x = j;
				w[w_cnt].y = i;
				w_cnt += 1;
			}
		}
	}

	return;
}

void quit(void)
{
	for (int i = 1; i <= 8; i++)
		printf("%s\n", &board[i][1]);
}

int l, r, u, d, x, y;
struct ppos {
	int *r = NULL;
	int *c = NULL;
};
enum {
	up_left = 0,
	up,
	up_right,
	right,
	down_right,
	down,
	down_left,
	left,
	num_check_ponits
};

int flags[num_check_ponits] = {
	UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT
};

// Following check points start from up-left in clockcycle direction
struct ppos check_points[num_check_ponits];

inline void init_check_points(int row, int col)
{

	x = l = r = col;
	y = d = u = row;
	l--;
	r++;
	d++;
	u--;
	check_points[up_left].r = check_points[up].r = check_points[up_right].r = &u;
	check_points[up_left].c = &l; check_points[up].c = &x; check_points[up_right].c = &r;
	check_points[right].r = &y; check_points[right].c = &r;
	check_points[down_right].r = &d; check_points[down_right].c = &r;
	check_points[down].r = &d; check_points[down].c = &x;
	check_points[down_left].r = &d; check_points[down_left].c = &l;
	check_points[left].r = &y; check_points[left].c = &l;
}

inline void init_check(int row, int col, int &check)
{
	if (col == 1)
		check &= FIRST_COL_CHECK;

	if (col == 8)
		check &= LAST_COL_CHECK;

	if (row == 1)
		check &= FIRST_ROW_CHECK;

	if (row == 8)
		check &= LAST_ROW_CHECK;

	init_check_points(row, col);
	for (int i = 0; i < num_check_ponits; i++) {
		int col, row;
		col = *check_points[i].c;
		row = *check_points[i].r;

		if (IS_SPACE(board[row][col]))
			check &= ~flags[i];
	}
}

void pos_check1(int &check)
{
	for (int i = 0; i < num_check_ponits; i++) {
		int col, row;
		col = *check_points[i].c;
		row = *check_points[i].r;

		if (!(check & flags[i]))
			continue;

		if (col <= 1)
			check &= ~(LEFT | UP_LEFT | DOWN_LEFT);
		if (row <= 1)
			check &= ~(UP | UP_LEFT | UP_RIGHT);
		if (col >= 8)
			check &= ~(RIGHT | UP_RIGHT | DOWN_RIGHT);
		if (row >= 8)
			check &= ~(DOWN | DOWN_RIGHT | DOWN_LEFT);
		if IS_SPACE(board[row][col]) { // find a possible position
			board[row][col] |= f;
			check &= ~flags[i];
		} else if (board[row][col] == cur_player)
			check &= ~flags[i];
	}
	l--;
	r++;
	d++;
	u--;
}

void do_list(void)
{
	char o; // other color to be checked
	int x, y, n;
	struct pos *p_list = NULL;

	if (cur_player == 'B') {
		p_list = b;
		o = 'W';
		n = b_cnt;
	}
	else if (cur_player == 'W') {
		p_list = w;
		o = 'B';
		n = w_cnt;
	} else {
		printf("Opp! This should never hapen!\n");
		exit(-1);
	}

	for (int i = 0; i < n; i++) {
		int check = DEFAULT_CHECK;
		int s, t, u, v;
		s = t = x = p_list[i].x;
		v = u = y = p_list[i].y;

		init_check(y, x, check);
		//- check
		while (check)
			pos_check1(check);
	}
	int c = 0;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (board[i][j] & f) {
				board[i][j] = SPACE;
				if (c)
					printf("%c", ' ');
				printf("(%d,%d)", i, j);
				c++;
			}
		}
	}
	if (!c)
		printf("No legal move.\n");
	else
		printf("\n");
	return;
}

void do_move(int x, int y)
{
	bool change_player = true;
	struct pos *p_list = NULL;
	char c, o = (cur_player == 'W') ? 'B' : 'W';

again:
	if (cur_player == 'B') {
		p_list = b;
		o = 'W';
	} else if (cur_player == 'W') {
		p_list = w;
		o = 'B';
	} else {
		printf("Opp! This should never hapen!\n");
		exit(-1);
	}
	int check = DEFAULT_CHECK;
	int s, t, u, v;
	s = t = x;
	v = u = y;

	init_check(y, x, check);

	s--;
	t++;
	v--;
	u++;
	if (board[v][s] == SPACE || board[v][s] == cur_player)
		check &= ~UP_LEFT;
	if (board[v][x] == SPACE || board[v][x] == cur_player)
		check &= ~UP;
	if (board[v][t] == SPACE || board[v][t] == cur_player)
		check &= ~UP_RIGHT;
	if (board[y][s] == SPACE || board[y][s] == cur_player)
		check &= ~LEFT;
	if (board[y][t] == SPACE || board[y][t] == cur_player)
		check &= ~RIGHT;
	if (board[u][s] == SPACE || board[u][s] == cur_player)
		check &= ~DOWN_LEFT;
	if (board[u][x] == SPACE || board[u][x] == cur_player)
		check &= ~DOWN;
	if (board[u][t] == SPACE || board[u][t] == cur_player)
		check &= ~DOWN_RIGHT;
	while (check) {
		if (check & UP) { // do up check
			if (v == 1)
				check &= ~UP; // cannot go up anymore
			if (board[v][x] == cur_player) { // find a possible position
				change_player = false;
				for (int k = v; k < y; k++)
					board[k][x] = cur_player;
				check &= ~UP;
			} else if ((board[v][x] & ~f) == SPACE)
				check &= ~UP;
		}
		if (check & UP_LEFT) {
			if (v == 1 || s == 1)
				check &= ~UP_LEFT;
			if (board[v][s] == cur_player) {
				change_player = false;
				for (int k = 0; k < y - v; k++)
					board[v + k][s + k] = cur_player;
				check &= ~UP_LEFT;
			} else if ((board[v][s] & ~f) == SPACE)
				check &= ~UP_LEFT;
		}
		if (check & UP_RIGHT) {
			if (v == 1 || t == 8)
				check &= ~UP_RIGHT;
			if (board[v][t] == cur_player) {
				change_player = false;
				for (int k = 0; k < y - v; k++)
					board[v + k][t - k] = cur_player;
				check &= ~UP_RIGHT;
			} else if ((board[v][t] & ~f) == SPACE)
				check &= ~UP_RIGHT;
		}
		if (check & RIGHT) {
			if (t == 8)
				check &= ~RIGHT;
			if (board[y][t] == cur_player) {
				change_player = false;
				for (int k = t; k > x; k--)
					board[y][k] = cur_player;
				check &= ~RIGHT;
			} else if ((board[y][t] & ~f) == SPACE)
				check &= ~RIGHT;
		}
		if (check & LEFT) {
			if (s == 1)
				check &= ~LEFT;
			if (board[y][s] == cur_player) {
				change_player = false;
				for (int k = s; k < x; k++)
					board[y][k] = cur_player;
				check &= ~LEFT;
			} else if ((board[y][s] & ~f) == SPACE)
				check &= ~LEFT;
		}
		if (check & DOWN_RIGHT) {
			if (u == 8 || t == 8)
				check &= ~DOWN_RIGHT;
			if (board[u][t] == cur_player) {
				change_player = false;
				for (int k = 0; k < t - x; k++)
					board[u - k][t - k] = cur_player;
				check &= ~DOWN_RIGHT;
			} else if ((board[u][t] & ~f) == SPACE)
				check &= ~DOWN_RIGHT;
		}
		if (check & DOWN) {
			if (u == 8)
				check &= ~DOWN;
			if (board[u][x] == cur_player) {
				change_player = false;
				for (int k = u; k > y; k--)
					board[k][x] = cur_player;
				check &= ~DOWN;
			} else if ((board[u][x] & ~f) == SPACE)
				check &= ~DOWN;
		}
		if (check & DOWN_LEFT) {
			if (u == 8 || s == 1)
				check &= ~DOWN_LEFT;
			if (board[u][s] == cur_player) {
				change_player = false;
				for (int k = 0; k < x - s; k++)
					board[u - k][s + k] = cur_player;
				check &= ~DOWN_LEFT;
			} else if ((board[u][s] & ~f) == SPACE)
				check &= ~DOWN_LEFT;
		}
		s--;
		t++;
		v--;
		u++;
	}

	if (change_player == false)
		board[y][x] = cur_player;
	else {
		cur_player = o;
		change_player = false;
		goto again;
	}

	w_cnt = b_cnt = 0;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (board[i][j] == 'W') {
				w[w_cnt].x = j;
				w[w_cnt].y = i;
				w_cnt++;
			}

			if (board[i][j] == 'B') {
				b[b_cnt].x = j;
				b[b_cnt].y = i;
				b_cnt++;
			}
		}
	}
	printf("Black - %2d White - %2d\n", b_cnt, w_cnt);
	// change the current player
#if 0
	{
		// show results
		printf("Current player is %c\n", cur_player);
		quit();
	}
#endif
	cur_player = o;
	return;
}

int main(void)
{
	int n; // number of game to be processed

	scanf("%d", &n);

	while (n--) {
		for (int i = 1; i < N; i++) {
			scanf("%s", &board[i][1]);
			board[i][9] = 0;
		}
		do_stats();
		while (scanf("%s", cmd)) {
			if (cmd[0] == 'L') {
				// List all possible moves for the current player.
				do_list();
			} else if (cmd[0] == 'W') {
				// set current player to wight
				cur_player = 'W';
			} else if (cmd[0] == 'B') {
				// set current player to black
				cur_player = 'B';
			} else if (cmd[0] == 'M') {
				int y = cmd[1] - '0';
				int x = cmd[2] - '0';
				do_move(x, y);
			} else if (cmd[0] == 'Q') {
				quit();
				break;
			}
		}
		if (n)
			printf("\n");
	}
	return 0;
}
