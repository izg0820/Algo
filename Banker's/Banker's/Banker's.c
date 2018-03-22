#include <stdio.h>
#include <stdlib.h>

struct PCB {
	int pid;
	int allocation[100];
	int max[100];
	int need[100];
	struct PCB *next;
	struct PCB *prev;
};
struct NODE {
	int pid;
	int req_resource[100];
};

struct PCB *head = NULL;
struct PCB *tail = NULL;
struct NODE request;

int available[10];

void enqueue(int *temp, int rN);
void dequeue(int temp_pid);
void cycle(struct NODE req, int pN, int rN);
int cnt = 0;

int main(int argc, char *argv[]) {

	FILE *input, *output;
	int resourceNumber = atoi(argv[3]);
	int processNumber = atoi(argv[4]);
	int temp[1000];
	int i, k = 0, total = 0;
	int n = 0;

	input = fopen(argv[1], "r");
	output = fopen(argv[2], "wt");

	/*file open and input data to temp array*/
	while (fscanf(input, "%d", &temp[total]) != EOF) {
		total++;
	}

	/*input data to available */
	for (i = 0; i < resourceNumber; i++) {
		available[i] = temp[cnt];
		cnt++;
	}
	/*input data to PCB using queue-linked list*/
	while (n < processNumber) {
		enqueue(temp, resourceNumber);
		n++;
	}

	/*input data to request structure*/
	request.pid = temp[cnt];
	cnt++;
	for (i = cnt; i < resourceNumber; i++) {
		request.req_resource[k] = temp[i];
		k++;
	}

	/*struct PCB *current = NULL;
	current = head;
	for (int i = 0; i < resourceNumber; i++) {
		printf("%d ", available[i]);
	}
	printf("\n");

	while (current != NULL) {
		printf("%d ", current->pid);
		for (int i = 0; i < resourceNumber; i++) {
			printf("%d ", current->allocation[i]);
		}
		for (int i = 0; i < resourceNumber; i++) {
			printf("%d ", current->need[i]);
		}
		printf("\n");
		current = current->next;
	}*/
	cycle(request, resourceNumber, processNumber);
}

void enqueue(int *temp, int rN) {

	int i = 0;
	struct PCB* new_node = (struct PCB*)malloc(sizeof(struct PCB));
	new_node->next = NULL;


	new_node->pid = temp[cnt];
	cnt++;
	for (i = 0; i < rN; i++) {
		new_node->allocation[i] = temp[cnt];
		cnt++;
	}
	for (i = 0; i < rN; i++)
	{
		new_node->max[i] = temp[cnt];
		cnt++;
	}

	for (i = 0; i < rN; i++) {
		new_node->need[i] = new_node->max[i] - new_node->allocation[i];
	}

	if (head == NULL) {
		head = new_node;
		tail = new_node;
	}
	else {
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;

	}
}
void dequeue(int temp_pid) {

	struct PCB  *p;

	p = head;
	p->prev = NULL;
	while (p != NULL) {
		if (p->pid == temp_pid) {
			if (p == head) {
				p->next->prev = NULL;
				p->next = head;
			}
			else if (p == tail) {
				tail->prev->next = NULL;
				tail->prev = tail;
			}
			else {
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}
		}
		else
			p = p->next;
	}
}

void cycle(struct NODE request, int rN, int pN) {

	int sequence[100];
	struct PCB *current = NULL;
	int check_bit[100], i, k = 0, state = 0, n = 0, m = 1, check_count = 0;
	int temp_pN = pN;
	current = head;

	for (i = 1; i <= pN; i++) {
		check_bit[i] = 0;
	}
	while (1) {
		while (current != NULL) {
			while (k < rN) {
				if ((available[k] >= current->need[k])) {
					state = 1;
					k++;
				}
				else {
					current = current->next;
				}
			}
			if (state == 1) {
				for (int a = 0; a < rN; a++) {
					available[a] = available[a] + current->allocation[a];
				}
				sequence[n] = current->pid;
				n++;
				check_bit[current->pid] = 1;
				current = current->next;
				dequeue(current->pid);
				temp_pN--;
				current = current->next;
			}			
		}
		for (int a = 0; a < pN; a++) {
			if (check_bit[i] == 1)
				check_count++;
		}
		if (check_count == temp_pN) {
			printf("All");
			exit(0);
		}
		else {
			for (int c = 0; c < pN; c++) {
				printf("%d", sequence[c]);
			}
		}
		if (current == NULL)
			break;

	}



	//while (1) {
	//	while (k < rN) {
	//		if ((available[k] >= current->need[k])) {
	//			state = 1;
	//			k++;
	//		}
	//		else {
	//			current = current->next;
	//		}
	//	}
	//	if (state == 1) {
	//		check_bit[current->pid] = 1;
	//		check_count++;
	//		while (n < temp_pN) {
	//			if (check_count == temp_pN) {
	//				printf("All");
	//				exit(0);
	//			}
	//			else {
	//				printf("p%d ->", current->pid);
	//				dequeue(head, current->pid);
	//				temp_pN--;
	//				for (int a = 0; a < rN; a++) {
	//					available[a] = available[a] + current->allocation[a];
	//				}
	//				current = current->next;
	//			}
	//		}
	//		
	//		//current = current->next;
	//		if (current == NULL)
	//			break;

	//	}
}