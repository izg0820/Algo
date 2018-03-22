//#include <stdio.h>
//#include <stdlib.h>
//#include <String.h>
//
//struct node{
//	struct node *lptr;
//	char key[81];
//}hash[33];
//
//int index,sum;
//int hash_sum(char *key);
//int hash_mod(int sum);
//int insert(struct node *ptr,char *key);
//int delete(struct node *ptr,char *key);
//int search(struct node *ptr, char *key);
//int print_table(struct node *ptr);
//
//
//void main() {
//	char term[50],i=0,choice,key[50];
//	FILE *fp = fopen("keyinput.txt", "r");
//
//	while (fscanf(fp, "%s", term) != EOF)
//	{
//		sum = hash_sum(term);
//		index = hash_mod(sum);
//		strcpy(hash[index].key, term[i]);
//		i++;
//	}
//	while (1) {
//		printf("1.Insert 2.Delete 3.Search 4.Print 5.Exit");
//		scanf("%d", &choice);
//		switch (choice) {
//		case 1:
//			printf("What is key to insert?");
//			scanf("%s", key);
//			insert(&hash[index],key);
//		case 2:
//			printf("What is key to delete?");
//			scanf("%s", key);
//			delete(&hash[index],key);
//		case 3:
//			printf("What is key to search?");
//			scanf("%s", key);
//			search(&hash[index],key);
//		case 4:
//			print_table();
//		case 5:
//			break;
//		}
//
//	}
//}
//int hash_sum(char *key) {
//	int i;
//	for (i = 0; i < 50; i++)
//	{
//		if (key[i] == NULL)
//			return 0;
//		else {
//			sum += atoi(key[i]);
//			return sum;
//		}
//	}
//}
//int hash_mod(int sum) {
//	index = sum % 33;
//	return index;
//}
//
//int insert(struct node *ptr, char *key) {
//	if (search(ptr, key) == 1) {
//		return 0;
//	}
//	if (ptr->key[0] == NULL) {
//		strcpy(ptr->key, key);
//		ptr->lptr = NULL;
//		return 1;
//	}
//	else{
//		if (ptr->lptr) {
//			strcmpt(key,ptr->key)==0;
//			return 0;
//		}
//		else 
//
//
//
//	
//}
#include <stdio.h>

void main() {
	int i, num, cnt = 0;

	for (i = 1;; i++) {
		printf("Insert the number: ");
		scanf("%d", &num);

		if (num % 3 == 0 || num % 5 == 0) {
			cnt++;
			continue;
		}
		else if (num == 0) {
			printf("%d", cnt);
			break;
		}
		
	}



}