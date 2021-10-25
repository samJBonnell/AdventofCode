#include <iostream>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <regex>
#include <vector>
#include <utility>
#include <cstring>
#include <istream>
#include <string>
#include <sstream>

#define inputParam string

using namespace std;

struct passportStruct {
	pair<string, bool> byr;
	pair<string, bool> iyr;
	pair<string, bool> eyr;
	pair<string, bool> hgt;
	pair<string, bool> hcl;
	pair<string, bool> ecl;
	pair<string, bool> pid;
	pair<string, bool> cid;
	bool validBit = 0;
};

void fileInput(vector<inputParam>& inputVector, ifstream& in);
passportStruct parse(string passportInformation);
int validatePassport(passportStruct passport);


int main(void) {
	ifstream in;
	string fileName;
	vector<inputParam> passportInformation;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(0);
	}

	vector<passportStruct> passports;
	int passSum = 0;
	
	fileInput(passportInformation, in);
	for (auto const& ptr : passportInformation) {
		passports.push_back(parse(ptr));
	}

	for (auto const& ptr : passports) {
		passSum += validatePassport(ptr);
	}

	cout << passSum << endl;

	return 0;
}

void fileInput(vector<inputParam>& inputVector, ifstream& in) {
	string IO, temp = "";
	while (getline(in, IO)) {
		if (IO.empty()) {
			temp.erase(temp.end() - 1, temp.end());
			inputVector.push_back(temp); temp = "";
		}
		temp += IO + " ";
	}

	inputVector.push_back(temp);
}

passportStruct parse(string passportInformation) {
	string IO;
	vector<string> tempString;
	stringstream ss(passportInformation);
	passportStruct temp;

	while (getline(ss, IO, ' ')) {
		if (IO.find("byr") != IO.npos) { // Birth Year
			temp.byr.first = IO.substr(IO.find(":") + 1, IO.find(" "));
			temp.byr.second = 0;
		}
		if (IO.find("iyr") != IO.npos) { // Issue Year
			temp.iyr.first = IO.substr(IO.find(":") + 1, IO.find(" "));
			temp.iyr.second = 0;
		}
		if (IO.find("eyr") != IO.npos) { // Expiration Year
			temp.eyr.first = IO.substr(IO.find(":") + 1, IO.find(" "));
			temp.eyr.second = 0;
		}
		if (IO.find("hgt") != IO.npos) { // Height
			temp.hgt.first = IO.substr(IO.find(":") + 1, IO.find(" "));
			temp.hgt.second = 0;
		}
		if (IO.find("hcl") != IO.npos) { // Hair Colour
			temp.hcl.first = IO.substr(IO.find(":") + 1, IO.find(" "));
			temp.hcl.second = 0;
		}
		if (IO.find("ecl") != IO.npos) { // Eye Colour
			temp.ecl.first = IO.substr(IO.find(":") + 1, IO.find(" "));
			temp.ecl.second = 0;
		}
		if (IO.find("pid") != IO.npos) { // Passport ID
			temp.pid.first = IO.substr(IO.find(":") + 1, IO.find(" "));
			temp.pid.second = 0;
		}
		if (IO.find("cid") != IO.npos) { // Country ID
			temp.cid.first = IO.substr(IO.find(":") + 1, IO.find(" "));
			temp.cid.second = 0;
		}
	}

	if (temp.byr.first.empty()) temp.byr.first = "1";
	if (temp.iyr.first.empty()) temp.iyr.first = "1";
	if (temp.eyr.first.empty()) temp.eyr.first = "1";
	if (temp.hgt.first.empty()) temp.hgt.first = "1";
	if (temp.hcl.first.empty()) temp.hcl.first = "1";
	if (temp.ecl.first.empty()) temp.ecl.first = "1";
	if (temp.pid.first.empty()) temp.pid.first = "1";
	if (temp.cid.first.empty()) temp.cid.first = "1";

	return temp;
}

int validatePassport(passportStruct passport) {
	vector<string> eyeColour({ "amb" , "blu", "brn", "gry", "grn", "hzl", "oth" });
	int eyeColourCheck = 0;

	regex regHCL("(#[a-f0-9]{6})");
	regex regPID("([0-9]{9})");

	if (stoi(passport.byr.first) >= 1920 && stoi(passport.byr.first) <= 2002) passport.byr.second = 1; // Birth Year
	if (stoi(passport.iyr.first) >= 2010 && stoi(passport.iyr.first) <= 2020) passport.iyr.second = 1; // Issue Year
	if (stoi(passport.eyr.first) >= 2020 && stoi(passport.eyr.first) <= 2030) passport.eyr.second = 1; // Expiration Date
	if (passport.hgt.first.find("in") != passport.hgt.first.npos) {														   // Height
		passport.hgt.first.erase(passport.hgt.first.find("in"), passport.hgt.first.back());
		if (stoi(passport.hgt.first) >= 59 && stoi(passport.hgt.first) <= 76) passport.hgt.second = 1;
	}
	if (passport.hgt.first.find("cm") != passport.hgt.first.npos) {
		if (stoi(passport.hgt.first) >= 150 && stoi(passport.hgt.first) <= 193) passport.hgt.second = 1;
	}
	if (regex_match(passport.hcl.first, regHCL)) passport.hcl.second = 1;							   // Hair Colour
	
	for (auto const& ptr : eyeColour) {
		if (passport.ecl.first.find(ptr) != passport.ecl.first.npos) {
			eyeColourCheck++;
		}
	}
	if (eyeColourCheck == 1) passport.ecl.second = 1;
	if (regex_match(passport.pid.first, regPID)) passport.pid.second = 1;							   // Passport ID
	if (passport.byr.second == 1 && passport.ecl.second == 1 && passport.eyr.second == 1 && passport.hcl.second == 1 && passport.hgt.second == 1 && passport.iyr.second == 1 && passport.pid.second == 1) return 1;

	return 0;
}
