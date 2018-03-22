#include <stdio.h>
#define MAX 50

void find_friend(int friend[MAX][2], int person, int time,int relationship);
void comb(int n, int r, int q);
void process(int q);

int T[MAX];
int empty_set[MAX];
int possible_set[MAX][2];
int count = 0;
int result = 0;

int main() {
	int case_count;
	int person;
	int relationship;
	int friend[MAX][2];
	int time;

	scanf("%d", &case_count);
	for (int i = 0; i < case_count; i++) {
		scanf("%d %d", &person, &relationship);

		for (int j = 0; j < relationship; j++) {
			scanf("%d %d", &friend[j][0], &friend[j][1]);
		}
		for (time = 0; time < relationship; time++) {
			find_friend(friend, person, time, relationship);
		}
		printf("%d ", result);
	}
}

void find_friend(int friend[MAX][2], int person, int time, int relationship) {

	int person_set[MAX];
	int j = 0;

	for (int i = 0; i < MAX; i++) {
		person_set[i] = -1;
	}

	for (int i = 0; i < person; i++) {
		person_set[i] = i;
	}

	for (int i = 0; i < person; i++) {
		if (i == friend[time][0] || i == friend[time][1])
			continue;
		else
			empty_set[j++] = i;
	}
	comb(j, 2, 2);
	for (int i = 0; i < (person*(person - 1)) / 2; i++) {
		for (int j = 0; j < relationship; j++) {
			if ((possible_set[i][0] == friend[j][0]) && (possible_set[i][1] == friend[j][1]))
				result++;
		}
	}
}

void comb(int n, int r, int q) {
	if (r == 0) {
		process(q);
		return;
	}
	else if (n < r) {
		return;
	}
	else {
		T[r - 1] = empty_set[n - 1];
		comb(n - 1, r - 1, q);
		comb(n - 1, r, q);
	}
}

void process(int q) {
	for (int i = q - 1; i >= 0; i = i - 2) {
		possible_set[count][1] = T[i];
		possible_set[count++][0] = T[i - 1];
	}
}