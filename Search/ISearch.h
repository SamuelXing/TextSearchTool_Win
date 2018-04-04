#pragma once
//////////////////////////////////////////////////////////////
// ISearch.h - TextSearch Component Interface               //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
//////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package describe the interfaces of TextSearch component
*
* Required Files:
* ---------------
* ../FileMgr/FileMgrFactory.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2017
* - first release
*
*/
#include "stdafx.h"
#include<string>
#include<vector>
#include "../FileMgr/FileMgrFactory.h"

class  ISearch
{
public:
	ISearch() {}
	virtual ~ISearch() {}
	// ----<set searching text - a regular expression string>-----
	virtual void setText(const std::string& reg) = 0;
	// ---<for the given file, find the regular expression exixted or not>------
	virtual std::vector<std::string> scanner(const std::string& fileSpec) = 0;
	// ---<for the given file, find the regular expression exixted or not>------
	virtual std::vector<std::string> scanner(const std::string& fileSpec, const std::string& text) = 0;
private:

};
