// CompFileMgr.cpp : Implementation of CCompFileMgr

#include "stdafx.h"
#include "CompFileMgr.h"

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
