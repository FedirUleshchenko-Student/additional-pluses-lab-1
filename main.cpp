#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <utility>
#include <fstream>
#include <stdexcept>
#include <format>
#include <vector>
#include <memory>
#include <chrono>
#include "DS.h"

using namespace std;

int main()
{
	if (true) {
		vector<string> data;
		data = { "1", "2", "3", "4", "5" };
		for (int i = 1; i <= data.size(); i++) {
			DS s(data, i);
			string ans;
			while (true) {
				//cout << s.currVar() << endl;
				try {
					ans = s();
				}
				catch (...) {
					break;
				}
				cout << ans << endl;
			}
			cout << string(40, '-') << endl;
			cout << string(40, '-') << endl;
		}
	}
	return 0;
}

