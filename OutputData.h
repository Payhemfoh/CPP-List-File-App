#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <filesystem>

#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WIN32
#define stat _stat
#define getFilePaths(path) UTF8Converter::to_utf8(path.generic_wstring())
#define getFileNames(path) UTF8Converter::to_utf8(path.filename().generic_wstring())
#define getDate(date,time) localtime_s(date, time)
#include "UTF8Converter.h"
#else
#include <unistd.h>
#define getFilePaths(path) path.generic_string()
#define getFileNames(path) path.filename().generic_string()
#define getDate(date,time) localtime_r(time, date)
#endif

class OutputData
{
private:
	std::ofstream output;
public:
	OutputData(std::string filename);
	~OutputData();
	void appendToFile(std::filesystem::path& file);
	bool is_open();
	void close();
	void outputStartFormat();
	void outputEndFormat();
	std::string toReadable(uintmax_t);
};

