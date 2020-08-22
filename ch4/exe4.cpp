// UVa253
// By LaoZhang
// Date 2020-08-20

#include <cstring>
#include <cstdio>

char cubes[13];

// cube could be rotated in left hand direction.
// After each rotation, faces' color number would
// be reorgonized.
// Here we use 3 pointer groups for faces rotated
// in the same direction.
char *x[4];
char *y[4];
char *z[4];

bool compare_cubes(void)
{
	for (int i = 0; i < 6; i++) {
		if (cubes[i] != cubes[i + 6])
			return false;
	}
	return true;
}

void rotate(char c)
{
	char t;
	char **cp;
	if (c == 'x')
		cp = x;
	else if (c == 'y')
		cp = y;
	else
		cp = z;

	t = *cp[0];
	for (int i = 0; i < 3; i++)
		*cp[i] = *cp[i + 1];
	*cp[3] = t;
}

int main(void)
{
	while (scanf("%s", cubes) != EOF) {
		int i, j, k;
		// inite pointer groups
		// For x-axis, faces #1, #2, #6, #5
		x[0] = cubes + 1;
		x[1] = cubes + 5;
		x[2] = cubes + 4;
		x[3] = cubes;
		// for y-axis, faces #1, #4, #6, #3
		y[0] = cubes + 3;
		y[1] = cubes + 5;
		y[2] = cubes + 2;
		y[3] = cubes;
		// for z-axis, faces #2, #4, #5, #3
		z[0] = cubes + 3;
		z[1] = cubes + 4;
		z[2] = cubes + 2;
		z[3] = cubes + 1;

		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 4; k++) {
					if (compare_cubes() == true)
						goto out;
					// rotate in x-axis
					rotate('x');
				}
				rotate('y');
			}
			rotate('z');
		}
out:
		if (k == 4 && i == 4 && j == 4)
			printf("FALSE\n");
		else
			printf("TRUE\n");
	}
	return 0;
}
