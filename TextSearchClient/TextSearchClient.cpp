// TextSearchClient.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include<atlbase.h>
#include <atlsafe.h>
#include<iostream>
#include<string>
#include<vector>
#include "../FileMgrComp/FileMgrComp_i.h"
#include "../TextSearchComp/TextSearchComp_i.h"

#define TEST_SEARCH_COMP
#ifdef TEST_SEARCH_COMP

namespace Utilities {
	std::string BSTR2STDSTR(const BSTR bstring, int cp = CP_UTF8) {
		std::wstring ws(bstring);
		std::string stdstr(ws.begin(), ws.end());
		return stdstr;
	}
}

class ISearchEngine 
{
public:
	ISearchEngine() {}
	virtual ~ISearchEngine() {}
	virtual void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) = 0;
};

class SearchEngine : public ISearchEngine {
public:
	SearchEngine() {}
	virtual ~SearchEngine() {}
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
					pSearchComp->getResult(&pResults);
					CComSafeArray<BSTR> Results;
					Results.Attach(pResults);
					if (Results.GetCount() == 1 && Utilities::BSTR2STDSTR(Results[0]) == "EOF") {
						std::cout << "\n======================\nend of processing\n";
						break;
					}
					std::cout << "Output of TextSearch Component:\n";
					if ((int)Results.GetCount() == 0)
						std::cout << "no lines matched\n";
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

