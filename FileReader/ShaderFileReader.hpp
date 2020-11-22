#pragma once

#include <string>
#include <filesystem>
#include <ios>
#include <fstream>

#include <iostream>

namespace loser_reader{
	inline std::string readShaderFile(const std::filesystem::path& path_name) noexcept{
		std::string source_code;

		std::ifstream input(path_name, std::ios::binary);
		if(!input.is_open()){
			std::clog << "aaaaaaaaaa" << std::endl;
			return source_code;
		}

		std::string line;
		while(std::getline(input, line)){
			source_code += line + "\n";
			line.clear();
		}

		return source_code;
	}
}
