#include "InputData.h"

InputData::InputData(std::string filename) {
	this->input.open(filename, std::ios::in);
}

InputData::~InputData() {
	if (this->input) {
		this->input.close();
	}
}

bool InputData::is_open() {
	return this->input.is_open();
}

bool InputData::eof() {
	return this->input.eof();
}

void InputData::close() {
	if (this->input) {
		this->input.close();
	}
}

std::string InputData::getline() {
	std::string target("");
	if (!this->input.eof()) {
		//*this->input >> target;
		std::getline(this->input, target);
	}
	return this->trim(target);
}

std::string InputData::trim(std::string& str) {
	trimFront(str);
	trimBack(str);

	return str;
}

std::string InputData::trimFront(std::string& str) {
	str.erase(str.begin(), std::find_if(
		str.begin(), 
		str.end(),
		[](unsigned char c) {return !std::isspace(c); }
	));

	return str;
}

std::string InputData::trimBack(std::string& str) {
	str.erase(
		std::find_if(
			str.rbegin(), 
			str.rend(), 
			[](unsigned char c) {return !std::isspace(c); }
		).base(),
		str.end()
	);

	return str;
}