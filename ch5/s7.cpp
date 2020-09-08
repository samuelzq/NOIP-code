// UVa207 - PGA Tour Prize Money
// By LaoZhang
// Date 2020-09-06


// Not AC hit runtime error
//
// 1. Remove players disqualified in first 2 rounds.
// 2. If more than 70 players left, sort all players by
//    first 2-rounds score. The best 70 players would be
//    checked for prize.
// 3. Sort palyers have 4-round scores.
// 4. Remove players disqualified in last 2-rounds.
// 5. Check players' prize according to their places.
//
// Note:
//   1. The order for tie case is not clearly discribed.
//   2. For prize, consider the accuracy of rounding.

#include <iostream>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

typedef struct {
	char name[22];
	char score[21];
	int  total = 0;
	int  q = 0;
	int  round = 0;
	char r[4];
	double  awards;
	bool t_flag = false;
	bool tie = false;
	bool dq = false;
	bool amateur = false;
} Player;

struct {
	bool operator() (Player &a, Player &b) {
		if (a.q != b.q)
			return a.q < b.q;
		else  { // should add tie flag here
			for (int i = 0; i < 20; i++) {
				if (a.name[i] != b.name[i])
					return a.name[i] < b.name[i];
			}
		}
	}
} q_cmp;

struct {
	bool operator() (Player &a, Player &b) {
		if (a.total != b.total)
			return a.total < b.total;
		else  { // should add tie flag here
			for (int i = 0; i < 20; i++) {
				if (a.name[i] != b.name[i])
					return a.name[i] < b.name[i];
			}
		}
	}
} my_cmp;

struct {
	bool operator() (Player &a, Player &b) {
		if (a.round != b.round)
			return a.round > b.round;
		else if (a.total != b.total)
			return a.total < b.total;
		else if (a.q != b.q)
			return a.q < b.q;
		else  { // should add tie flag here
			for (int i = 0; i < 20; i++) {
			if (a.name[i] != b.name[i])
				return a.name[i] < b.name[i];
			}
		}
	}
} dq_cmp;

double purse = 0.0;
double per[70];
Player players[145];
list<Player> player;
list<Player> dq_player;
int w = 9;

void output(void)
{
	cout << "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n";
	cout << "-----------------------------------------------------------------------\n";
	for (list<Player>::iterator it = player.begin(); it != player.end(); ++it) {
		cout << it->name;
		cout << setfill(' ') << left << setw(10) << it->r;
		cout << it->score;
		if (it->amateur != true) {
			cout << setfill(' ') << left << setw(10) << it->total;
			cout << '$' << setfill(' ') << right << setw(w) << fixed << setprecision(2) << it->awards << '\n';
		} else
			cout << setw(3) << it->total << '\n';
	}
	for (list<Player>::iterator it = dq_player.begin(); it != dq_player.end(); ++it) {
		char rk[10];
		cout << left << it->name;
		cout << "          ";
		cout << it->score;
		cout << left << "DQ\n";
	}
}

void fill_rank(Player &p, int r)
{
	int idx = 0;
	if (r > 9) {
		p.r[idx++] = r / 10 + '0';
		p.r[idx++] = r % 10 + '0';
	} else {
		p.r[idx++] = r + '0';
	}
	if (p.tie == true)
		p.r[idx++] = 'T';
	p.r[idx] = 0;
	return;

}
void cal_awd(void)
{
	int r = 1, p_idx = 0;
	int cnt = 0, s = 0;
	player.sort(q_cmp);
	if (70 < player.size()) {
		list<Player>::iterator it = player.begin();
		advance(it, 69);
		auto hit = it;
		hit++;
		while (hit != player.end() && hit->q == it->q) {
			hit++;
			cnt++;
		}
		player.resize(70 + cnt);
	}

	for (list<Player>::iterator it = player.begin(); it != player.end();) {
		auto hit = it;
		it++;
		if (hit->dq == true) {
			dq_player.push_back(*hit);
			player.erase(hit);
		}
	}
	player.sort(my_cmp);

	for (list<Player>::iterator it = player.begin(); it != player.end();) {
		double p = 0.0;
		auto hit = it;
		int cnt = 0, a = 0;

		for (; hit != player.end() && hit->total == it->total; hit++) {
			cnt++;
			if (hit->amateur == true) {
				a++;
				continue;
			}

			// Only the low 70 non-amateur places and
			// ties earn prize money.
			if (p_idx < 70)
				p += per[p_idx++];
			else
				p += 0;
		}

		// Round and keep percentile
		if (cnt - a > 0) {
			p /= (cnt - a);
			p = purse * p;
			double tmp = floor(p + 0.5);
			p = tmp / 100.00;
		}

		while (it != hit) {
			if (it->amateur == false) {
				it->awards = p;
				if (cnt - a > 1)
					it->tie = true;
			}
			fill_rank(*it, r);
			it++;
		}

		r += cnt;
	}
	dq_player.sort(dq_cmp);
}

void get_players(void)
{
	int n;
	string golf;
	player.clear();
	dq_player.clear();
	cin >> n;
	cin.get();
	for (int i = 0; i < n; i++) {
		int j = 0;
		string tmp;
		getline(cin, golf);
		tmp = golf.substr(0, 20);
		players[i].amateur = false;
		for (int j = 0; j < 20; j++) {
			players[i].name[j] = tmp[j];
			if (tmp[j] == '*')
				players[i].amateur = true;
		}
		players[i].name[20] = ' ';
		players[i].name[21] = 0;

		// get scores
		players[i].round = 0;
		players[i].q = 0;
		players[i].total = 0;
		players[i].tie = false;
		players[i].t_flag = false;
		players[i].dq = false;
		tmp = golf.substr(21, 32);
		memset(players[i].score, ' ', 20);
		for (j = 0; j < 4; j++) {
			int k = j * 5;
			int l = j * 3;
			if (tmp[l] == 'D') {
				players[i].dq = true;
				break;
			}
			players[i].round++;
			players[i].score[k] = tmp[l];
			players[i].score[k + 1] = tmp[l + 1];
			if (players[i].score[k + 1] != ' ')
				players[i].total += (players[i].score[k] - '0') * 10 + (players[i].score[k + 1] - '0');
			else
				players[i].total += players[i].score[k] - '0';
			if (j < 2) {
				if (players[i].score[k + 1] != ' ')
					players[i].q += (players[i].score[k] - '0') * 10 + (players[i].score[k + 1] - '0');
				else
					players[i].q += players[i].score[k] - '0';

			}
		}
		players[i].score[21] = 0;
		if (j > 1)
			player.push_back(players[i]);
	}
}

void get_purse(void)
{
	cin >> purse;
	for (int i = 0; i < 70; i++) {
		cin >> per[i];
	}
}

int main(void)
{
	int n;

	while (cin >> n && n != EOF) {
		while (n--) {
			get_purse();
			get_players();
			cal_awd();
			output();
			if (n >= 1)
				cout << '\n';
		}
	}
	return 0;
}
