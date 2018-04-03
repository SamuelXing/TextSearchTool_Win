// CompFileMgr.cpp : Implementation of CCompFileMgr

#include "stdafx.h"
#include "CompFileMgr.h"
#include <atlsafe.h>

// CCompFileMgr
STDMETHODIMP CCompFileMgr::setPath(BSTR path)
{
	// TODO: Add your implementation code here
	if (fileMgr == nullptr)
		return E_FAIL;
	std::string pathStr = BSTR2STDSTR(path);
	fileMgr->setPath(pathStr);
	return S_OK;
}


STDMETHODIMP CCompFileMgr::addPattern(BSTR pattern)
{
	// TODO: Add your implementation code here
	if (fileMgr == nullptr)
		return E_FAIL;
	std::string patternStr = BSTR2STDSTR(pattern);
	fileMgr->addPattern(patternStr);
	return S_OK;
}


STDMETHODIMP CCompFileMgr::getFileMgrInstance()
{
	// TODO: Add your implementation code here
	fileMgr = FileMgrFactory::CreateFileMgr();
	return S_OK;
}


STDMETHODIMP CCompFileMgr::traverse()
{
	// TODO: Add your implementation code here
	if (fileMgr == nullptr)
		return E_FAIL;
	fileMgr->traverseAndEnQ();
	return S_OK;
}


STDMETHODIMP CCompFileMgr::getResult(BSTR* pResult)
{
	// TODO: Add your implementation code here
	std::string rst = fileMgr->get();
	CComBSTR BSTR_RST(rst.c_str());
	*pResult = BSTR_RST.Detach();
	return S_OK;
}

STDMETHODIMP CCompFileMgr::get(SAFEARRAY ** pResult)
{
	// TODO: Add your implementation code here
	std::array<std::string, 2> rst = fileMgr->get(0);
	CComSafeArray<BSTR> _record;
	_record.Add(CComBSTR(rst[0].c_str()));
	_record.Add(CComBSTR(rst[1].c_str()));
	*pResult = _record.Detach();
	return S_OK;
}
