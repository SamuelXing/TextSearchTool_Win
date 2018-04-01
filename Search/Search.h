#pragma once
#include "ISearch.h"
#include "../CPPBlockingQueue/BlockingQueue.h"
#include "../FileSystem/FileSystem.h"

class Search :public ISearch
{
public:
	Search() {}
	virtual ~Search()
	{
		if (pFileMgr != nullptr)
			delete pFileMgr;
	};
	void setText(const std::string&);
	void scanner(const std::string& fileSpec);
	///////////////////////
	void setFileMgr(IFileMgr* IfileMgr);
	void put(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg);
	void search();
	std::string get();
	void scanner(const std::string& fileSpec, const std::string& reg);
private:
	Async::BlockingQueue<std::string> q_;
	IFileMgr * pFileMgr;
	std::string text_;
};