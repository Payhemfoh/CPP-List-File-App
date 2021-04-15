#include "FileNotFoundException.h"


FileNotFoundException::FileNotFoundException(std::string path) {
	this->path = path;
}

std::string FileNotFoundException::msg() const throw() {
	return "Cannot Open File/Folder '" + this->path + "'";
}
