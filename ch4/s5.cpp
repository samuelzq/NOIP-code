// UVa512
// By LaoZhang
// Date 2020-08-12

#include <iostream>
#include <string>

using namespace std;

const int N = 10000;

enum ops {
	EX = 0,
	DC,
	DR,
	IC,
	IR,
	INVALID_OP,
	OPS_COUNT = INVALID_OP
};

struct ex_param {
	int r1, c1, r2, c2;
};

struct ins_del_param {
	int count;
	int xy[20];
};

struct Command {
	enum ops ops = INVALID_OP;
	union {
		struct ex_param ex;
		struct ins_del_param ins_del;
	} params;
} cmd[N];


// for exchange
int ops(int &r, int &c, struct ex_param &ex)
{
	if (ex.r1 == r && ex.c1 == c) {
		r = ex.r2;
		c = ex.c2;
	} else if (ex.r2 == r && ex.c2 == c) {
		r = ex.r1;
		c = ex.c1;
	}
	return 0;
}

// for insertion
int ops(int &rc, struct ins_del_param params)
{
	int inc = 0;
	for (int i = 0; i < params.count; i++) {
		if (params.xy[i] > rc)
			continue;
		inc++;
	}
	rc += inc;
	return 0;
}

// for deletion
int ops(struct ins_del_param params, int &rc)
{
	int dec = 0;

	for (int i = 0; i < params.count; i++) {
		if (params.xy[i] > rc)
			continue;
		else if (params.xy[i] == rc)
			return -1;
		dec++;
	}
	rc -= dec;
	return 0;
}

int run(int &r, int &c, int n)
{
	for (int i = 0; i < n; i++) {
		switch (cmd[i].ops) {
			case EX:
				ops(r, c, cmd[i].params.ex);
				break;
			case DC:
				if (-1 == ops(cmd[i].params.ins_del, c))
					return 0;
				break;
			case DR:
				if (-1 == ops(cmd[i].params.ins_del, r))
					return 0;
				break;
			case IC:
				ops(c, cmd[i].params.ins_del);
				break;
			case IR:
				ops(r, cmd[i].params.ins_del);
				break;
			default:
				break;
		}
	}
	return 1;
}

int main()
{
	int r0, c0, q, n, r, c, kase = 0;

	while (cin >> r >> c && r) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			string cc;
			cin >> cc;
			if (cc == "EX") {
				struct ex_param *p = &cmd[i].params.ex;
				cin >> p->r1 >> p->c1 >> p->r2 >> p->c2;
				cmd[i].ops = EX;
			} else {
				struct ins_del_param *p = &cmd[i].params.ins_del;
				if (cc == "DC")
					cmd[i].ops = DC;
				else if (cc == "DR")
					cmd[i].ops = DR;
				else if (cc == "IR")
					cmd[i].ops = IR;
				else if (cc == "IC")
					cmd[i].ops = IC;
				cin >> p->count;
				for (int j = 0; j < p->count; j++)
					cin >> p->xy[j];
			}
		}

		if (kase > 0)
			cout << "\n";
		cout << "Spreadsheet #" << ++kase << '\n';

		cin >> q;
		while (q--) {
			cin >> r0 >> c0;
			cout << "Cell data in (" << r0 << ',' << c0 << ") ";

			if (!run(r0, c0, n))
				cout << "GONE\n";
			else
				cout << "moved to (" << r0 << ',' << c0 << ")\n";
		}
	}

	return 0;
}
