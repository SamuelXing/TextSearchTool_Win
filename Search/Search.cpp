// Search.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Search.h"
#include<regex>
#include<exception>
#include<fstream>
#include <codecvt>
#include<algorithm>

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

void Search::put(const std::string& rst) 
{
	this->q_.enQ(rst);
	return;
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
	/*
	File in(fileSpec);
	in.open(File::in);
	int lineCnt = 1;
	std::regex r(reg);
	while (in.isGood())
	{
		std::string temp = in.getLine();
		std::cout << temp << std::endl;
		if (std::regex_match(temp, r))
			this->q_.enQ(in.name() + ", line " + std::to_string(lineCnt) + ", "+temp);
		lineCnt++;
	}
	*/
	int lineCnt = 1;
	std::regex r(reg);
	std::ifstream ifs(fileSpec);
	if (ifs.good())
	{
		std::string fileContent((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		fileContent.erase(std::remove(fileContent.begin(),fileContent.end(),'\0'), fileContent.end());
		std::istringstream f(fileContent);
		std::string line;
		while (std::getline(f, line)) {
			//std::cout << line << std::endl;
			if (std::regex_search(line, r))
			{
				if (lineCnt == 1) line = line.substr(2);
				this->q_.enQ(FileSystem::Path::getName(fileSpec) + ", line " + std::to_string(lineCnt) + ", " + line);
			}
				//this->q_.enQ(FileSystem::Path::getName(fileSpec) + ", line " + std::to_string(lineCnt) + ", " + line);
			lineCnt++;
		}
	}

	/*
	int lineCnt = 1;
	std::regex r(reg);
	std::wifstream wif(fileSpec);
	if (wif.good())
	{
		wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
		std::wstringstream wss;
		wss << wif.rdbuf();
		std::wstring ws = wss.str();
		std::string fileContent(ws.begin(), ws.end());
		//std::string fileContent((std::istreambuf_iterator<char>(ifs)),
		//	(std::istreambuf_iterator<char>()));
		std::istringstream f(fileContent);
		std::string line;
		while (std::getline(f, line)) {
			std::cout << line << std::endl;
			if (std::regex_match(line, r))
				this->q_.enQ(FileSystem::Path::getName(fileSpec) + ", line " + std::to_string(lineCnt) + ", " + line);
			lineCnt++;
		}
	}
	*/
}


void Search::scanner(const std::string& fileSpec)
{
	File in(fileSpec);
	in.open(File::in);
	int lineCnt = 1;
	std::regex r(text_);
	std::string temp;
	while (in.isGood())
	{
		temp = in.getLine();
		if (std::regex_match(temp, r))
			this->q_.enQ(in.name() + ", line " + std::to_string(lineCnt) + ", " + temp);
		lineCnt++;
	}
}


void Search::done() 
{
	this->q_.enQ("END");
}



