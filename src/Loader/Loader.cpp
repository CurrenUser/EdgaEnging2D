#include "Loader.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string Loader::Loader::LoadShaderSrc(std::string src_file_path) {
	std::ifstream input;
	input.exceptions(std::ifstream::badbit);
	std::stringstream sstr;
	std::cout << "loading src_file:" + src_file_path << std::endl;

	try {
		input.open(src_file_path);

		while (input >> sstr.rdbuf());
			std::cout << sstr.str() << std::endl;
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error loading shader:" + src_file_path + " error:" + e.what() << std::endl;
		exit(-1);
	}

	input.close();
	return sstr.str();
}