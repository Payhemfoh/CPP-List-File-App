#include "OutputData.h"

OutputData::OutputData(std::string filename) {
	this->output.open(filename, std::ios::out | std::ios::binary);
	this->outputStartFormat();
}

OutputData::~OutputData() {
	this->close();
}

void OutputData::outputStartFormat() {
	std::string input("");
	std::ifstream startformat("startformat.bin", std::ios::in);
	if (startformat.is_open()) {
		while (!startformat.eof()) {
			std::getline(startformat, input);
			this->output << input << std::endl;
		}
	}
}

void OutputData::outputEndFormat() {
	std::string input("");
	std::ifstream endformat("endformat.bin",std::ios::in);
	if (endformat.is_open()) {
		while (!endformat.eof()) {
			std::getline(endformat, input);
			this->output << input << std::endl;
		}
	}
}


void OutputData::appendToFile(std::filesystem::path& file) {
	
	if (file.filename().c_str()[0] != '~') {
		std::string filepath = getFilePaths(file);
		struct stat result;

		if (stat(filepath.c_str(), &result) == 0) {
			auto mod_time = result.st_mtime;
			std::string filename = getFileNames(file);
			uintmax_t filesize = std::filesystem::file_size(file);
			std::string readable_size = toReadable(filesize);
			char date[50];

			struct tm timeinfo;
			getDate(&timeinfo, &mod_time);
			strftime(date, 50, "%F %T", &timeinfo);

			this->output << "INSERT INTO `files`(`filename`,`path`,`filesize`,`last_modified`) values ";
			this->output <<"(\"" << filepath <<"\",\"" << filename << "\",\"" << readable_size << "\",\"" << date<< "\");" << std::endl;

			if (this->output.fail()) {
				this->output.clear();
				this->output << std::endl;
			}
		}
	}
}

bool OutputData::is_open() {
	return this->output.is_open();
}

void OutputData::close() {
	if (this->output) {
		this->outputEndFormat();
		this->output.close();
	}
}

std::string OutputData::toReadable(uintmax_t filesize) {
	const double kB = 1024;
	const double MB = 1024 * 1024;
	const double GB = 1024 * 1024 * 1024;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	std::string size = std::to_string(filesize)+" Byte";

	if (filesize > GB) {
		stream << ceil(filesize*100 / GB)/100  << " GB";
		size = stream.str();
	}
	else if (filesize > MB) {
		stream << ceil(filesize * 100 / MB) / 100 << " MB";
		size = stream.str();
	}
	else if (filesize > kB) {
		stream << ceil(filesize * 100 / kB) / 100 << " kB";
		size = stream.str();
	}

	return size;
}