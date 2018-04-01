#pragma once
#ifndef FILEMGR_H
#define FILEMGR_H

#include<iostream>
#include "IFileMgr.h"
#include "../CPPBlockingQueue/BlockingQueue.h"
#include "../FileSystem/FileSystem.h"
#include "../FileSystem/FileSystem.h"

class FileMgr : public IFileMgr 
{
	using path = std::string;
	using patterns = std::vector<std::string>;
public:
	FileMgr();
	virtual void traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns);
	virtual void traverseAndEnQ();
	virtual std::string get();
	void addPattern(const std::string& pattern);
	void setPath(const std::string& path);
	
private:
	Async::BlockingQueue<std::string> q_;
	path path_;
	patterns patterns_;
	void traverseHelper(const std::string& path, const std::vector<std::string>& filePatterns);
	void traverseHelper(const std::string& path);
};
#endif // !FILEMGR_H
