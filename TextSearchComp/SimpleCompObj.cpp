// SimpleCompObj.cpp : Implementation of CSimpleCompObj

#include "stdafx.h"
#include "SimpleCompObj.h"
#include "../FileMgrComp/FileMgrComp_i.h"

// CSimpleCompObj



STDMETHODIMP CSimpleCompObj::passFileMgrIF(IUnknown* pFileMgr)
{
	// TODO: Add your implementation code here
	pFileMgr_ = pFileMgr;
	return S_OK;
}


STDMETHODIMP CSimpleCompObj::getRst(BSTR* pReuslt)
{
	// TODO: Add your implementation code here
	std::string rst = pSearch_->get();
	CComBSTR BSTR_RST(rst.c_str());
	*pReuslt = BSTR_RST.Detach();
	return S_OK;
}


STDMETHODIMP CSimpleCompObj::setText(BSTR searchText)
{
	std::string std_searchText = BSTR2STDSTR(searchText);
	pSearch_->setText(std_searchText);
	return S_OK;
}


STDMETHODIMP CSimpleCompObj::startSearch()
{
	// TODO: Add your implementation code here
	CComQIPtr<ICompFileMgr> pFileMgr = pFileMgr_;
	if (!pFileMgr)
		return E_NOINTERFACE;
	BSTR fileSpec;
	std::string std_fileSpec;
	do {
		HRESULT hr = pFileMgr->getResult(&fileSpec);
		if (!SUCCEEDED(hr))
			return E_FAIL;
		std_fileSpec = BSTR2STDSTR(fileSpec);
		pSearch_->scanner(std_fileSpec);
	} while (std_fileSpec != "EOF");

	return S_OK;
}
