#pragma once
#include "ISearch.h"
#include "../CPPBlockingQueue/BlockingQueue.h"
#include "../FileSystem/FileSystem.h"

class Search :public ISearch
{
public:
	Search() {}
	virtual ~Search()
	{};
	void setText(const std::string&);
	std::vector<std::string> scanner(const std::string& fileSpec);
	std::vector<std::string> scanner(const std::string& fileSpec, const std::string& text);
	///////////////////////
	/*
	void put(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg);
	void put(const std::string&);
	void search();
	*/
private:
	std::string text_;
};