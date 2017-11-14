#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct arr {
	double x;
	double y;
}dot[30];
int parent[30];//checkinf cycle
double table[30][30];//for saving the length

void main()                           
{
	int find(int);
	int uni(int, int);
	int node_count, i, j, count = 0, x, xindex, y, yindex;
	double total = 0, min, temp;
	printf("Input the number of dots\n");
	scanf("%d", &node_count);

	printf("Input the X point and Y point\n");
	for (i = 0; i<node_count; i++)
		scanf("%lf %lf", &dot[i].x, &dot[i].y);
	
	//calculation length of dots
	for (i = 0; i < node_count; i++) {
		for (j = 0; j < node_count; j++)
			table[i][j] = sqrt(((dot[i].x - dot[j].x)*(dot[i].x - dot[j].x)) + ((dot[i].y - dot[j].y)*(dot[i].y - dot[j].y)));
	}
	
	for (i = 0; i<node_count; i++)
		parent[i] = -1;

	while (count != node_count- 1)
	{
		min = 1000;
		for (i = 0; i<node_count; i++)
		{
			for (j = i; j<node_count; j++)
			{
				if (table[i][j] < min && table[i][j] != 0)
				{
					min = table[i][j];
					x = xindex = i;
					y = yindex = j;
				}
			}
		}
		x = find(x);
		y = find(y);
		if (uni(x, y) == 1)
		{
			total = total + table[xindex][yindex];
			count++;
		}
		table[xindex][yindex] = 1000;
	}
	printf("min cost : %.2lf\n", total);
}
/*
*purpose: check that index make cycle 
*input: index
*output: not make cycle return num make cycle return -1
*/

int find(int num)
{
	while (parent[num] != -1)
		num = parent[num];
	return num;
}
/*
*purspose: index of length is uni set or isn't uni set
*input: index of length
*output: uni set return 1 or return 0
*/

int uni(int x, int y)
{
	if (x != y)
	{
		parent[y] = x;
		return 1;
	}
	return 0;
}
