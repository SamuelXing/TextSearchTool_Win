// Search.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Search.h"
#include<regex>
#include<exception>

using namespace FileSystem;

void Search::setFileMgr(IFileMgr* IfileMgr) {
	pFileMgr = IfileMgr;
}

void Search::put(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) 
{
	try 
	{
		if (this->pFileMgr == nullptr)
			throw "empty fileMgr pointer";
		this->pFileMgr->traverseAndEnQ(path, filePatterns);
		std::string fileSpec;
		do 
		{
			fileSpec = this->pFileMgr->get();
			scanner(fileSpec, reg);
		} while (fileSpec != "EOF");
		this->q_.enQ("END");
	}
	catch (std::string err) 
	{
		std::cout << err << std::endl;
	}
}

std::string Search::get()
{
	return this->q_.deQ();
}

void Search::setText(const std::string& text) 
{
	text_ = text;
}

void Search::search() 
{
	std::string fileSpec;
	do
	{
		fileSpec = this->pFileMgr->get();
		scanner(fileSpec, text_);
	} while (fileSpec != "EOF");
	this->q_.enQ("END");
}

void Search::scanner(const std::string& fileSpec, const std::string& reg) 
{
	File in(fileSpec);
	in.open(File::in);
	int lineCnt = 1;
	std::regex r(reg);
	while (in.isGood())
	{
		std::string temp = in.getLine();
		if (std::regex_match(temp, r))
			this->q_.enQ(in.name() + ", line " + std::to_string(lineCnt) + ", "+temp);
		lineCnt++;
	}
}

void Search::scanner(const std::string& fileSpec) 
{
	File in(fileSpec);
	in.open(File::in);
	int lineCnt = 1;
	std::regex r(text_);
	while (in.isGood())
	{
		std::string temp = in.getLine();
		if (std::regex_match(temp, r))
			this->q_.enQ(in.name() + ", line " + std::to_string(lineCnt) + ", " + temp);
		lineCnt++;
	}
}



