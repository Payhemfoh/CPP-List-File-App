#pragma once
#include <exception>
#include <string>

class FileNotFoundException : public std::exception
{
private:
	std::string path;
public:
	FileNotFoundException(std::string path);
	std::string msg() const throw();
};

