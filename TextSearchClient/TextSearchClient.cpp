// TextSearchClient.cpp : Defines the entry point for the console application.
// TODO: handle empty case
// TODO: API modifing

#include "stdafx.h"
#include<atlbase.h>
#include<iostream>
#include<string>
#include "../FileMgrComp/FileMgrComp_i.h"
#include "../TextSearchComp/TextSearchComp_i.h"

#define TEST_SEARCH_COMP
#ifdef TEST_SEARCH_COMP

std::string BSTR2STDSTR(const BSTR bstring, int cp = CP_UTF8) {
	std::wstring ws(bstring);
	std::string stdstr(ws.begin(), ws.end());
	return stdstr;
}

int main()
{
	std::cout << "Test Search Component";
	CoInitialize(NULL);
	{
		// create a FileMgrComp instance
		CComQIPtr<ICompFileMgr> pFileMgrComp;
		pFileMgrComp.CoCreateInstance(CLSID_CompFileMgr);
		if (pFileMgrComp)
		{
			pFileMgrComp->getFileMgrInstance();
			CComBSTR path(".");
			pFileMgrComp->setPath(path);
			CComBSTR pattern1("*.cpp");
			CComBSTR pattern2("*.h");
			pFileMgrComp->addPattern(pattern1);
			pFileMgrComp->addPattern(pattern2);
			pFileMgrComp->traverse();
		}

		// create a SearchComp instance that using the FileMgrComp created above
		CComQIPtr<ISimpleCompObj> pSearchComp;
		pSearchComp.CoCreateInstance(CLSID_SimpleCompObj);
		if (pSearchComp)
		{
			pSearchComp->passFileMgrIF(pFileMgrComp);
			CComBSTR text("(_|\\b)include(_|\\b)");
			pSearchComp->setText(text);
			BSTR fileSpec;
			std::string std_fileSpec;
			// start search
			do {
				HRESULT hr = pFileMgrComp->getResult(&fileSpec);
				if (!SUCCEEDED(hr))
					return E_FAIL;
				std_fileSpec = BSTR2STDSTR(fileSpec);
				pSearchComp->search(fileSpec, text);
			} while (std_fileSpec != "EOF");
			pSearchComp->done();

			BSTR result;
			std::string msg;
			do
			{
				pSearchComp->getRst(&result);
				std::wcout << "\n  " << result;
				msg = BSTR2STDSTR(result);
			} while (msg != "END");
		}
		std::wcout << "\n\n";
	}
	CoUninitialize();
	return 0;
}
#endif

