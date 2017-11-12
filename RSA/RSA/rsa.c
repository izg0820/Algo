#include<stdio.h>
#include<math.h>

long int p, q, e[100000], d[100000], phi, n;

int check_prime(long int);
void get_input();
int gcd(long int, long int);
void get_e();
void get_d(long int, int);
long int encrypte(long int);
long int decrypte(long int);

void main() {
	long int m, c;

	get_input();
	get_e();

	printf("enter the message ");
	scanf("%ld", &m);

	c = encrypte(m);

	printf("the result of encryption: %ld\n", c);

	m = decrypte(c);

	printf("the result of decryption: %ld\n", m);

	printf("n: %ld\n", n);
	printf("phi: %ld\n", phi);
	printf("e: %ld\n", e[0]);
	printf("d: %ld\n", d[0]);
}

/*
purpose: input 
input: none
output: none
*/
void get_input() {
	do {
		printf("enter prime number P ");
		scanf("%ld", &p);

		if (check_prime(p) == 0)
			printf("P is not a prime number\n");
	} while (check_prime(p) != 1);

	do {
		printf("enter prime number Q ");
		scanf("%ld", &q);

		if (check_prime(q) == 0)
			printf("Q is not a prime number\n");
	} while (check_prime(q) != 1);

	n = p * q;
	phi = (p - 1) * (q - 1);
}
/*
purpose: check whether input number is prime number
intput: one integer
output: prime number return 1 
*/
int check_prime(long int num) {
	int temp = sqrt(num);

	for (int i = 2; i <= temp; i++) {
		if (num % i == 0)
			return 0; 
	}

	return 1; 


}
/*
purpose: Find greatest common divisor
input: Two integer
output: greatest commom divisor
*/
int gcd(long int a, long int b) {
	if (a > b) {
		do {
			int temp = a % b;
			a = b;
			b = temp;
		} while (b != 0);

		return a;
	}
	else {
		do {
			int temp = b % a;
			b = a;
			a = temp;
		} while (a != 0);

		return b;
	}
}
/*
purpose: Find encryption key
input:none
output:none
*/
void get_e() {
	int index = 0;

	for (int i = 3; i < phi; i += 2) {
		if (gcd(phi, i) == 1 && i != p && i != q) {
			e[index] = i;
			get_d(i, index++);
		}
	}
}
/*
purpose: Find decryption key
input: integer, index 
output: none
*/
void get_d(long int e, int index) {
	long int k = 1;

	while (1) {
		k += phi;

		if (k%e == 0) {
			d[index] = k / e;
			return;
		}
	}
}

long int encrypte(long int message) {
	unsigned long long temp = (unsigned long long)pow((double)message, (double)e[0]);
	return temp % n; 
}


long int decrypte(long int cipher) {
	unsigned long long temp = (unsigned long long)pow((double)cipher, (double)d[0]);
	return temp % n; 
}