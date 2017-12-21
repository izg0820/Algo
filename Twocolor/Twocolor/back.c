#include<stdio.h>
#include<stdlib.h>

int vertex[30][30] = { 0, };
int a, b;
int numOfEdge;
int two_coloring();

void main() {

	scanf("%d", &numOfEdge);

	for (int i = 0; i < numOfEdge; i++) {
		scanf("%d %d", &a, &b);
		vertex[a][b] = 1;
	}

	if (two_coloring() == 1)
		printf("two-color graph\n");
	else
		printf("not two-color graph\n");
}

/*
purpose: check two color or not two color
input: none 
output: if two color return 1 not two color return 0 
*/
int two_coloring() {

	int color[30];

	for (int i = 0; i < numOfEdge; i++) {
		color[i] = -1;
	}
	color[0] = 1;


	for (int i = 0; i < numOfEdge; i++) {
		for (int j = 0; j < numOfEdge; j++) {
			if (vertex[i][j] == 1 && color[j] == -1)
				color[j] = 1 - color[i];

			else if (vertex[i][j] == 1 && color[j] != -1)
				return 0;
		}

	}
	return 1;
}
