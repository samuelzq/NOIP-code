// UVa207 - PGA Tour Prize Money
// By LaoZhang
// Date 2020-09-06

#include <iostream>
#include <list>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

typedef struct {
	string name;
	string score[4];
	int  total;
	int  rank;
	char r[4];
	double  awards;
	bool tie = false;
	bool dq = false;
	bool amateur = false;
} Player;

struct {
	bool operator() (const Player &a, const Player &b) const {
		if (a.total != b.total)
			return a.total < b.total;
		esle  { // should add tie flag here
			a.tie = b.tie = true;
			return strcmp(a.name, b.name);
		}
	}
} my_cmp;

double purse = 0.0;
double per[70];
Player players[140];
list<Player> player;

void output(void)
{
	player.sort(my_cmp);

	cout << "Player NamePlace     RDJ  RD2  RD3  RD4  TOTAL     Money Won\n";
	cout << "-------------------------------------------------------------\n"
	for (list<Player>::iterator it = player.begin(); it != player.end(); ++it) {
		int r = 1, idx = 0;
		char rk[10];
		cout << setw(21) << left << it.name;
		if (r > 10) {
			rk[idx++] = r / 10;
			rk[idx++] = r % 10;
		} else {
			rk[idx++] = r;
		}
		if (it.tie == true)
			r[idx++] = 'T';
		else
			r++;
		r[idx] = 0;
		cout << setw(10) << left << r;
		for (int i = 0; i < 4; i++)
			cout << setw(5) << left << it.score[i];
		cout << setw(10) << left << it.total;
		cout << '$' << setw(9) << right << fixed << setprecision(2) << it.awards + 0.005 << '\n';
	}
}

void get_players(int n)
{
	string golf;
	for (int i = 0; i < n; i++) {
		getline(cin, golf);
		players[i].name = golf.substr(0, 20);
		for (auto rit = players[i].name.crbegin(); rit! = players[i].name.crend(); ++rit) {
			if (*rit == ' ')
				*rit = 0;
			else if (*rt == '*')
				players[i].amateur = true;
			else
				break;
		}
			
		for (int j = 0; j < 4; j++) {
			int s = 21 + j * 3;
			players[i].score[j] = golf.substr(s, s + 2);
			if (players[i].score[j] == "DQ")
				break;
			players[i].total = (players[i].score[j][0] - '0') * 10 + (players[i].score[j][1] - '0');
		}
		player.insert(players[i]);
	}
}

void get_purse(void)
{
	cin >> total;
	for (int i = 0; i < 70; i++) {
		cin >> purse[i];
	}
}

int main(void)
{
	int n;

	while (cin >> n) {
		while (n--) {
			get_players(n);
			output();
		}
	}
	return 0;
}
