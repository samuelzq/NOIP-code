// UVa213
// By LaoZhang
// Date 2020-08-08

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

char hd_buf[8][1 << 8];

void process_header(string &header)
{
	int t = 0, n = header.length();

	for (int i = 1; i <= 8; i++) {
		for (int j = 0; j < pow(2, i) - 1  && t < n; j++) {
			hd_buf[i - 1][j] = header[t];
			t++;
		}
	}
}

int get_indx(string &str, int s, int len)
{
	int l = 1;
	int idx = 0;

	for (int i = 0; i < len; i++) {
		int d = str[s + i] - '0';
		l &= d;
		idx = (idx << 1) + d;
	}

	if (l)
		return -1;
	else
		return idx;
}

int main(void)
{
	int n;
	string header;

	while (getline(cin, header)) {
		char tail_key[8];
		string nkey;
		bool refresh_width = true;
		int key_width = -1;
		int idx = 0;
		n = header.length();
		process_header(header);

		tail_key[0] = 0;
		while (getline(cin, nkey)) {
			string key = tail_key;
			key += nkey;
			int key_len = key.length();

			idx = 0;
			if (refresh_width == true) { // need to refresh key width
				if (key_len < 3) {
					tail_key[key.copy(tail_key, key_len - idx, idx)] = 0;
					continue;
				}

				key_width = get_indx(key, idx, 3);
				idx += 3;
				refresh_width = false;
				if (key_width == 0)
					break; // end of key
				if (key_width == -1)
					key_width = 7;
			} else {
				if (key_len < key_width) { // get anothe line of key
					tail_key[key.copy(tail_key, key_len - idx, idx)] = 0;
					continue;
				}
			}

			while (idx + key_width <= key_len) {
				int h_id = 0;
				h_id = get_indx(key, idx, key_width);
				idx += key_width;
				if (h_id == -1) {
					if (key_len - idx > 2) {
						refresh_width = false;
						key_width = get_indx(key, idx, 3);
						if (key_width == 0)
							goto next_header;
						if (key_width == -1)
							key_width = 7;
	
						idx += 3;
						continue;
					} else {
						refresh_width = true;
						break;
					}
				}
				cout << hd_buf[key_width - 1][h_id];
			}
			tail_key[key.copy(tail_key, key_len - idx, idx)] = 0;
		}
next_header:
		cout << '\n';
	}
	return 0;
}
