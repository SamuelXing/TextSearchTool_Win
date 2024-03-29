///////////////////////////////////////////////////////////////////////
// SimpleCompObj.cpp: Implementation of TextSearchComp               //
//                                                                   //
// Zihao Xing, CSE775 - Distributed Objects, Spring 2018             //
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SimpleCompObj.h"
#include "../FileMgrComp/FileMgrComp_i.h"
#include "../FileSystem/FileSystem.h"
#include <regex>
#include <atlsafe.h>
#pragma warning( disable : 4018)


// ------<pass a FileMgrComp reference to current instance>------
STDMETHODIMP CSimpleCompObj::passFileMgrIF(IUnknown* pFileMgr)
{
	pFileMgr_ = pFileMgr;
	return S_OK;
}

// -------<set searching text>--------
STDMETHODIMP CSimpleCompObj::setText(BSTR searchText)
{
	std::string std_searchText = BSTR2STDSTR(searchText);
	pSearch_->setText(std_searchText);
	return S_OK;
}

// --------<get searhcing results>-------
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
	if (rst.size() == 0)
		return E_HANDLE;
	for (int i = 0; i < rst.size(); i++)
		_ret.Add(CComBSTR(rst[i].c_str()));
	*pResult = _ret.Detach();
	return S_OK;
}


