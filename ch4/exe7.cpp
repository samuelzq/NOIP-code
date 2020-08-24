// UVa 509 - RAID! 
// By LaoZhang
// Date 2020-08-22
// Passed by all online test input. But cannot AC

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <termios.h>
#include <unistd.h>

using namespace std;

char disc[6][6500];
int parity[6500];
int xcnt[6500];
char block[400];
char buf[100];
char pack[] = "0000";
int even_parity = 0;

struct termios settings;
int clear_icanon(void)
{
	struct termios new_settings;
	int result;
	result = tcgetattr (STDIN_FILENO, &settings);
	if (result < 0) {
		perror ("error in tcgetattr");
		return 0;
	}

	new_settings = settings;
	new_settings.c_lflag &= ~ICANON;
	result = tcsetattr (STDIN_FILENO, TCSANOW, &new_settings);
	if (result < 0) {
		perror ("error in tcsetattr");
		return 0;
	}
	return 1;
}

int recover_icanon(void)
{
	int result;
	result = tcsetattr (STDIN_FILENO, TCSANOW, &settings);
	if (result < 0) {
		perror ("error in tcsetattr");
		return 0;
	}
	return 1;
}

char *get_data(int d, int s, int b)
{

	int idx = b * s;
	char *disk = disc[d];

	for (int i = 0; i < s; i++) {
		if (disk[idx + i] == 'x') {
			if (parity[idx + i] % 2 == 0)
				buf[i] = even_parity + '0';
			else
				buf[i] = 1 - even_parity + '0';
		} else {
			buf[i] = disk[idx + i];
		}
	}
	return buf;
}

void out(char *b, int len)
{
	int x = 0;

	for (int i = 0; i < len; i += 4) {
		x = 0;
		for (int j = 0; j < 4; j++) {
			x = (x << 1) + (b[i + j] - '0');
		}
		//cout << setiosflags(ios::uppercase) << hex << x;
		printf("%X", x);
	}
}
int main(void)
{
	int d, s, b, kase = 0;
	char e;

	clear_icanon();
	while (cin >> d && d != 0) {
		kase++;
		cin >> s >> b;
		int i, len = s * b;
		cin >> e;
		if (e == 'E')
			even_parity = 0;
		else
			even_parity = 1;

		cin >> disc[0];
		for (int j = 0; j < len; j++) {
			xcnt[j] = 0;
			parity[j] = 0;
			if (disc[0][j] == 'x')
				xcnt[j] = 1;
			if (disc[0][j] == '1')
				parity[j] = 1;
		}
		for (i = 1; i < d; i++) {
			cin >> disc[i];
			for (int j = 0; j < len; j++) {
				if (disc[i][j] == 'x')
					xcnt[j] += 1;
				if (disc[i][j] == '1')
					parity[j] += 1;
			}
		}

		for (i = 0; i < len; i++) {
			if (parity[i] % 2 != even_parity && xcnt[i] != 1)
				break;
		}

		if (i < len) {
			// cannot recovery
			cout << "Disk set " << kase << " is invalid.\n";
		} else {
			int len;
			char *bb = NULL;
			cout << "Disk set 1 is valid, contents are: ";
			for (i = 0; i < b; i++) {
				block[0] = 0;
				for (int j = 0; j < d; j++) {
					if (i % d == j)  // skip parity block
						continue;
					// get data block from disk j
					bb = get_data(j, s, i);
					strcat(block, bb);
				}
				len = s * (d - 1) % 4;
				if (len) {
					len = 4 - len;
					strncat(block, pack, len);
				}
				out(block, s * (d - 1) + len);
			}
		}
		cout << '\n';
	}
	recover_icanon();
	return 0;
}
