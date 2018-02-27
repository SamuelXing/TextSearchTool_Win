#include "stdafx.h"
#include "FileMgrFactory.h"
#include<iostream>

#ifdef TEST_FILEMGR

void test() 
{
	std::cout << "Here\n";
} 

int main()
{
	std::cout << "  DEMO FILE MANAGER \n";
	std::cout << "=====================\n";

	IFileMgr* fm = FileMgrFactory::CreateFileMgr();


	std::vector<std::string> filePatterns;
	filePatterns.push_back("*.cpp");

	fm->traverseAndEnQ(".", filePatterns);
	return 0;
}
#endif // TEST_FILEMGR

