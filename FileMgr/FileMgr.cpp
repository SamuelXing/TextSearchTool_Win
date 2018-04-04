// FileMgr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileMgr.h"
#include<exception>

using namespace FileSystem;

struct EmptyPath : public std::exception {
	const char* what() const throw() {
		return "path is null";
	}
};

FileMgr::FileMgr() {

}

void FileMgr::traverseHelper(const std::string& path, const std::vector<std::string>& filePatterns) 
{
	for (size_t i = 0; i < filePatterns.size(); i++)
	{
		std::vector<std::string> matchedFileNames = Directory::getFiles(path, filePatterns[i]);
		for (size_t j = 0; j < matchedFileNames.size(); j++)
		{
			std::string filePath = Path::fileSpec(path, matchedFileNames[j]);
			std::string fullName = Path::getFullFileSpec(filePath);
			this->q_.enQ(fullName);
			std::cout << "Found: " << fullName << std::endl;
		}
	}

	std::vector<std::string> dirs = Directory::getDirectories(path, "*");
	for (size_t i = 0; i < dirs.size(); i++)
	{
		if (dirs[i] == "." || dirs[i] == "..")
			continue;
		std::string fullDirPath = Path::fileSpec(path, dirs[i]);
		traverseHelper(fullDirPath, filePatterns);
	}

	return;
}

void FileMgr::traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns) 
{
	std::cout << "call FileManager Component given inputs: \n";
	std::cout << "path: " << path << std::endl;
	for (int i = 0; i < filePatterns.size(); i++)
		std::cout << "pattern: " << filePatterns[i] << std::endl;
	std::cout << "\nOutput of FileManager Component:\n";
	traverseHelper(path, filePatterns);
	std::cout << "-------------------------------------------------\n";
	std::cout << "Total: " << this->q_.size() << " files matched\n\n";
	this->q_.enQ("EOF");
	return;
}

void FileMgr::traverseAndEnQ() 
{
	try 
	{
		if (this->path_ == "")
			throw EmptyPath();
		if (this->patterns_.size() == 0)
			this->addPattern("*.*");
		this->traverseAndEnQ(path_, patterns_);
	}
	catch (EmptyPath& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}
}

void FileMgr::setPath(const std::string& path) 
{
	this->path_ = path;
}

void FileMgr::addPattern(const std::string& pattern) 
{
	this->patterns_.push_back(pattern);
}


std::string FileMgr::get() 
{
	return this->q_.deQ();
}

std::array<std::string, 2> FileMgr::get(int) 
{
	std::string fileSpec = this->get();
	std::array<std::string, 2> record;
	if (fileSpec != "EOF")
		record = { fileSpec, "FILE" };
	else
		record = { "", "EOF" };
	return record;
}
