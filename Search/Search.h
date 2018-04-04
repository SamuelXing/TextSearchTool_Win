#pragma once
//////////////////////////////////////////////////////////////
// Search.h - TextSearch Component Interface                //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
//////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* The implementations of TextSearch Component
*
* Required Files:
* ---------------
* ../CPPBlockingQueue/BlockingQueue.h
* ../FileSystem/FileSystem.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2017
* - first release
*
*/

#include "ISearch.h"
#include "../CPPBlockingQueue/BlockingQueue.h"
#include "../FileSystem/FileSystem.h"

class Search :public ISearch
{
public:
	Search() {}
	virtual ~Search()
	{};
	// ----<set searching text - a regular expression string>-----
	void setText(const std::string&);
	// ---<for the given file, find the regular expression exixted or not>------
	std::vector<std::string> scanner(const std::string& fileSpec);
	// ---<for the given file, find the regular expression exixted or not>------
	std::vector<std::string> scanner(const std::string& fileSpec, const std::string& text);
private:
	std::string text_;
};