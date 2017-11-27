#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100000

typedef struct Node {
	int x;
	int y;
}coordinate;

float closest_pair(coordinate* c, int l, int r);
float brute_force(coordinate c[], int l, int r);
float dis(coordinate a, coordinate b);
coordinate* sortX(coordinate* c,int n);
coordinate* sortY(coordinate* c,int n);

void main() {
	int set = 0;
	coordinate *c;
	coordinate *temp;

	while (1) {
		
		printf("If you want finish, type 0\n");
		scanf("%d", &set);
		if (set == 0)
			break;
		else {
			temp = (coordinate*)malloc((set + 1) * sizeof(coordinate));

			for (int i = 0; i < set; i++) {
				scanf("%d %d", &temp[i].x, &temp[i].y);
			}

			c = sortX(temp, set);
			printf("Answer : %.2f\n\n", closest_pair(c, 0, set - 1));
			free(c);
		}
	}
}

/*
purpose:Find closest pair using divide and conquer method
input: coordinate structre array, count of left side, count of right side
output: at least distance
*/
float closest_pair(coordinate* c, int l, int r)
{
	int q = 0;
	float dl = 0, dr = 0;
	float d = 0;
	int n = 0;
	coordinate s[100];
	coordinate *sprime;

	if (r - l < 3) {
		return brute_force(c, l, r);
	}
	
		if ((l + r) % 2 == 0) {
			q = (l+ r) / 2;
		}
		else
			q = (l + r) / 2 + 1;
		
		dl = closest_pair(c, l, q - 1);
		dr = closest_pair(c, q, r);
		
		if (dl > dr)
			d = dr;
		else
			d = dl;

		for (int i = 0; i < r; i++) {
			if (c[q].x - d <= c[i].x && c[i].x <= c[q].x + d) {
				s[n++] = c[i];
			}
		}

		sprime = sortY(s, n);

		if (d > brute_force(sprime, 0, n - 1))
			d = brute_force(sprime, 0, n - 1);

		return d;
}
/*
purpose: Find the shortest of the dots on the left and the dots on the right 
input: coordinate structure array, count of left side, count of right side
output: at least distance
*/
float brute_force(coordinate c[], int l, int r)
{
	float min = MAX;
	float res = 0;

	for (int i = l; i < r; i++) {
		for (int j = i; j <= r; j++) {
			res = dis(c[i], c[j + 1]);
			if (min > res&&res != 0)
				min = res;
		}
	}
	return min;
}

/*
purpose: compute distance two points
input: two coordinates information
output: distance of two points
*/
float dis(coordinate a, coordinate  b)
{
	return  sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/*
purpose: sort by X coordinates
input:unsortes structure array, structure size
output: sorted structure array
*/
coordinate* sortX(coordinate * c,int n)
{
	coordinate temp;
	for (int i = 0; i < n; i++) {
		if (c[i].x > c[i + 1].x)
		{
			temp = c[i];
			c[i] = c[i + 1];
			c[i + 1] = temp;
		}
	}
	return c;
}

/*
purpose: sort by Y coordinates
input:unsortes structure array, structure size 
output: sorted structure array
*/coordinate* sortY(coordinate * c,int n)
{
	coordinate temp;
	for (int i = 0; i < n; i++)
	{
		if (c[i].y > c[i + 1].y)
		{
			temp = c[i];
			c[i] = c[i + 1];
			c[i + 1] = temp;
		}
	}
	return c;
}