
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node {
	int x;
	int y;
}point;
point p[100][100];

int count = 0, n, k;
int isPossible(point v, point con[], int num);
int	findSolution(point con[], point v, int num);
void backtrace(point con[], int num);

void main() {
	int i, j;
	point con[100];

	while (1) {

		scanf("%d %d", &n, &k);
		if (n == 0 && k == 0)
			break;
		else {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					p[i][j].x = i;
					p[i][j].y = j;
				}
			}

			backtrace(con, 0);
			printf("%d\n\n", count);
			count = 0;
		}
	}
}

/*purpose:Make sure that the selected coordinates are in the selected coordinate array
input: selected coordinates, coordinates to select, board size
output: if correct return 1 or 0 
*/
int findSolution(point con[], point v, int num) {
	int i;

	if (num == 0)
		return 0;

	for (i = 0; i < num; i++)
	{
		if (con[i].x == v.x && con[i].y == v.y)
			return 1;
	}

	return 0;

}

/*purpose: make sure you are on the same line
input: coordinate to select,selected coordinates,board size
output:if same line return 0 
*/
int isPossible(point v, point con[], int num) {
	int i;
	if (num == 0)
		return 1;
	for (i = 0; i < num; i++) {

		if (abs(con[i].x - v.x) == abs(con[i].y - v.y))
			return 0;
	}
	return 1;
}

/*purpose: search by back tracking method, Depth search
input:selected coordinates, board size
output:none
*/
void backtrace(point con[], int num) {
	int i, j;
	if (num == k)
	{
		count++;
		return;
	}

	if (num != 0) {
		i = con[num - 1].x;
		j = con[num - 1].y;

	}
	else
	{
		i = 0;
		j = 0;
	}

	for (i; i < n; i++) {
		for (j; j < n; j++) {
			if (findSolution(con, p[i][j], num))
				continue;

			if (num == 0 || isPossible(p[i][j], con, num)) {
				con[num] = p[i][j];
				backtrace(con, num + 1);
			}
		}
		j = 0;
	}
}