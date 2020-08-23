// UVa 12108 - Extraordinarily Tired Students 
// By LaoZhang
// Date 2020-08-23

#include <iostream>

using namespace std;

struct student {
	int a = 0;
	int s = 0;
	int t = 0;  // initial state
	int c = 0;  // current state. When all students come to the initial state, they could never be all awaken.
} st[10];

int main(void)
{
	int n;
	int kase = 1;

	while (cin >> n && n != 0) {
		int ans = 0;
		int cp = n / 2 + 1;
		int sleep = 0;      // additional sleep count in next cycle
		int awake = 0;      // additional awaken count in next cycle
		bool cycle = false;
		for (int i = 0; i < n; i++) {
			cin >> st[i].a >> st[i].s >> st[i].t;
			if (st[i].t > st[i].a) {
				int t = st[i].s - st[i].t;
				sleep++;
			}
			st[i].c = st[i].t;
		}
		awake = n - sleep;

		while (sleep && cycle == false) {
			int ds = 0, da = 0;
			ans++;
			for (int i = 0; i < n; i++) {
				if (st[i].c == st[i].s + st[i].a) {
					st[i].c = 1;
					da++;
				} else if (st[i].c == st[i].a) {
					if (sleep > awake) {
						st[i].c++;
						ds++;
					} else {
						st[i].c = 1;
					}
				} else {
					st[i].c++;
				}
			}
			sleep = sleep + ds - da;
			awake = awake + da - ds;

			// check whether the init state come again
			cycle = true;
			for (int i = 0; i < n; i++) {
				if (st[i].c != st[i].t) {
					cycle = false;
					break;
				}
			}
		}

		cout << "Case " << kase++;
		if (sleep > awake)
			cout << ": " << -1 << '\n';
		else
		cout << ": " << ans + 1 << '\n';
	}
	return 0;
}
