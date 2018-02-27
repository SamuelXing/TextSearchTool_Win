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
public:
	virtual void traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns);
	virtual std::string get();

private:
	Async::BlockingQueue<std::string> q_;
	void traverseHelper(const std::string& path, const std::vector<std::string>& filePatterns);
};
#endif // !FILEMGR_H
