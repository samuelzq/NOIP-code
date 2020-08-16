// UVa12412
// By LaoZhang
// Date 2020-08-14

// Passed be the debug data but "Awnser error" when submitted

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

const int N = 125;
using namespace std;

#define ULL    unsigned long long

struct student {
	unsigned long long sid = 0;
	unsigned short rk = 0, cid = 0;
	unsigned short cn, math, en, prg, total;
	float avg;
	char name[11];

	student() {
		cn = math = en = prg = total;
		avg = 0.0;
		memset(name, 0, sizeof(name));
	};
} rec[N];

int count = 0;

void usage(void)
{
	cout << "Welcome to Student Performance Management System (SPMS).\n\n";
	cout << "1 - Add\n";
	cout << "2 - Remove\n";
	cout << "3 - Query\n";
	cout << "4 - Show ranking\n";
	cout << "5 - Show Statistics\n";
	cout << "0 - Exit\n";
	cout << '\n';
}

void add(void)
{
	int c = 0;

	while (1) {
		unsigned long long sid;
		unsigned short cid, cn, math, en, prg, i, l, b;
		string name;
		struct student *st = NULL;
		cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish.\n";
		cin >> sid;
		if (sid == 0)
			break;

		for (i = 0; i < count; i++) {
			if (rec[i].sid == sid) {
				break;
			}
		}
		cin >> cid >> name >> cn >> math >> en >> prg;

		if (i < count) {
			cout << "Duplicated SID.\n";
			continue;
		}

		st = &rec[i];
		st->sid = sid;
		st->cid = cid;
		st->cn = cn;
		st->math = math;
		st->en = en;
		st->prg = prg;
		st->total = cn + math + en + prg;
		st->avg = st->total / 4.0;
		name.copy(st->name, name.length());
		st->name[name.length()] = 0;
		l = b = 1;
		for (int i = 0; i < count; i++) {
			if (rec[i].total > st->total)
				b++;
			else if (rec[i].total < st->total) {
				rec[i].rk++;
				l++;
			}
		}
		st->rk = b;
		// hash record
		count++;
	}
}

void clear(int i)
{
	struct student *st = NULL;
	int n = count - i - 1;

	st = &rec[i];
	for (i = 0; i < count; i++) {
		if (rec[i].rk > st->rk)
			rec[i].rk--;
	}
	count--;
	memcpy(st, st + 1, n * sizeof(struct student));
}

void remove(void)
{
	int c = 0;

	while (1) {
		unsigned long long sid = 0;
		unsigned int n, i = 0;
		string name;

		cout << "Please enter SID or name. Enter 0 to finish.\n";
		cin >> name;
		if (name.length() == 1 && name[0] == '0')
			break;

		n = 0;
		if (name == "AA")
			i = n;
		if (name[0] >= 'A') {
			// query by name
			for (i = 0; i < count; ) {
				if (!name.compare(rec[i].name)) {
					clear(i);
					n++;
				} else {
					i++;
				}
			}
		} else {
			// query by sid
			sid = stoull(name);
			for (i = 0; i < count; i++) {
				if (sid == rec[i].sid) {
					clear(i);
					n++;
					break;
				}
			}
		}
		cout << n << " student(s) removed.\n";
	};
}

void outrec(int i)
{
	cout << rec[i].rk << ' ' << setw(10) << setfill('0') << rec[i].sid;
	cout << ' ' << rec[i].cid << ' ' << rec[i].name << ' ' << rec[i].cn << ' ' << rec[i].math;
	cout << ' ' << rec[i].en << ' ' << rec[i].prg << ' ' << rec[i].total << ' ' << fixed << setprecision(2) << rec[i].avg << '\n';
}

void query(void)
{
	int c = 0;

	while (1) {
		string name;
		unsigned long long sid = 0;
		unsigned int i = 0;
		struct student *st = NULL;

		cout << "Please enter SID or name. Enter 0 to finish.\n";
		cin >> name;

		if (name.length() == 1 && name[0] == '0')
			break;

		if (name[0] >= 'A') {
			// query by name
			for (int i = 0; i < count; i++) {
				if (!name.compare(rec[i].name)) {
					outrec(i);
				}
			}
		} else {
			// query by sid
			sid = stoull(name);
			for (int i = 0; i < count; i++) {
				if (sid == rec[i].sid) {
					outrec(i);
					break;
				}
			}
		}
	}
}

void ranklist(void)
{
	cout << "Showing the ranklist hurts students' self-esteem. Don't do that.\n";
}

void show_stats(void)
{
	float avg = 0, amath = 0, aen = 0, acn = 0, aprg = 0;     // average score
	short math = 0, cn = 0, en = 0, prg = 0; // passed number
	int i, n = 0, cid = 0;
	short p[5] = {0, 0, 0, 0, 0};
	cout << "Please enter class ID, 0 for the whole statistics.\n";

	cin >> cid;

	int pass_count = 0;
	for (i = 0; i < count; i++) {
		pass_count = 0;
		if (cid == 0 || cid == rec[i].cid) {
			n++;
			amath += rec[i].math;
			acn += rec[i].cn;
			aen += rec[i].en;
			aprg += rec[i].prg;
			if (rec[i].math >= 60) {
				pass_count++;
				math++;
				p[pass_count]++;
			}
			if (rec[i].en >= 60) {
				pass_count++;
				en++;
				p[pass_count]++;
			}
			if (rec[i].cn >= 60) {
				pass_count++;
				cn++;
				p[pass_count]++;
			}
			if (rec[i].prg >= 60) {
				pass_count++;
				prg++;
				p[pass_count]++;
			}
			if (pass_count == 0)
				p[pass_count]++;
		}
	}
	amath = amath / (float)n;
	acn = acn / (float)n;
	aen = aen / (float)n;
	aprg = aprg / (float)n;
	cout << "Chinese\n";
	cout << "Average Score: " << fixed << setprecision(2) << acn << '\n';
	cout << "Number of passed students: " << cn << '\n';
	cout << "Number of failed students: " << n - cn << "\n\n";
	cout << "Mathematics\n";
	cout << "Average Score: " << fixed << setprecision(2) << amath << '\n';
	cout << "Number of passed students: " << math << '\n';
	cout << "Number of failed students: " << n - math << "\n\n";
	cout << "English\n";
	cout << "Average Score: " << fixed << setprecision(2) << aen << '\n';
	cout << "Number of passed students: " << en << '\n';
	cout << "Number of failed students: " << n - en << "\n\n";
	cout << "Programming\n";
	cout << "Average Score: " << fixed << setprecision(2) << aprg << '\n';
	cout << "Number of passed students: " << prg << '\n';
	cout << "Number of failed students: " << n - prg << "\n\n";
	cout << "Overall:\n";
	cout << "Number of students who passed all subjects: " << p[4] << '\n';
	cout << "Number of students who passed 3 or more subjects: " << p[3] << '\n';
	cout << "Number of students who passed 2 or more subjects: " << p[2] << '\n';
	cout << "Number of students who passed 1 or more subjects: " << p[1] << '\n';
	cout << "Number of students who failed all subjects: " << p[0] << '\n';
	cout << '\n';
}

int main(void)
{
	int choice;

	while (1) {
		usage();
		cin >> choice;

		switch (choice) {
			case 1:
				add();
				break;
			case 2:
				remove();
				break;
			case 3:
				query();
				break;
			case 4:
				ranklist();
				break;
			case 5:
				show_stats();
				break;
			case 0:
				cout << '\n';
				return 0;
			default:
				break;
		}
	}
}
