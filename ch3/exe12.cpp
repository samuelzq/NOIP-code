// UVa11809
// By LaoZhang
// Date 2020-08-06

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
	double A[10][31];
	double a,c;
	double x;
	long long B[10][31];
	long long b,d;
	int i,j;

	for(i = 0; i < 10; i++)
		for(j = 1; j < 31; j++){//打表
			a = 1 - pow(2, -i - 1);
			b = pow(2, j) - 1;
			x = log10(a) + b * log10(2);
			d = floor(x);
			c = pow(10, x - d);
			A[i][j] = c;
			B[i][j] = d;
		}

	char s[30];
	double p;
	int q;

	while (cin >> s){
		if(s[0] == '0' && s[1] == 'e' && s[2] == '0')
			return 0;
		s[17]=' ';//将e变为空格
		sscanf(s, "%lf %d", &p, &q);//从s读入p，q
		for (i = 0; i < 10; i++)
			for (j = 1; j < 31; j++)
				if(fabs(A[i][j] - p) < 1e-5 && B[i][j] == q)//匹配输出
					cout << i << ' ' << j << endl;
	}
	return 0;
}
