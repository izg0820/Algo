#include <iostream>
#include <string>

using namespace std;

void check(string term);
int que[10000];
int top = 0;
int back = -1;

int main() {
	int T;
	string term;
	for (int i = 0; i < 10000; i++) {
		que[i] = -1;
	}

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> term;
		check(term);
	}
}

void check(string term) {
	if (term.find("push") != string::npos) {
		int num;
		cin >> num;
		que[++back] = num;

	}
	else if (term.find("front") != string::npos) {
		if (back != -1) {
			cout << que[top] << "\n";
		}
		else {
			cout << "-1\n";
		}
	}
	else if (term.find("back") != string::npos) {
		if (back != -1) {
			cout << que[back] << "\n";
		}
		else {
			cout << "-1\n";
		}
	}
	else if (term.find("empty") != string::npos) {
		int size = 0;
		for (int i = 0; i < 10000; i++) {
			if (que[i] != -1) {
				size++;
			}

		}
		if (size != 0) {
			cout << "0\n";
		}
		else {
			cout << "1\n";
		}
	}

	else if (term.find("pop") != string::npos) {
		int size = 0;
		for (int i = 0; i < 10000; i++) {
			if (que[i] != -1) {
				size++;
			}

		}
		if (size != 0) {
			cout << que[top] << "\n";
			que[top++] = -1;
		}
		else {
			cout << "-1\n";
		}
	}
	else if (term.find("size") != string::npos) {
		int size = 0;
		for (int i = 0; i < 10000; i++) {
			if (que[i] != -1) {
				size++;
			}
		}
		cout << size << "\n";
	}
}