
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	int T;

	cin >> T;
	for (int i = 0; i < T; i++) {
		int count = 0;
		vector<string> c;
		string term;
		cin >> term;

		for (int j = 0; j < term.size(); j++) {
			c.push_back(term.substr(j, 1));

			if (c.size() == 1) {
				continue;
			}
			else {

				for (int k = 0; k < c.size() - 1; k++) {
					if (c.empty())
						break;

					string q = c[k];
					string w = c[k + 1];
					if (q == "(" && w == ")") {
						c.pop_back();
						c.pop_back();
					}

				}
			}
		}

		if (c.empty()) {
			cout << "YES" << endl;

		}
		else
			cout << "NO" << endl;
	}
}


vector<string> check(vector<string> b) {

	if (b.size() == 1) {
		return b;
	}
	else {
		for (int i = 0; i > b.size(); i++) {

			string termA = b[i];
			cout << termA << endl;
			string termB = b[i + 1];
			cout << termB << endl;
			if ((termA == ")" && termB == "(") || (termA == "(" && termB == ")")) {
				b.pop_back();
				b.pop_back();
			}
		}
		return b;
	}

}

