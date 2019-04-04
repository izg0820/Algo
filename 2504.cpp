#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	string line;

	cin >> line;
	vector<string> a;
	int result = 0;
	float ans = 1;

	for (int i = 0; i < line.size(); i++) {
		a.push_back(line.substr(i, 1));
	}



	for (int i = 0; i < a.size(); i++) {
		if (a[i] == "(") {
			ans = ans * 2;
		}
		else if (a[i] == "[") {
			ans = ans * 3;
		}
		else if (a[i] == ")") {
			if (i == 0) {
				ans = 3;
				break;
			}
			if (a[i - 1] == "]" || a[i - 1] == ")") {
				ans = ans / 2;
			}
			else if (a[i - 1] == "[") {
				result = 0;
				break;
			}
			else if (a[i - 1] == "(") {
				result = result + ans;
				ans = ans / 2;
			}
		}
		else if (a[i] == "]") {
			if (i == 0) {
				ans = 3;
				break;
			}
			if (a[i - 1] == "]" || a[i - 1] == ")") {
				ans = ans / 3;
			}
			else if (a[i - 1] == "[") {
				result = result + ans;
				ans = ans / 3;
			}
			else if (a[i - 1] == "(") {
				result = 0;
				break;
			}
		}
	}

	if (ans != 1) {
		cout << 0;
	}
	else {
		cout << (int)result;
	}
}

