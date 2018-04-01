#pragma once
#include "stdafx.h"
#include<string>
#include<vector>
#include "../FileMgr/FileMgrFactory.h"

class  ISearch
{
public:
	ISearch() {}
	virtual ~ISearch() {}
	virtual void setText(const std::string& reg) = 0;
	virtual void scanner(const std::string& fileSpec) = 0;
	virtual void scanner(const std::string& fileSpec, const std::string& text) = 0;
	virtual void put(const std::string&) = 0;
	virtual std::string get() = 0;
	virtual void done() = 0;
private:

};
