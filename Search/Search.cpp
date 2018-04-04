// Search.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Search.h"
#include<regex>
#include<exception>
#include<fstream>
#include <codecvt>
#include<algorithm>

using namespace FileSystem;

void Search::setText(const std::string& text) 
{
	text_ = text;
}

std::vector<std::string> Search::scanner(const std::string& fileSpec, const std::string& reg)
{
	std::cout << "\ncall TextSearch Component given inputs: " << fileSpec << ", " << reg << std::endl;
	std::cout << "===============================================================\n";
	int lineCnt = 1;
	std::regex r(reg);
	std::ifstream ifs(fileSpec);
	std::vector<std::string> rst;
	if (ifs.good())
	{
		std::string fileContent((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		fileContent.erase(std::remove(fileContent.begin(),fileContent.end(),'\0'), fileContent.end());
		std::istringstream f(fileContent);
		std::string line;
		while (std::getline(f, line)) {
			if (std::regex_search(line, r))
			{
				if (lineCnt == 1) line = line.substr(2);
				rst.push_back(FileSystem::Path::getName(fileSpec) + ", line " + std::to_string(lineCnt) + ", " + line);
			}
			lineCnt++;
		}
	}
	return rst;
}

std::vector<std::string> Search::scanner(const std::string& fileSpec)
{
	return this->scanner(fileSpec, text_);
}




