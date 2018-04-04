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
	virtual std::vector<std::string> scanner(const std::string& fileSpec) = 0;
	virtual std::vector<std::string> scanner(const std::string& fileSpec, const std::string& text) = 0;
private:

};
