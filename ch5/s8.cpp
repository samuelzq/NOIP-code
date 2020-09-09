// UVa814 - The Letter Carrier's Rounds
// By LaoZhang
// Date: 2020-09-09
//
// Do not beleive the result for Test case 3/4/5 on uDebug.

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

set<string> receivers;
void get_users(void)
{
	string str;
	string name;
	receivers.clear();
	while (cin >> str && str != "*") {
		int cnt = 0;
		vector<string> users;
		if (str == "MTA")
			cin >> name >> cnt;
		for (int i = 0; i < cnt; i++) {
			string user;
			cin >> user;
			receivers.insert(user + '@' + name);
		}
	}
}

#define SPACE         "     "

vector<string> r_mta;
set<string> r_users;
map<string, vector<string>> receint;
string user, sender, tx_mta;
int get_recievers(void)
{
	int ret = -1;
	size_t pos = string::npos;

	cin >> user;
	if (user == "*")
		return ret;
	ret = 0;
	receint.clear();
	r_mta.clear();

	// check senders
	pos = user.find("@");
	sender = user.substr(0, pos);
	tx_mta = user.substr(pos + 1);

	r_users.clear();
	while (cin >> user && user != "*") {
		string receiver, rx_mta;
		if (r_users.count(user) > 0)  // check duplicated receivers
			continue;
		else
			r_users.insert(user);

		// Group receivers on the same MTA
		pos = user.find("@");
		receiver = user.substr(0, pos);
		rx_mta = user.substr(pos + 1);
		if (receint.count(rx_mta) == 0) {
			vector<string> rs;
			rs.push_back(receiver);
			receint[rx_mta] = rs;
			r_mta.push_back(rx_mta);
		}
		else
			receint[rx_mta].push_back(receiver);

	};
	return 1;
}

vector<string> mail;
void get_data(void)
{
	string str;
	mail.clear();
	cin.get();
	while (getline(cin, str) && str != "*")
		mail.push_back(str);
}

void send_data(void)
{
	int ret = 0;
	// connection and check receivers
	// Map will sorts etems.
	// destination MTA should be accessed following input order.
	// So a speciail container is used to keep the original input sequence.
	for (vector<string>::iterator it = r_mta.begin(); it != r_mta.end(); ++it) {
		cout << "Connection between " << tx_mta << " and " << *it << '\n';
		cout << SPACE << "HELO " << tx_mta << '\n';
		cout << SPACE << "250\n";
		cout << SPACE << "MAIL FROM:<" << sender << '@' << tx_mta << ">\n";
		cout << SPACE << "250\n";
		for (vector<string>::iterator vit = receint[*it].begin();
				vit != receint[*it].end(); vit++) {
			cout << SPACE << "RCPT TO:<" << *vit << '@' << *it << ">\n";
			if (receivers.count(*vit + '@' + *it) != 0) {
				cout << SPACE << "250\n";
				ret = 1;
			} else {
				cout << SPACE << "550\n";
			}
		}
		if (ret == 1) {
			cout << SPACE << "DATA\n";
			cout << SPACE << "354\n";
			for (vector<string>::iterator it = mail.begin(); it != mail.end(); it++)
				cout << SPACE << *it << "\n";
			cout << SPACE << ".\n";
			cout << SPACE << "250\n";
			ret = 0;
		}
		cout << SPACE << "QUIT\n";
		cout << SPACE << "221\n";
	}
}

int main(void)
{
	int r = 0;
	get_users();

	while ((r = get_recievers()) > 0) {
		get_data();
		send_data();
	}
	return 0;
}
