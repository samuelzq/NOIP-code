// UVa508 - Morse Mismatches
// By LaoZhang
// Date 2020-08-22

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <algorithm>

// buffer for morse code
#define W           11
char morse[36][W];

#define  N          21
char ctext[N * W];
struct context {
	char text[N];
	char code[W * N]; // no more than 10x6
	int len;          // text length
	int mlen;         // length of the context's morse code
	int match;        // length of the matchedd length with a key

	// context should be sorted once there is no match
	bool operator < (const context a)const
	{
		return strcmp(text,a.text) < 0;      // Looks a requierment was missed in the question discription
	}
};

struct context ct[101];
int p_match[N];
int a_match[N];

void cmp_code(char *code, int len, int cnt)
{
	int pidx = 0, aidx = 0;  // index for the last perfect match
	for (int i = 0; i < cnt; i++) {
		int j, l = ct[i].mlen;
		if (!strcmp(code, ct[i].code))
			// perfect match
			p_match[pidx++] = i;

		if (pidx > 1)
			break;
	}
	if (pidx) {
		// match found
		printf("%s", ct[p_match[0]].text);
		if (pidx > 1)
			printf("!\n");
		else
			printf("\n");
	} else {
		std::sort(ct, ct + cnt);   // cannot pass without this sort
		// errors in transmission
		int minl = 2000, ii = -1;
		for (int i = 0; i < cnt; i++) {
			int l = ct[i].mlen;
			if (len > l && strstr(code, ct[i].code) == code) {
				if (len - l < minl) {
					minl = len - l;
					ii = i;
				}
			} else if (len < l && strstr(ct[i].code, code) == ct[i].code) {
				if (l - len < minl) {
					minl = l - len;
					ii = i;
				}
			}
		}
		if (ii == -1)
			printf("%s\?\n", ct[0].text);
		else
			printf("%s\?\n", ct[ii].text);
	}
}

int main(void)
{
	char c;
	int i;
	
	// get Morse code for each characters
	while (scanf("%c", &c)) {
		if (isspace(c))
			continue;
		if (c == '*')
			break;
		if (c >= 'A' && c <= 'Z')
			scanf("%s", morse[c - 'A']);
		if (c >= '0' && c <= '9')
			scanf("%s", morse[c - '0'  + 26]);
	}

	// get context
	i = 0;
	while (scanf("%s", ctext) && ctext[0] != '*') {
		if (isspace(ctext[0]))
			continue;
		int mlen = 0, clen = 0;
		ct[i].len = strlen(ctext);
		ct[i].mlen = 0;
		strncpy(ct[i].text, ctext, ct[i].len);
		for (int j = 0; j < ct[i].len; j++) {
			int idx;
			c = ctext[j];
			if (c >= 'A' && c <= 'Z')
				idx = c - 'A';
			if (c >= '0' && c <= '9')
				idx = c - '0'  + 26;
			mlen = strlen(morse[idx]);
			memcpy(ct[i].code + ct[i].mlen, &morse[idx], mlen);
			ct[i].mlen += mlen;
		}
		i++;
		memset(ctext, 0, sizeof(ctext));
	}

	while (scanf("%s", ctext) && ctext[0] != '*') {
		if (isspace(ctext[0]))
			continue;
		// compare codes with each context
		cmp_code(ctext, strlen(ctext), i);
		memset(ctext, 0, sizeof(ctext));
	}
	printf("\n");
	return 0;
}
