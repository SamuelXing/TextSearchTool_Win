// SimpleCompObj.cpp : Implementation of CSimpleCompObj

#include "stdafx.h"
#include "SimpleCompObj.h"
#include "../FileMgrComp/FileMgrComp_i.h"
#include "../FileSystem/FileSystem.h"
#include <regex>
#include <atlsafe.h>


// CSimpleCompObj
STDMETHODIMP CSimpleCompObj::passFileMgrIF(IUnknown* pFileMgr)
{
	// TODO: Add your implementation code here
	pFileMgr_ = pFileMgr;
	return S_OK;
}

STDMETHODIMP CSimpleCompObj::setText(BSTR searchText)
{
	std::string std_searchText = BSTR2STDSTR(searchText);
	pSearch_->setText(std_searchText);
	return S_OK;
}


STDMETHODIMP CSimpleCompObj::getResult(SAFEARRAY ** pResult)
{
	CComQIPtr<ICompFileMgr> pFileMgr = pFileMgr_;
	if (!pFileMgr)
		return E_NOINTERFACE;
	CComSafeArray<BSTR> Record;
	std::string std_fileSpec;

	CComSafeArray<BSTR> _ret;
	SAFEARRAY record;
	SAFEARRAY* pRecord = &record;
	HRESULT hr = pFileMgr->get(&pRecord);
	if (!SUCCEEDED(hr))
		return E_FAIL;
	Record.Attach(pRecord);
	if (BSTR2STDSTR(Record[1]) == "EOF") 
	{
		std::string END = "EOF";
		_ret.Add(CComBSTR(END.c_str()));
		*pResult = _ret.Detach();
		return S_OK;
	}
	std_fileSpec = BSTR2STDSTR(Record[0]);
	std::vector<std::string> rst = pSearch_->scanner(std_fileSpec);
	for (int i = 0; i < rst.size(); i++)
		_ret.Add(CComBSTR(rst[i].c_str()));
	*pResult = _ret.Detach();
	//} while (BSTR2STDSTR(Record[1]) != "EOF");
	return S_OK;
}


