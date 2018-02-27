#pragma once
#include "ISearch.h"
#include "../FileMgr/FileMgrFactory.h"
#include "../CPPBlockingQueue/BlockingQueue.h"
#include "../FileSystem/FileSystem.h"

class Search :public ISearch
{
public:
	Search();
	virtual ~Search() { delete pFileMgr; }
	void put(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg);
	std::string get();
private:
	void scanner(std::string fileSpec, std::string reg);
private:
	Async::BlockingQueue<std::string> q_;
	IFileMgr * pFileMgr;
};