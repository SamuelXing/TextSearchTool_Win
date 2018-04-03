#pragma once
#ifndef FILEMGR_H
#define FILEMGR_H

#include<iostream>
#include "IFileMgr.h"
#include "../CPPBlockingQueue/BlockingQueue.h"
#include "../FileSystem/FileSystem.h"

class FileMgr : public IFileMgr 
{
	using path = std::string;
	using patterns = std::vector<std::string>;
public:
	FileMgr();
	virtual void traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns);
	virtual void traverseAndEnQ();
	virtual void addPattern(const std::string& pattern);
	virtual void setPath(const std::string& path);
	virtual std::string get();
	virtual std::array<std::string, 2> get(int);
private:
	Async::BlockingQueue<std::string> q_;
	path path_;
	patterns patterns_;
	void traverseHelper(const std::string& path, const std::vector<std::string>& filePatterns);

};
#endif // !FILEMGR_H
