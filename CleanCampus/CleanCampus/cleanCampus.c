#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct point {
	double x;
	double y;
}C;

double angle[100][2];
C stack[100];
int top = 0;

int calculate_angle(C *p, C min, int edge);
struct point find_min(C *p, int edge);
void sort(int edge);
int ccw(C p[], int i);
void push(C p);
C pop();
void calculate_length();

void main() {

	int test_case = 0;
	int node_count = 0;
	int set, first, second, third, start;
	C *p;
	C min;

	scanf("%d", &test_case);
	for (int i = 0; i < test_case; i++) {
		scanf("%d", &node_count);

		p = (C*)malloc((node_count + 1) * sizeof(C));
		p[0].x = 0;   p[0].y = 0;

		for (int j = 1; j <= node_count; j++) {
			scanf("%lf %lf", &p[j].x, &p[j].y);
		}
		min = find_min(p, node_count);
		set = calculate_angle(p, min, node_count);
		sort(set);

		first = angle[0][1]; second = angle[1][1]; third = angle[2][1];
		push(p[first]); push(p[second]); push(p[third]);

		for (int k = 3; k <= node_count; k++) {
			ccw(p, k);
		}
		calculate_length(min);
	}
}

/*
purpose: caculation angle using cosine
input: structure of coordinate for all node, coordinate with the smallest y, the number of node
output: angle table size
*/
int calculate_angle(C *p, C min, int node_count) {

	double dx, dy;
	int set = 1;
	int temp = 0;

	angle[0][0] = 0; angle[0][1] = 0;

	for (int i = 1; i <= node_count; i++) {
		if ((p[i].x == min.x) && (p[i].y == min.y)) {
			temp = i;
		}
		else {
			dx = sqrt(pow((p[i].x - min.x), 2) + pow((p[i].y - min.y), 2));
			dy = abs(p[i].x - min.x);
			if (p[i].x >= min.x) {
				angle[set][0] = (dy / dx);
				angle[set++][1] = i;
			}
			else {
				angle[set][0] = -1 * (dy / dx);
				angle[set++][1] = i;
			}
		}
	}
	angle[set][0] = -2;
	angle[set++][1] = temp;
	return set;
}

/*
purpose: find coordinate with the smallest y
input:structure of coordinate for all node, the number of node
output: coordinate with the smallest y
*/
C find_min(C *p, int edge) {

	C min = p[1];

	for (int i = 2; i <= edge; i++) {
		if ((min.y > p[i].y) || (min.x > p[i].x))
			min = p[i];
	}
	return min;
}

/*
purpose: sort in descending order
intput: angle table size
output: none
*/
void sort(int set) {
	double temp0;
	int temp1;

	for (int i = 1; i < set - 1; i++) {
		for (int j = 1; j < set - 1 - i; j++) {

			if (angle[j][0] < angle[j + 1][0]) {
				temp0 = angle[j][0];
				temp1 = angle[j][1];
				angle[j][0] = angle[j + 1][0];
				angle[j][1] = angle[j + 1][1];
				angle[j + 1][0] = temp0;
				angle[j + 1][1] = temp1;
			}
		}
	}
}

/*purpose: Distinguish whether the connected lines of the three points are clockwise or counterclockwise
input:structure of coordinate for all node
output: res>0 counterclockwise, res<0 clockwise , res=0 in line
*/
int ccw(C p[], int r)
{
	int a_x = stack[top - 2].x;   int a_y = stack[top - 2].y;
	int b_x = stack[top - 1].x;   int b_y = stack[top - 1].y;
	int c = angle[r][1];
	double res;

	res = (a_x*b_y + b_x*p[c].y + p[c].x*a_y) - (a_x*p[c].y + b_x*a_y + p[c].x*b_y);

	if (res > 0)
		push(p[c]);
	else if (res < 0) 
		pop();
	else if (res == 0)
		push(p[c]);

}

/*purpose: push in stack
input: stacked structure of coordinate
output:none
*/
void push(C p) {
	stack[top++] = p;
}

/*purpose:pop from stack
input:none
output: top stack
*/
C pop() {
	return stack[top--];
}

/*purpose: calculation length
input:none
output:none
*/
void calculate_length()
{
	double result = 0;
	
	for (int i = 0; i < top; i++) {
			result = result + sqrt(pow(stack[i + 1].x - stack[i].x, 2) + pow(stack[i + 1].y - stack[i].y, 2));
	}
	printf("\n%.2lf\n", result + 2);
}
