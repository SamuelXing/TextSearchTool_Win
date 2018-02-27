#pragma once
#include "stdafx.h"
#include<string>
#include<vector>

class  ISearch
{
public:
	ISearch() {}
	virtual ~ISearch() {}
	virtual void put(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) = 0;
	virtual std::string get() = 0;
private:

};
