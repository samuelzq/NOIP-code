// UVa1590
// By LaoZhang
// Date 2020-08-20

#include <cstdio>

int ip1;
int ip2;
const int mask = 0xFFFFFFFF;
int ip[4];

#define IP_ADDR(byte0, byte1, byte2, byte3)   (((byte0) & 0xff) << 24 | ((byte1) & 0xff) << 16 | ((byte2) & 0xff) << 8 | (byte3) & 0xff)
int cmp_bit(unsigned int c1, unsigned int c2)
{
	unsigned int t = c1 ^ c2;

	if (!t)
		return 0;
	int i = 0;
	do {
		i++;
		t = t >> 1;
	} while(t >= 1);
	return i;
}


void output(int ip)
{
	printf("%d.%d.%d.%d\n", (ip >> 24) & 0xff, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff);
}

int main(void)
{
	int n, d, l;
	unsigned long t = 0;

	while (scanf("%d", &n) != EOF) {
	scanf("%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
	ip1 = IP_ADDR(ip[0], ip[1], ip[2], ip[3]);
	l = 0;
	while (--n) {
		int b = 0;
		scanf("%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
		ip2 = IP_ADDR(ip[0], ip[1], ip[2], ip[3]);
		b = cmp_bit(ip1, ip2);
		l = (l > b) ? l : b;
	}

	t = ip1;
	t = (t >> l) << l;
	output(t);

	t = mask;
	t = (t >> l) << l;
	output(t);

	}
	return 0;
}
