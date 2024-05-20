
#include "AdventOfAkasuna.h"
#include "day09.h"

using namespace std; 

const char* const cookie = "53616c7465645f5feef6b0564a27cd44690075eafbb271c054ae54586a63c973f24c1e8c1204d50379fd60ab3d8afc9aed55477f101ddc6a219d8dccc856423c";


std::vector<std::string> AdventOfCode::GetDayInput(char day) {
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

int main() {
	day09::part2();

}

