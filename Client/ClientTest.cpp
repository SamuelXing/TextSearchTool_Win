#include<atlbase.h>
#include<iostream>
#include<string>
#include "../FileMgrComp/FileMgrComp_i.h"
#include "../SearchComp/SearchComp_i.h"

int main()
{
	std::cout << "Test Search Component";
	CoInitialize(NULL);

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
	CComQIPtr<ICompSearch> pSearchComp;
	pSearchComp.CoCreateInstance(CLSID_CompSearch);
	if (pSearchComp)
	{
		pSearchComp->passFileMgrIF(pFileMgrComp);
		CComBSTR text("(.*?)FileSys(.*?)");
		pSearchComp->setText(text);
		pSearchComp->startSearch();
		// get rst from searchComp
		BSTR result;
		pSearchComp->getRst(&result);
		std::wcout << "\n  " << result;
	}
	std::wcout << "\n\n";
	CoUninitialize();
	return 0;
}