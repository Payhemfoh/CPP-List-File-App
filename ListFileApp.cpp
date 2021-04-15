/*
*	Author : Payhemfoh
*	Created At : 8 April 2021
*	Purpose : Read all files and subfolders and output a sql file which contains following details:
*			  - path
*			  - file name
*			  - file size
*			  - file date
* 
*/


#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include "FileNotFoundException.h"
#include "UTF8Converter.h"
#include "OutputData.h"
#include "InputData.h"


void checkFolder(std::filesystem::path, OutputData&);
void checkEntry(std::filesystem::directory_entry, OutputData&);

#ifdef _WIN32

#include <windows.h>
#define getFileName(path) UTF8Converter::to_utf8(path.generic_wstring());

int wmain(int argc, wchar_t** argv) {
	//setup console font type and codepage for compactibility reason
	CONSOLE_FONT_INFOEX cfi{ sizeof cfi , 0, {0,16}, FF_DONTCARE, FW_NORMAL, L"NSimSun" };

	SetConsoleOutputCP(65001);	//set codepage
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

#else

#define getFileName(path) path.generic_string();
int main(int argc,char** argv){

#endif
	//declare variable
	InputData input("folderList.txt");
	OutputData output("fileList.sql");
	std::vector<std::string> folderList;
	std::vector<std::string> checkedList;
	std::string data = "";

	try {
		
		//read folder path from input file
		if (!input.is_open()) {
			throw new FileNotFoundException("folderList.txt");
		}

		while (!input.eof()) {
			data = input.getline();
			folderList.push_back(data);
		}

		input.close();
		

		//check if output file is opened successfully
		if (!output.is_open()) {
			throw new FileNotFoundException("fileList.sql");
		}

		//loop through the given list
		for (std::string& temp : folderList) {
			try {
				std::filesystem::path p1 = temp;
				std::string path = p1.generic_string();
				std::replace(path.begin(), path.end(), '\\', '/');

				//check if folder is accessed before
				if (std::find(checkedList.begin(), checkedList.end(), path) == checkedList.end()) {
					
					//check if path is exist
					if (std::filesystem::exists(p1)) {
						checkFolder(p1, output);
					}
					else
						throw new FileNotFoundException(p1.generic_string());

					checkedList.push_back(path);
				}
			}
			catch (FileNotFoundException* e) {
				std::cerr << e->msg() << std::endl;
			}
		}
		std::cout << "SQL Exported successfully" << std::endl;
		output.close();
	}
	
	catch (FileNotFoundException* e) {
		std::cerr << e->msg() << std::endl;
	}
	catch (std::filesystem::filesystem_error& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Error" << std::endl;
	}
	
	std::cout << "Press any key to close the window." << std::endl;
	std::cin.ignore();

	return 0;
}

void checkEntry(std::filesystem::directory_entry entry, OutputData& output) {
	std::filesystem::path path = entry.path();
	if (std::filesystem::is_regular_file(path)) {
		output.appendToFile(path);
	}
}

void checkFolder(std::filesystem::path folder, OutputData& output) {
	std::string file = getFileName(folder);

	std::cout << "Checking : " << file << std::endl;
	if (std::filesystem::is_directory(folder)) {
		for (auto& temp : std::filesystem::recursive_directory_iterator(folder)) {
			checkEntry(temp,output);
		}
	}
	else {
		output.appendToFile(folder);
	}
}