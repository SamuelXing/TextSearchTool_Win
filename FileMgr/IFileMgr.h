#pragma once
#ifndef IFILEMGR_H
#define IFILEMGR_H
#include<string>
#include<vector>

class IFileMgr
{
public:
	IFileMgr() {}
	virtual ~IFileMgr() {}
	virtual void traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns) = 0;
	virtual std::string get() = 0;
private:

};

#endif // !IFILEMGR_H