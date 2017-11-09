#include<stdio.h>
#include<math.h>

int gdc(int A, int B);
void find(int A, int B, int GDC);
int X = 0, Y = 0;

int main() {
	int A, B;
	int GDC;
	printf("Enter two integer A and B \n");
	scanf("%d %d", &A, &B);
	GDC = gdc(A, B);
	find(A, B, GDC);

	printf("%d %d %d", X, Y, GDC);
}

/*
purpose: Find greatest common divisor
input : two integer
output: greatest common divisor
*/
int gdc(int A, int B) {
	int i;
	int temp;

	for (i = 1; i <= B; i++) {
		if (A%i == 0 && B%i == 0)
			temp = i;
	}
	return temp;
}

/*
purpose: Finds X and Y satisfying AX+BY = GCD
input : integer A , B and greatest common divisor
output: none;
*/
void find(int A, int B, int GDC) {
	int min = 10000;

	for (int i = -GDC*(A / GDC)*(B / GDC); i < GDC*(A/GDC)*(B/GDC); i++) {
		for (int j = -GDC*(A / GDC)*(B / GDC); j < GDC*(A / GDC)*(B / GDC); j++) {
				if (((A*i) + (B*j) == GDC) && (min > i + j)) {
					if (i > j) 						
						continue;
					else {
						min = abs(i) + abs(j);
						X = i;
						Y = j;
					}
				}			
		}
	}
}
