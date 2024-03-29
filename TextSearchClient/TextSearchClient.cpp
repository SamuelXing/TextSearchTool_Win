///////////////////////////////////////////////////////////////
// TextSearchClient.cpp - The Client of the TextSearchTool   //
// ver 1.0                                                   //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018      //
///////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* - This package contains the TextSearchEngine class that talks 
* the FileMgr component and the TextSearch component
* - This package contains the main entry of this project
*
* Required Files:
* ---------------
* ../FileMgrComp/FileMgrComp_i.h
* ../TextSearchComp/TextSearchComp_i.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2018
* - first release
*
*/
#include "stdafx.h"
#include<atlbase.h>
#include <atlsafe.h>
#include<iostream>
#include<string>
#include<vector>
#include "../FileMgrComp/FileMgrComp_i.h"
#include "../TextSearchComp/TextSearchComp_i.h"
#pragma warning( disable : 4018)
#define TEST_SEARCH_COMP
#ifdef TEST_SEARCH_COMP


// ------<helper function to convert BSTR to std::string>----
namespace Utilities {
	std::string BSTR2STDSTR(const BSTR bstring, int cp = CP_UTF8) {
		std::wstring ws(bstring);
		std::string stdstr(ws.begin(), ws.end());
		return stdstr;
	}
}

//////////////////////////////////////////////////////
// Class Definition:
// - define the SearchEngine interface
// Public interfaces:
// =================
// void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg)
// -  start the searching process
class ISearchEngine 
{
public:
	ISearchEngine() {}
	virtual ~ISearchEngine() {}
	// ------<start the searching process>-------
	virtual void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) = 0;
};

//////////////////////////////////////////////////////
// Class Definition:
// - the definition of SearchEngine class
class SearchEngine : public ISearchEngine {
public:
	SearchEngine() {}
	virtual ~SearchEngine() {}
	// ------<start the searching process>-------
	void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) 
	{
		CoInitialize(NULL);
		{
			// create a FileMgrComp instance
			CComQIPtr<ICompFileMgr> pFileMgrComp;
			pFileMgrComp.CoCreateInstance(CLSID_CompFileMgr);
			if (pFileMgrComp){
				pFileMgrComp->getFileMgrInstance();
				CComBSTR Path(".");
				pFileMgrComp->setPath(Path);
				for (int i = 0; i < filePatterns.size(); i++) {
					CComBSTR pattern(filePatterns[i].c_str());
					pFileMgrComp->addPattern(pattern);
				}
				pFileMgrComp->traverse();
			}
			// create a SearchComp instance that using the FileMgrComp created above
			CComQIPtr<ISimpleCompObj> pSearchComp;
			pSearchComp.CoCreateInstance(CLSID_SimpleCompObj);
			if (pSearchComp){
				pSearchComp->passFileMgrIF(pFileMgrComp);
				CComBSTR text(reg.c_str());
				pSearchComp->setText(text);
				SAFEARRAY results;
				SAFEARRAY* pResults = &results;
				do {
					HRESULT hr = pSearchComp->getResult(&pResults); 
					if (hr == E_HANDLE) { std::cout << "no lines matched\n"; continue;}
					CComSafeArray<BSTR> Results;
					Results.Attach(pResults);
					if (Results.GetCount() == 1 && Utilities::BSTR2STDSTR(Results[0]) == "EOF") {
						std::cout << "\n======================\nend of processing\n";
						break;
					}
					std::cout << "Output of TextSearch Component:\n";
					for (int i = 0; i < (int)Results.GetCount(); ++i) {
						std::string output = Utilities::BSTR2STDSTR(Results[i]);
						std::cout << output << std::endl;
					}
					std::cout << "\n";
				} while (true);
			}
			std::wcout << "\n";
		}
		CoUninitialize();
		return;
	}
};


// ------<main entry>------------
int main(int argc, char** argv)
{
	std::cout << "TextSearchComponent Demonstration\n";
	std::cout << "=================================\n";
	std::string path;
	std::vector<std::string> filePatterns;
	std::string regStr;
	// command line argument parsing
	if (argc < 3) {
		std::cout << "Invalid arguments! Usage: client [reg_expression] [path] [patterns] ...\n";
		exit(0);
	}
	else
	{
		regStr = argv[1];
		path = argv[2];
		for (int i = 3; i<argc; i++)
			filePatterns.push_back(argv[i]);
	}
	ISearchEngine* pSearchEngine = new SearchEngine();
	pSearchEngine->startSearching(path, filePatterns, regStr);

	return 0;
}
#endif

