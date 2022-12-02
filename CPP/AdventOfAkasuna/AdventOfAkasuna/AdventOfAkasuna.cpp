#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <algorithm> 
#include <numeric>

using namespace std; 

const char* const cookie = "53616c7465645f5feef6b0564a27cd44690075eafbb271c054ae54586a63c973f24c1e8c1204d50379fd60ab3d8afc9aed55477f101ddc6a219d8dccc856423c";


std::vector<std::string> GetDayInput(char day) {
	FILE* fp;
	std::stringstream ss;
	ss << "curl https://adventofcode.com/2022/day/";
	ss << day;
	ss << "/input -H \"Cookie:session=";
	ss << cookie;
	fp = _popen(ss.str().c_str(), "r");
	if (fp == nullptr) {
		cout << "popen failed";
	}

	std::string result;
	char buffer[128];
	while (fgets(buffer, 128, fp) != nullptr) {
		result += buffer;
	}
	std::vector<std::string> resultVector;
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = result.find('\n', prev)) != std::string::npos) {
		resultVector.push_back(result.substr(prev, pos - prev));
		prev = pos + 1;
	}
	resultVector.push_back(result.substr(prev));
	return resultVector;
}

void DayOneOne() { 
	std::vector<std::string> input = GetDayInput('1');
	int sum = 0;
	int max = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i].empty()) {
			max = (sum >= max) ? sum : max;
			sum = 0;
		}
		else {
			sum += stoi(input[i]);
		}
	}
	cout << max;
}

void DayOneTwo() {
	std::vector<std::string> input = GetDayInput('1');
	std::vector<int> max{0,0,0};
	int sum = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i].empty()) {
			for (int j = 0; j < max.size(); j++) {
				if (sum >= max[j]) {
					max[j]=sum;
					break;
				}
			}
			sort(max.begin(), max.end());
			sum = 0;
		}
		else {
			sum += stoi(input[i]);
		}
	}
	cout << accumulate(max.begin(), max.end(),0);
}


int main()
{
	DayOneTwo();
	return 0;
}

