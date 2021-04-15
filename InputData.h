#pragma once
#include <string>
#include <fstream>

class InputData
{
private:
	std::ifstream input;
public:
	InputData(std::string filename);
	~InputData();
	bool is_open();
	bool eof();
	void close();
	std::string getline();
	std::string trim(std::string& str);
	std::string trimFront(std::string& str);
	std::string trimBack(std::string& str);
};

